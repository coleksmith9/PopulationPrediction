#include "GrassDiffEq.hpp"
#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>
#include <iostream>

GrassDiffEq::GrassDiffEq(std::string funcName): UnsolvedDiffEq::UnsolvedDiffEq(funcName) {
	//
}

void GrassDiffEq::setPrarieDogRef(std::shared_ptr<UnsolvedDiffEq> &prarieDogDERef){
	this->prarieDogDERef=prarieDogDERef;
}

void GrassDiffEq::incrementIndependentVar(void){
	UnsolvedDiffEq::incrementIndependentVar();
	//const double grassMax=UnsolvedDiffEq::constants->getConstant("GrassMax");
	//if (UnsolvedDiffEq::getDependentVar()>grassMax){
	//	UnsolvedDiffEq::curFuncVals.first=UnsolvedDiffEq::constants->getConstant("GrassMax");
	//} else if (UnsolvedDiffEq::getDependentVar()<0){
	//	UnsolvedDiffEq::curFuncVals.first=0;
	//}
}

double GrassDiffEq::calculateValue(void){
	const double popGrowth=UnsolvedDiffEq::constants->getConstant("GrassGrowthRate")*UnsolvedDiffEq::getDependentVar();
	const double popDecline=UnsolvedDiffEq::constants->getConstant("GrassEaten")*UnsolvedDiffEq::getDependentVar()*this->prarieDogDERef->getDependentVar();
	//const double populationGrowth=UnsolvedDiffEq::constants->getConstant("GrassGrowthRate")*UnsolvedDiffEq::getDependentVar();
	//const double populationDecline=UnsolvedDiffEq::constants->getConstant("GrassEaten")*this->prarieDogDERef->getDependentVar();
	//const double resourceLimitation=UnsolvedDiffEq::constants->getConstant("GrassGrowthRate")*UnsolvedDiffEq::getDependentVar()/UnsolvedDiffEq::constants->getConstant("GrassMax");
	return popGrowth-popDecline;
}
