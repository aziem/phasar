/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <phasar/PhasarLLVM/ControlFlow/LLVMBasedICFG.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/Gen.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/Kill.h>
#include <phasar/PhasarLLVM/IfdsIde/Problems/IFDSSignAnalysis.h>
#include <phasar/Utils/LLVMShorthands.h>
using namespace std;

IFDSSignAnalysis::IFDSSignAnalysis(IFDSSignAnalysis::i_t icfg,
                                   vector<string> EntryPoints)
    : DefaultIFDSTabulationProblem(icfg), EntryPoints(EntryPoints) {
  IFDSSignAnalysis::zerovalue = createZeroValue();
}

shared_ptr<FlowFunction<IFDSSignAnalysis::d_t>>
IFDSSignAnalysis::getNormalFlowFunction(IFDSSignAnalysis::n_t curr,
                                        IFDSSignAnalysis::n_t succ) {
  cout << "IFDSSignAnalysis::getNormalFlowFunction()\n";
  return Identity<IFDSSignAnalysis::d_t>::getInstance();
}

shared_ptr<FlowFunction<IFDSSignAnalysis::d_t>>
IFDSSignAnalysis::getCallFlowFunction(IFDSSignAnalysis::n_t callStmt,
                                      IFDSSignAnalysis::m_t destMthd) {
  cout << "IFDSSignAnalysis::getCallFlowFunction()\n";
  return Identity<IFDSSignAnalysis::d_t>::getInstance();
}

shared_ptr<FlowFunction<IFDSSignAnalysis::d_t>>
IFDSSignAnalysis::getRetFlowFunction(IFDSSignAnalysis::n_t callSite,
                                     IFDSSignAnalysis::m_t calleeMthd,
                                     IFDSSignAnalysis::n_t exitStmt,
                                     IFDSSignAnalysis::n_t retSite) {
  cout << "IFDSSignAnalysis::getRetFlowFunction()\n";
  return Identity<IFDSSignAnalysis::d_t>::getInstance();
}

shared_ptr<FlowFunction<IFDSSignAnalysis::d_t>>
IFDSSignAnalysis::getCallToRetFlowFunction(IFDSSignAnalysis::n_t callSite,
                                           IFDSSignAnalysis::n_t retSite,
                                           set<IFDSSignAnalysis::m_t> callees) {
  cout << "IFDSSignAnalysis::getCallToRetFlowFunction()\n";
  return Identity<IFDSSignAnalysis::d_t>::getInstance();
}

shared_ptr<FlowFunction<IFDSSignAnalysis::d_t>>
IFDSSignAnalysis::getSummaryFlowFunction(IFDSSignAnalysis::n_t callStmt,
                                         IFDSSignAnalysis::m_t destMthd) {
  cout << "IFDSSignAnalysis::getSummaryFlowFunction()\n";
  return Identity<IFDSSignAnalysis::d_t>::getInstance();
}

map<IFDSSignAnalysis::n_t, set<IFDSSignAnalysis::d_t>>
IFDSSignAnalysis::initialSeeds() {
  cout << "IFDSSignAnalysis::initialSeeds()\n";
  map<IFDSSignAnalysis::n_t, set<IFDSSignAnalysis::d_t>> SeedMap;
  for (auto &EntryPoint : EntryPoints) {
    SeedMap.insert(std::make_pair(&icfg.getMethod(EntryPoint)->front().front(),
                                  set<IFDSSignAnalysis::d_t>({zeroValue()})));
  }
  return SeedMap;
}

IFDSSignAnalysis::d_t IFDSSignAnalysis::createZeroValue() {
  // create a special value to represent the zero value!
  return LLVMZeroValue::getInstance();
}

bool IFDSSignAnalysis::isZeroValue(IFDSSignAnalysis::d_t d) const {
  return isLLVMZeroValue(d);
}

string IFDSSignAnalysis::DtoString(IFDSSignAnalysis::d_t d) const {
  return llvmIRToString(d);
}

string IFDSSignAnalysis::NtoString(IFDSSignAnalysis::n_t n) const {
  return llvmIRToString(n);
}

string IFDSSignAnalysis::MtoString(IFDSSignAnalysis::m_t m) const {
  return m->getName().str();
}