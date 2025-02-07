#include "ast/codegen.hh"

namespace ast {

std::unique_ptr<CodeGen> global_gen;

void CodeGen::startFunction(std::string& name) {
  // single __pcl_start function for void module
  llvm::FunctionType *FT = llvm::FunctionType::get(
      llvm::Type::getVoidTy(context_), /* va args? */ false);

  function_ = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name,
                                     module_.get());

  // basic block to start instruction insertion
  llvm::BasicBlock *bb = llvm::BasicBlock::Create(context_, "entry", function_);
  builder_->SetInsertPoint(bb);
}

llvm::Value* CodeGen::addUnOp(UnOp op, llvm::Value* lhs) {
  switch (op) {
  case UnOp::kPlus:
    return lhs;
  case UnOp::kMinus:
    return builder_->CreateNeg(lhs);
  case UnOp::kNot:
    return builder_->CreateNot(lhs);
  }
}

llvm::Value* CodeGen::addBinOp(BinOp op, llvm::Value* lhs, llvm::Value* rhs) {
  switch (op) {
  case BinOp::kAdd:
    return builder_->CreateAdd(lhs, rhs);
  case BinOp::kSub:
    return builder_->CreateSub(lhs, rhs);
  case BinOp::kMul:
    return builder_->CreateMul(lhs, rhs);
  case BinOp::kDiv:
    return builder_->CreateSDiv(lhs, rhs);
  case BinOp::kMod:
    return builder_->CreateSRem(lhs, rhs);
  case BinOp::kAnd:
    return builder_->CreateAnd(lhs, rhs);
  case BinOp::kOr:
    return builder_->CreateOr(lhs, rhs);
  case BinOp::kIsEq:
    return builder_->CreateICmpEQ(lhs, rhs);
  case BinOp::kIsNe:
    return builder_->CreateICmpNE(lhs, rhs);
  case BinOp::kIsGt:
    return builder_->CreateICmpSGT(lhs, rhs);
  case BinOp::kIsGe:
    return builder_->CreateICmpSGE(lhs, rhs);
  case BinOp::kIsLt:
    return builder_->CreateICmpSLT(lhs, rhs);
  case BinOp::kIsLe:
    return builder_->CreateICmpSLE(lhs, rhs);
  default:
    assert(0 && "Unhandled UnOp enum value");
  }
}

} // namespace ast
