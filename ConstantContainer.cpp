#include "ConstantContainer.hpp"
#include <fstream>
#include <utility>
#include <string>
#include <map>

ConstantContainer::ConstantContainer(const std::string &fileName){
	std::ifstream iFile(fileName);
	this->fail=iFile.fail();
	if (!this->fail){
		this->parseRawData(iFile);
		iFile.close();
	}
}

double ConstantContainer::getConstant(const std::string &id) const {
	if (this->constants.count(id)==1){
		return this->constants.at(id);
	}
	return 0;
}

void ConstantContainer::parseRawData(std::ifstream &iFile){
	while (!iFile.eof()){
		std::pair<std::string,double> iterPair;
		iFile >> iterPair.first >> iterPair.second;
		this->constants.insert(iterPair);
	}
}
