#pragma once

#include <map>
#include <memory>
#include <string>

#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"

#include "inode.hh"

namespace ast {

class CodeGen final {
  llvm::LLVMContext context_;
  std::unique_ptr<llvm::IRBuilder<>> builder_;
  std::unique_ptr<llvm::Module> module_;
  std::map<std::string, llvm::Value*> named_values_;

  llvm::Function* function_ = nullptr;

  CodeGen(std::string& module_name)
      : builder_(new llvm::IRBuilder<>(context_)),
        module_(new llvm::Module(module_name, context_)) {}

  // assumption: extern void Name() { ..... }
  void startFunction(std::string Name);

  void endCurrentFunction() { builder_->CreateRetVoid(); }

  void saveModule(std::string ModuleName);

  llvm::Value* addDeclRead(std::string varname) {
    auto* v = named_values_[varname];
    assert(v);
    auto* ty = static_cast<llvm::AllocaInst*>(v)->getAllocatedType();
    return builder_->CreateLoad(ty, v, varname.c_str());
  }

  llvm::Value* addDeclWrite(std::string varname, llvm::Value* rhs) {
    auto* v = named_values_[varname];
    assert(v);
    return builder_->CreateStore(rhs, v);
  }

  void addDecl(std::string varname) {
    auto&& bb = function_->getEntryBlock();
    auto ty = llvm::Type::getInt32Ty(context_);
    llvm::IRBuilder<> tmpb(&bb, bb.begin());
    auto *alloca = tmpb.CreateAlloca(ty, 0, varname.c_str());
    named_values_[varname] = alloca;
  }

  llvm::BasicBlock* startIf(llvm::Value* condv) {
    llvm::BasicBlock* thenbb = llvm::BasicBlock::Create(context_, "then", function_);
    llvm::BasicBlock* mergebb = llvm::BasicBlock::Create(context_, "endif", function_);
    builder_->CreateCondBr(condv, thenbb, mergebb);
    builder_->SetInsertPoint(thenbb);
    return mergebb;
  }

  void endIf(llvm::BasicBlock* mergebb) {
    // assume we are now in ThenBB
    builder_->CreateBr(mergebb);
    builder_->SetInsertPoint(mergebb);
  }

  using WhileBlocksTy = std::pair<llvm::BasicBlock*, llvm::BasicBlock*>;

  WhileBlocksTy StartWhile(llvm::Value* condv) {
    llvm::BasicBlock* bodybb = llvm::BasicBlock::Create(context_, "body", function_);
    llvm::BasicBlock* mergebb = llvm::BasicBlock::Create(context_, "endwhile", function_);
    builder_->CreateCondBr(condv, bodybb, mergebb);
    builder_->SetInsertPoint(bodybb);
    return std::make_pair(bodybb, mergebb);
  }

  void EndWhile(llvm::Value* condv, WhileBlocksTy bbs) {
    // assume we are now inside body
    builder_->CreateCondBr(condv, bbs.first, bbs.second);
    builder_->SetInsertPoint(bbs.second);
  }

  llvm::Type* getInt32Ty() { return llvm::Type::getInt32Ty(context_); }

  llvm::Type* getVoidTy() { return llvm::Type::getVoidTy(context_); }

  void createFnDecl(llvm::FunctionType* ft, std::string& name) {
    llvm::Function::Create(ft, llvm::Function::ExternalLinkage, name, module_.get());
  }
};

extern std::unique_ptr<CodeGen> global_gen;

} // namespace ast
