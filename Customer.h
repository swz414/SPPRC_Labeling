#pragma once

class Customer {
public:
	Customer(int custNo, int posX, int posY, int demand, int readyTime, int dueTime, int servTime) :
		custNo(custNo),
		posX(posX),
		posY(posY),
		demand(demand),
		readyTime(readyTime),
		dueTime(dueTime),
		servTime(servTime) {};

	int custNo;
	int posX;
	int posY;
	int demand;
	int readyTime;
	int dueTime;
	int servTime;
};