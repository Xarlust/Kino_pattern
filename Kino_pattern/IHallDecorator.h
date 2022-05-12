#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "IHall.h"
#include <windows.h>


class IHallDecorator : public IHall {
private:
	IHall* m_decoratedIHall;
public:
	IHallDecorator(IHall* decoratedIHall) : m_decoratedIHall(decoratedIHall) {
		m_decoratedIHall = decoratedIHall;
	}

	void getDecorator(int number_hall) {
		int full_hall = 0;
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		full_hall = m_decoratedIHall->Full_hall(number_hall);
		if (full_hall != 0) {
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		}
		else
		{
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		}
		m_decoratedIHall->Out_info_seat( number_hall);
	}
	friend class IHall;
};

