#ifndef GRASS_DE
#define GRASS_DE

#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>

class GrassDiffEq: public UnsolvedDiffEq {
	public:
		GrassDiffEq(std::string funcName);
		void incrementIndependentVar(void);
		void setPrarieDogRef(std::shared_ptr<UnsolvedDiffEq> &prarieDogDERef);
	protected:
		double calculateValue(void);
		std::shared_ptr<UnsolvedDiffEq> prarieDogDERef;
};

#endif
