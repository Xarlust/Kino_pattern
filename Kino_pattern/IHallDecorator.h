#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "IHall.h"
#include <windows.h>


class IHallDecorator : public IHall {
private:
	IHall* m_decoratedIHall;
public:
	IHallDecorator(IHall* decoratedIHall) : m_decoratedIHall(decoratedIHall) {}

	void getDecorator(IHall* Hall, int number_hall);
	friend class IHall;
};

void getDecorator(IHall* Hall, int number_hall) {

	int full_hall = 0;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	full_hall = Hall->Full_hall(number_hall);
	if (full_hall != 0) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		Hall->Out_info_seat(Hall, number_hall);
	}
	else
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		Hall->Out_info_seat(Hall, number_hall);
	}
}

/*class CollorDecorator : public IKinoDecorator { //декоратор
public:
	CollorDecorator(IKino *decoratedIKino): IKinoDecorator(decoratedIKino){}

};*/