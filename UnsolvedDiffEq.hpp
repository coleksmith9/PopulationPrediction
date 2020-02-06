#ifndef UNSOLVED_DIFF_EQ
#define UNSOLVED_DIFF_EQ

#include "ConstantContainer.hpp"
#include <utility>
#include <string>
#include <memory>

class UnsolvedDiffEq {
	public:
		UnsolvedDiffEq(const std::string &funcName);
		void setIndependentVar(double independentVar);
		const double getIndependentVar(void) const;
		void setIndependentVarStep(double indepentVarStep);
		const double getIndependentVarStep(void) const;
		const std::string& getFuncName(void) const;
		void setDependentVarInitialValue(double dependentVarInit);
		const double getDependentVar(void) const;
		void setConstants(const std::shared_ptr<ConstantContainer> &constants);
		void incrementIndependentVar(void);
		void calculateNewVal(void);
	protected:
		virtual double calculateValue(void)=0;
		void setCurFuncVals(void);
		std::shared_ptr<ConstantContainer> constants;
		std::pair<double,double> prevFuncValues;
		std::pair<double,double> curFuncVals;	//cur function value, cur function increment
		double independentVarStep;
		double independentVar;
		std::string funcName;
};

#endif
