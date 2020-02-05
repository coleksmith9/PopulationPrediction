#include "Simulation.hpp"
#include "ConstantContainer.hpp"
#include "PrarieDogDiffEq.hpp"
#include "GrassDiffEq.hpp"
#include "CSVFile.hpp"
#include <iostream>
#include <memory>

Simulation::Simulation(void){
	this->createConstCont();
	this->createDEModels();
	this->createCSVFile();
	this->initilizeDEModels();
}

void Simulation::createConstCont(void){
	this->constants=std::shared_ptr<ConstantContainer>(new ConstantContainer("data/constants.txt"));
}

void Simulation::createDEModels(void){
	this->grassDE=std::shared_ptr<GrassDiffEq>(new GrassDiffEq("GrassPopulation"));
	this->prarieDogDE=std::shared_ptr<PrarieDogDiffEq>(new PrarieDogDiffEq("PrarieDogPopulation"));
}

void Simulation::createCSVFile(void){
	this->csvFile=std::shared_ptr<CSVFile>(new CSVFile());
	this->csvFile->addHeader("Time");
	this->csvFile->addHeader(this->grassDE->getFuncName());
	this->csvFile->addHeader(this->prarieDogDE->getFuncName());
}

void Simulation::initilizeDEModels(void){
	std::shared_ptr<UnsolvedDiffEq> grassTemp=grassDE;
	std::shared_ptr<UnsolvedDiffEq> prarieDogTemp=prarieDogDE;

	this->grassDE->setPrarieDogRef(prarieDogTemp);
	this->grassDE->setConstants(this->constants);
	this->grassDE->setIndependentVarStep(this->constants->getConstant("TimeStep"));
	this->grassDE->setDependentVarInitialValue(this->constants->getConstant("GrassIV"));

	this->prarieDogDE->setGrassRef(grassTemp);
	this->prarieDogDE->setConstants(this->constants);
	this->prarieDogDE->setIndependentVarStep(this->constants->getConstant("TimeStep"));
	this->prarieDogDE->setDependentVarInitialValue(this->constants->getConstant("PrarieDogIV"));
}

void Simulation::resetCSVFile(void){
	this->csvFile->clear();
	this->csvFile->addHeader("Time");
	this->csvFile->addHeader(this->grassDE->getFuncName());
	this->csvFile->addHeader(this->prarieDogDE->getFuncName());
	this->setOutputFileName();
}

void Simulation::setOutputFileName(void){
	std::string temp;
	std::cout << "Please enter a file for output (ie. results.csv): ";
	getline(std::cin,temp);
	this->csvFile->setFileName(temp);
}

void Simulation::run(void){
	this->resetCSVFile();
	for (int i=0; i<this->constants->getConstant("SimulationLength"); i++){
		this->grassDE->incrementIndependentVar();
		this->prarieDogDE->incrementIndependentVar();

		this->grassDE->calculateNewVal();
		this->prarieDogDE->calculateNewVal();

		std::vector<double> iterData={ (double)i,grassDE->getDependentVar(), prarieDogDE->getDependentVar() };
		this->csvFile->addDataRow(iterData);
		//std::cout << "Grass DE:: Independent Var: " << grassDE->getIndependentVar() << " Dependent Var: " << grassDE->getDependentVar() << "   ";
		//std::cout << "Prarie Dog DE:: Independent Var: " << prarieDogDE->getIndependentVar() << " Dependent Var: " << prarieDogDE->getDependentVar() << std::endl;
	}
	this->csvFile->writeFile();
}
