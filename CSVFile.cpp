#include "CSVFile.hpp"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

CSVFile::CSVFile(void){
	//
}

CSVFile::CSVFile(std::string fileName){
	this->fileName=fileName;
}

void CSVFile::setFileName(std::string fileName){
	this->fileName=fileName;
}

void CSVFile::addHeader(std::string header){
	this->headers.push_back(header);
}

void CSVFile::addDataRow(std::vector<double> &row){
	this->data.push_back(row);
}

void CSVFile::setDataRow(const int index, std::vector<double> &row){
	if (index<this->data.size()){
		this->data.at(index)=row;
	}
}

const std::vector<double>& CSVFile::getDataRow(const int index) const {
	if (index<this->data.size()){
		return this->data.at(index);
	}
	return this->data.at(0);
}

double CSVFile::getDataRowAndHeader(const int index, const std::string &header) const {
	const int headerIndex=std::distance(this->headers.begin(),
			std::find(this->headers.begin(),this->headers.end(),header));
	if (index<this->data.size() && headerIndex<this->headers.size()){
		return this->data.at(index).at(headerIndex);
	}
	return 0;
}

void CSVFile::writeFile(void){
	if (this->fileName.size()>0 && this->headers.size()>0){
		std::ofstream oFile(this->fileName);
		for (unsigned int i=0; i<this->headers.size(); i++){
			oFile << this->headers.at(i);
			if (i!=this->headers.size()-1){
				oFile << ",";
			}
		}
		oFile << std::endl;
		for (unsigned int i=0; i<this->data.size(); i++){
			for (unsigned int j=0; j<this->data.at(i).size(); j++){
				oFile << this->data.at(i).at(j);
				if (j!=this->data.at(i).size()-1){
					oFile << ",";
				}
			}
			oFile << std::endl;
		}
		oFile.close();
	}
}

void CSVFile::clear(void){
	this->writeFile();
	this->headers.clear();
	for (unsigned int i=0; i<this->data.size(); i++){
		this->data.at(i).clear();
	}
	this->data.clear();
}
