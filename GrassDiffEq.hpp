#ifndef GRASS_DE
#define GRASS_DE

#include "UnsolvedDiffEq.hpp"
#include "ConstantContainer.hpp"
#include <string>
#include <memory>

class GrassDiffEq: public UnsolvedDiffEq {
	public:
		explicit GrassDiffEq(const std::string &funcName);
		void incrementIndependentVar(void);
		void setPrarieDogRef(const std::shared_ptr<UnsolvedDiffEq> &prarieDogDERef);
	protected:
		double calculateValue(void) override;
		std::shared_ptr<UnsolvedDiffEq> prarieDogDERef;
};

#endif
