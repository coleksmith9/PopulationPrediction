#ifndef PRARIE_DOG_DE
#define PRARIE_DOG_DE

#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>

class PrarieDogDiffEq: public UnsolvedDiffEq {
	public:
		explicit PrarieDogDiffEq(const std::string &funcName);
		void setGrassRef(const std::shared_ptr<UnsolvedDiffEq> &grassDERef);
	protected:
		double calculateValue(void) override;
		std::shared_ptr<UnsolvedDiffEq> grassDERef;
};

#endif
