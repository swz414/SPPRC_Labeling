#include "Data.h"

int main()
{
	bool ret = false;

	// Step 1: 读取数据
	string filename = "E:/others/运筹优化/庄若晨/Pulse_Python/instances/c101.txt";
	Data data;
	ret = data.ReadData(filename);
	if (!ret){
		db_print(DB_ERROR, "读取数据失败！\n");
		return 0;
	}
	db_print(DB_NORMAL, "vehicleNum: %d, capicity: %d, custNum: %d\n", data.vehicleNum, data.capicity, data.custNum);

	

}