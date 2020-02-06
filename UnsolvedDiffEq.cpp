#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <Utility>
#include <string>
#include <memory>

UnsolvedDiffEq::UnsolvedDiffEq(const std::string &funcName){
	this->funcName=funcName;
	this->independentVarStep=0;
	this->independentVar=0;
}

void UnsolvedDiffEq::setIndependentVar(double indepententVar){
	this->independentVar=independentVar;
}
const double UnsolvedDiffEq::getIndependentVar(void) const {
	return this->independentVar;
}

void UnsolvedDiffEq::setIndependentVarStep(double independentVarStep){
	this->independentVarStep=independentVarStep;
}
const double UnsolvedDiffEq::getIndependentVarStep(void) const {
	return this->independentVarStep;
}

const std::string& UnsolvedDiffEq::getFuncName(void) const {
	return this->funcName;
}

void UnsolvedDiffEq::setDependentVarInitialValue(double dependentVarInit) {
	this->curFuncVals.first=dependentVarInit;
}
const double UnsolvedDiffEq::getDependentVar(void) const {
	return this->curFuncVals.first;
}

void UnsolvedDiffEq::setConstants(const std::shared_ptr<ConstantContainer> &constants){
	this->constants=constants;
}

void UnsolvedDiffEq::incrementIndependentVar(void){
	this->prevFuncValues=this->curFuncVals;
	this->independentVar+=this->independentVarStep;
	this->setCurFuncVals();
}

void UnsolvedDiffEq::calculateNewVal(void){
	this->curFuncVals.second=this->calculateValue();
}

void UnsolvedDiffEq::setCurFuncVals(void){
	this->curFuncVals.first=this->prevFuncValues.first+this->prevFuncValues.second;
	this->curFuncVals.second=0;
}
