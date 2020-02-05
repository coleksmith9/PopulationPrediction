#include "PrarieDogDiffEq.hpp"
#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>
#include <cmath>

PrarieDogDiffEq::PrarieDogDiffEq(std::string funcName): UnsolvedDiffEq::UnsolvedDiffEq(funcName) {
	//
}

void PrarieDogDiffEq::setGrassRef(std::shared_ptr<UnsolvedDiffEq> &grassDERef){
	this->grassDERef=grassDERef;
}

double PrarieDogDiffEq::calculateValue(void){
	const double popGrowth=UnsolvedDiffEq::constants->getConstant("PrarieDogGrowthRate")*UnsolvedDiffEq::getDependentVar()*this->grassDERef->getDependentVar();
	const double popDecline=UnsolvedDiffEq::constants->getConstant("PrarieDogDeathRate")*UnsolvedDiffEq::getDependentVar();
	//const double populationGrowth=UnsolvedDiffEq::constants->getConstant("PrarieDogGrowthRate")*UnsolvedDiffEq::getDependentVar();
	//const double populationDecline=UnsolvedDiffEq::constants->getConstant("PrarieDogDeathRate")*UnsolvedDiffEq::getDependentVar();
	//const double resourceLimitation=(this->grassDERef->getDependentVar()>0)?
	//	0.5*UnsolvedDiffEq::getDependentVar()*log(UnsolvedDiffEq::constants->getConstant("GrassEaten")*UnsolvedDiffEq::getDependentVar()/this->grassDERef->getDependentVar()): 0;
	////const double resourceLimitation=(this->grassDERef->getDependentVar()!=0)? 
	////	pow(UnsolvedDiffEq::getDependentVar(),3)*pow(UnsolvedDiffEq::constants->getConstant("GrassEaten")/this->grassDERef->getDependentVar(),2): 0;
	return popGrowth-popDecline;
}
