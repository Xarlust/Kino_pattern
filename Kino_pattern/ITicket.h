#pragma once
#include <iostream>

class ITicket {					//�����
private:
	int number_hall;			//����� ����
	int seats;					//�����
	bool reservation = 0;	//����� �����
	ITicket* next;

	friend class IHall;
};