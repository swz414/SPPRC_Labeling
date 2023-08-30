# include "Data.h"

void Data::addCustomer(Customer cust)
{
	customers.push_back(cust);
	custNum += 1;
}

void Data::setVehicleNum(int vehi)
{
	vehicleNum = vehi;
}

void Data::setCapicity(int capi)
{
	capicity = capi;
}

// 读取数据
bool Data::ReadData(string filename, int maxCustNum)
{
	ifstream infile(filename);
	string line;
	int vehicleLine = 5;
	int customerLine = 10;
	int currLine = 0;
	int vehicleNum = 0, capacity = 0;
	int custNo, demand, readyTime, dueTime, servTime;
	float_t posX, posY;

	while (getline(infile, line))
	{
		currLine += 1;

		// 读取指定数量的客户
		if (currLine >= customerLine + maxCustNum)
			break;

		istringstream iss(line);

		if (currLine == vehicleLine)
		{
			iss >> vehicleNum >> capacity;
			setVehicleNum(vehicleNum);
			setCapicity(capacity);
		}
		else if (currLine >= customerLine)
		{
			iss >> custNo >> posX >> posY >> demand >> readyTime >> dueTime >> servTime;
			Customer tmpCus(custNo, posX, posY, demand, readyTime, dueTime, servTime);
			addCustomer(tmpCus);
		}
		else
		{
			continue;
		}
	}

	if (custNum <= 0 or vehicleNum <= 0 or capacity <= 0)
		return false;

	// 计算距离矩阵
	vector<vector<float_t>> disM(custNum, vector<float_t>(custNum));
	for (int i = 0; i < custNum; ++i)
	{
		for (int j = i; j < custNum; ++j)
		{
			if (i == j)
			{
				disM[i][j] = 0;
			}
			else
			{
				float_t tmpdis = (float_t)CalEuclidDis(customers[i].posX, customers[i].posY, customers[j].posX, customers[j].posY);
				disM[i][j] = disM[j][i] = tmpdis;
			}
		}
	}
	disMat.insert(disMat.end(), disM.begin(), disM.end());

	return true;
}

