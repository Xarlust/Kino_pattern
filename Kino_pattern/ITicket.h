#pragma once
#include <iostream>

class ITicket {					//билет
private:
	int number_hall;			//номер зала
	int seats;					//место
	bool reservation = 0;	//бронь места
	ITicket* next;

	friend class IHall;
};