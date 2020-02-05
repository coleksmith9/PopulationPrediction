#ifndef PRARIE_DOG_DE
#define PRARIE_DOG_DE

#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>

class PrarieDogDiffEq: public UnsolvedDiffEq {
	public:
		PrarieDogDiffEq(std::string funcName);
		void setGrassRef(std::shared_ptr<UnsolvedDiffEq> &grassDERef);
	protected:
		double calculateValue(void);
		std::shared_ptr<UnsolvedDiffEq> grassDERef;
};

#endif
