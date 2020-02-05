#ifndef SIMULATION
#define SIMULATION

#include "ConstantContainer.hpp"
#include "PrarieDogDiffEq.hpp"
#include "GrassDiffEq.hpp"
#include "CSVFile.hpp"
#include <memory>

class Simulation {
	public:
		Simulation(void);
		void run(void);
	private:
		void createConstCont(void);
		void createDEModels(void);
		void createCSVFile(void);
		void initilizeDEModels(void);
		void resetCSVFile(void);
		void setOutputFileName(void);
		std::shared_ptr<CSVFile> csvFile;
		std::shared_ptr<ConstantContainer> constants;
		std::shared_ptr<GrassDiffEq> grassDE;
		std::shared_ptr<PrarieDogDiffEq> prarieDogDE;
};

#endif
