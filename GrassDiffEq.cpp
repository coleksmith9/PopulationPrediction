#include "GrassDiffEq.hpp"
#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>
#include <iostream>

GrassDiffEq::GrassDiffEq(const std::string &funcName): UnsolvedDiffEq::UnsolvedDiffEq(funcName) {
	//
}

void GrassDiffEq::setPrarieDogRef(const std::shared_ptr<UnsolvedDiffEq> &prarieDogDERef){
	this->prarieDogDERef=prarieDogDERef;
}

void GrassDiffEq::incrementIndependentVar(void){
	UnsolvedDiffEq::incrementIndependentVar();
}

double GrassDiffEq::calculateValue(void){
	const double popGrowth=UnsolvedDiffEq::constants->getConstant("GrassGrowthRate")*UnsolvedDiffEq::getDependentVar();
	const double popDecline=UnsolvedDiffEq::constants->getConstant("GrassEaten")*UnsolvedDiffEq::getDependentVar()*this->prarieDogDERef->getDependentVar();
	return popGrowth-popDecline;
}
