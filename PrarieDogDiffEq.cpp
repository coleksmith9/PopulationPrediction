#include "PrarieDogDiffEq.hpp"
#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>
#include <cmath>

PrarieDogDiffEq::PrarieDogDiffEq(const std::string &funcName): UnsolvedDiffEq::UnsolvedDiffEq(funcName) {
	//
}

void PrarieDogDiffEq::setGrassRef(const std::shared_ptr<UnsolvedDiffEq> &grassDERef){
	this->grassDERef=grassDERef;
}

double PrarieDogDiffEq::calculateValue(void){
	const double popGrowth=UnsolvedDiffEq::constants->getConstant("PrarieDogGrowthRate")*UnsolvedDiffEq::getDependentVar()*this->grassDERef->getDependentVar();
	const double popDecline=UnsolvedDiffEq::constants->getConstant("PrarieDogDeathRate")*UnsolvedDiffEq::getDependentVar();
	return popGrowth-popDecline;
}
