#include "COP.h"

void COP::readRawData(string rawDataPath)
{
	std::ifstream fin;
	string str;
	int sensorNumber = 99;
	fin.open(rawDataPath);
	if (!fin.is_open()) { cout << "Failed to open raw data file\n"; }
	std::getline(fin, str);
	//for (int i = 0; i < sensorNumber; i++)
	//{
	//	vector<double> row;
	//	while (std::getline(fin, str))
	//	{

	//	}
	//}
}

void COP::readPosition(string positionPath)
{
}

double COP::calculateCOP(vector<vector<double>> RawData, vector<vector<double>> Position)
{
	return 0.0;
}
