#pragma once

class Customer {
public:
	Customer(int custNo, float_t posX, float_t posY, int demand, int readyTime, int dueTime, int servTime) :
		custNo(custNo),
		posX(posX),
		posY(posY),
		demand(demand),
		readyTime(readyTime),
		dueTime(dueTime),
		servTime(servTime) {};

	int custNo;
	float_t posX;
	float_t posY;
	int demand;
	int readyTime;
	int dueTime;
	int servTime;
};