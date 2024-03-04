#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<fstream>
using std::vector;
using std::string;
using std::ifstream;
using std::cout;
class COP
{
private:
	vector<vector<double>>sensorRawData;
	vector<vector<double>>sensorPosition;
public:
	void readRawData(string rawDataPath);
	void readPosition(string positionPath);
	double calculateCOP(vector<vector<double>> RawData, vector<vector<double>> Position);
};
