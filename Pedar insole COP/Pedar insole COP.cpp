// Pedar insole COP.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include<fstream>
#include<sstream>
#include<iterator>
#include<string>
#include<cmath>
#include<vector>
using std::string;
using std::vector;
using std::cout;
void readFile(string rawDataPath,vector<vector<double>>* rawData);
void readNodeNumberOfSensor(string rawDataPath, vector<vector<double>>* rawData);
void calculateSensorPosition(vector<vector<double>>* nodePosition, vector<vector<double>>* sensorNode, vector<vector<double>>* sensorPosition);
void calculateCOP(vector<vector<double>>* rawData, vector<vector<double>>* position, vector<vector<double>>* COP);
void calCOPnotAllSensor(vector<vector<double>>* rawData, vector<vector<double>>* position, vector<vector<double>>* COP);
void coutArr(vector<vector<double>>* data, string dataName);
void outputFile(string outputPath, vector<vector<double>>* vec);
int main()
{
	string sensorNodePath = "sensor\\sensor node.txt";
	string nodePosPath = "sensor\\node position.txt";
	string leftRawDataPath = "raw data\\L13.txt";
	string rightRawDataPath = "raw data\\R13.txt";
	string sensorPositionPath = "sensor position\\Pedar.txt";//different size (L or X); left and right foot sensor position are the same
	string leftOutputPath = "COP data\\L13COP-3 not all sensor.txt";
	string rightOutputPath = "COP data\\R13COP.txt";
	vector<vector<double>>nodePosition;
	vector<vector<double>>sensorNode;
	vector<vector<double>>LrawData;
	vector<vector<double>>RrawData;
	vector<vector<double>>position;
	vector<vector<double>>LCOP;
	vector<vector<double>>RCOP;
	readFile(nodePosPath, &nodePosition);
	readNodeNumberOfSensor(sensorNodePath, &sensorNode);
	//calculateSensorPosition(&nodePosition, &sensorNode, &position);
	//outputFile(sensorPositionPath, &position);
	readFile(leftRawDataPath, &LrawData);//read raw data
	//readFile(rightRawDataPath, &RrawData);
	readFile(sensorPositionPath, &position);//read sensor position
	//calculateCOP(&LrawData, &position, &LCOP);
	calCOPnotAllSensor(&LrawData, &position, &LCOP);
	coutArr(&LCOP, "LCOP");
	outputFile(leftOutputPath, &LCOP);

	//test read file
	//cout << "\n~~~node position~~~\n";
	//for (int i = 0; i < nodePosition.size(); i++)
	//{
	//	for (int j = 0; j < nodePosition[0].size(); j++)
	//	{
	//		cout << nodePosition[i][j] << " ";
	//	}
	//	cout << std::endl;
	//}
	//cout << "\n~~~sensor node~~~\n";
	//for (int i = 0; i < sensorNode.size(); i++)
	//{
	//	for (int j = 0; j < sensorNode[i].size(); j++)
	//	{
	//		cout << sensorNode[i][j] << " ";
	//	}
	//	cout << std::endl;
	//}
	//cout << "\n~~~sensor position~~~\n";
	//for (int i = 0; i < position.size(); i++)
	//{
	//	for (int j = 0; j < position[0].size(); j++)
	//	{
	//		cout << position[i][j] << " ";
	//	}
	//	cout << std::endl;
	//}
	//cout << "\n~~~raw data~~~\n";
	//int count = 0;
	//for (int i = 0; i < LrawData.size(); i++)
	//{
	//	for (int j = 0; j < LrawData[0].size(); j++)
	//	{
	//		cout << LrawData[i][j] << " ";
	//	}
	//	cout << std::endl;
	//	count++;
	//	if (count == 10)
	//		break;
	//}
	//cout << "\n~~~position~~~\n";
	//for (int i = 0; i < position.size(); i++)
	//{
	//	for (int j = 0; j < position[0].size(); j++)
	//	{
	//		cout << position[i][j] << " ";
	//	}
	//	cout << std::endl;
	//}
	//cout << "\n~~~COP~~~\n";
	//for (int i = 0; i < LCOP.size(); i++)
	//{
	//	for (int j = 0; j < LCOP[0].size(); j++)
	//	{
	//		cout << LCOP[i][j] << " ";
	//	}
	//	cout << std::endl;
	//}

}

void readFile(string rawDataPath, vector<vector<double>> *rawData)//for read m*n vector
{
	std::ifstream fin;
	string str;
	fin.open(rawDataPath);
	if (!fin.is_open()) { cout << "Failed to open data file\n"; }
	//std::getline(fin, str);
	while (std::getline(fin, str))
	{
		std::istringstream ss(str);
		(*rawData).emplace_back(std::istream_iterator<double>(ss), std::istream_iterator<double>());
	}
}

void readNodeNumberOfSensor(string rawDataPath, vector<vector<double>>* rawData)//讀取非方陣,for input node number of sensor
{
	std::ifstream fin;
	string str;
	int numberOfNode;
	int i = 0;
	fin.open(rawDataPath);
	if (!fin.is_open()) { cout << "Failed to open data file\n"; }
	(*rawData).resize(99);
	while (fin >> numberOfNode)
	{
		(*rawData)[i].resize(numberOfNode);
		if (numberOfNode == 3)
		{
			fin >> (*rawData)[i][0];
			fin >> (*rawData)[i][1];
			fin >> (*rawData)[i][2];
		}
		else
		{
			fin >> (*rawData)[i][0];
			fin >> (*rawData)[i][1];
			fin >> (*rawData)[i][2];
			fin >> (*rawData)[i][3];
		}
		i++;
	}
}

void calculateSensorPosition(vector<vector<double>>* nodePosition, vector<vector<double>>* sensorNode, vector<vector<double>>* sensorPosition)
{
	double numeratorX = 0;
	double numeratorY = 0;
	(*sensorPosition).resize(99);
	for (int i = 0; i < (*sensorPosition).size(); i++)
	{
		(*sensorPosition)[i].resize(2);
		numeratorX = 0; numeratorY = 0;
		for (int j = 0; j < (*sensorNode)[i].size(); j++)
		{
			numeratorX += (*nodePosition)[(*sensorNode)[i][j] - 1][0];
			numeratorY += (*nodePosition)[(*sensorNode)[i][j] - 1][1];
		}
		if ((*sensorNode)[i].size() == 3)
		{
			(*sensorPosition)[i][0] = numeratorX / 3;
			(*sensorPosition)[i][1] = numeratorY / 3;
		}
		else
		{
			(*sensorPosition)[i][0] = numeratorX / 4;
			(*sensorPosition)[i][1] = numeratorY / 4;
		}
	}
}

void calculateCOP(vector<vector<double>>* rawData, vector<vector<double>>* position, vector<vector<double>>* COP)
{
	double numeratorX = 0; double numeratorY = 0;
	double denometerX = 0; double denometerY = 0;
	(*COP).resize((*rawData).size());
	for (int i = 0; i < (*rawData).size(); i++)//i is time
	{
		(*COP)[i].resize(2);
		numeratorX = 0; numeratorY = 0;
		denometerX = 0; denometerY = 0;
		for (int j = 0; j < (*rawData)[0].size(); j++)//j is sensor number
		{
			numeratorX += ((*rawData)[i][j]) * ((*position)[j][0]);
			denometerX += (*rawData)[i][j];
			numeratorY += ((*rawData)[i][j]) * ((*position)[j][1]);
			denometerY += (*rawData)[i][j];
		}
		if ((denometerX != 0) && (denometerY != 0))
		{
			(*COP)[i][0] = numeratorX / denometerX;//COPX
			(*COP)[i][1] = numeratorY / denometerY;//COPY
		}
		else
		{
			(*COP)[i][0] = 0;
			(*COP)[i][1] = 0;
		}
	}
}

void calCOPnotAllSensor(vector<vector<double>>* rawData, vector<vector<double>>* position, vector<vector<double>>* COP)
{
	double numeratorX = 0; double numeratorY = 0;
	double denometerX = 0; double denometerY = 0;
	//int sensorNumArr[] = { 8,10,61,63,66,67,68,70,71,72,73,84 };//test 1
	//int sensorNumArr[] = { 8,10,61,63,66,68,71,84 };//test 2
	int sensorNumArr[] = { 7,8,10,11,61,63,66,67,68,70,71,72,73,84 };//test 3
	(*COP).resize((*rawData).size());
	for (int i = 0; i < (*rawData).size(); i++)//i is time
	{
		(*COP)[i].resize(2);
		numeratorX = 0; numeratorY = 0;
		denometerX = 0; denometerY = 0;
		for (int j, k = 0; k < sizeof(sensorNumArr)/sizeof(sensorNumArr[0]); k++)//j is sensor number
		{
			j = sensorNumArr[k] - 1;
			numeratorX += ((*rawData)[i][j]) * ((*position)[j][0]);
			denometerX += (*rawData)[i][j];
			numeratorY += ((*rawData)[i][j]) * ((*position)[j][1]);
			denometerY += (*rawData)[i][j];
		}
		if ((denometerX != 0) && (denometerY != 0))
		{
			(*COP)[i][0] = numeratorX / denometerX;//COPX
			(*COP)[i][1] = numeratorY / denometerY;//COPY
		}
		else
		{
			(*COP)[i][0] = 0;
			(*COP)[i][1] = 0;
		}
	}

}

void coutArr(vector<vector<double>>* data, string dataName)
{
	cout << "\n~~~~~" << dataName << "~~~~~\n";
	for (int i = 0; i < (*data).size(); i++)
	{
		for (int j = 0; j < (*data)[0].size(); j++)
		{
			cout << (*data)[i][j] << " ";
		}
		cout << std::endl;
	}
}

void outputFile(string outputPath, vector<vector<double>>* vec)
{
	std::ofstream fout;
	fout.open(outputPath);
	if (!fout.is_open()) { cout << "Failed to open data file\n"; }
	for (int i = 0; i < (*vec).size(); i++)
	{
		for (int j = 0; j < (*vec)[i].size(); j++)
		{
			fout << (*vec)[i][j];
			if (j != (*vec)[i].size() - 1)
				fout << " ";
		}
		if (i != (*vec).size() - 1)
			fout << "\n";
	}
	fout.close();
}
