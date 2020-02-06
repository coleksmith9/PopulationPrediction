#ifndef CSV_FILE
#define CSV_FILE

#include <fstream>
#include <string>
#include <vector>

class CSVFile {
	public:
		CSVFile(void);
		CSVFile(std::string fileName);
		void setFileName(std::string fileName);
		void addHeader(std::string header);
		void addDataRow(std::vector<double> &row);
		void setDataRow(const int index, std::vector<double> &row);
		const std::vector<double>& getDataRow(const int index) const;
		double getDataRowAndHeader(const int index, const std::string &header) const;
		void writeFile(void);
		void clear(void);
	private:
		std::vector<std::string> headers;
		std::vector<std::vector<double>> data;
		std::string fileName;
};

#endif
