#ifndef CONSTANT_CONTAINER
#define CONSTANT_CONTAINER

#include <fstream>
#include <string>
#include <map>

class ConstantContainer {
	public:
		explicit ConstantContainer(const std::string &fileName);
		double getConstant(const std::string &id) const;
	private:
		void parseRawData(std::ifstream &iFile);
		std::map<std::string,double> constants;
		bool fail;
};

#endif
