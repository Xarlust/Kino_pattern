#pragma once
#include "IHall.h"
#include "IKino.h"
#include "IHallDecorator.h"
#include <iostream>
#include <windows.h>


class Cinema_park : public IHall, IKino {
private:
	IHall* hall;
	IKino* film;
	IHallDecorator* decorator;

	Cinema_park()
	{
		hall = 0;
		film = 0;
		decorator = 0;
	}

public:
	/*Cinema_park(Cinema_park& outher) = delete;
	void operator=(const Cinema_park&) = delete;
	static Cinema_park* GetInstance();*/
	void Create(int number_hall, int number_seats, char name, char duration, int age_limit);
	void Delete();
	bool Empty();
	void Clear();
	void View();
	void Purchase_Ticket(int number_hall, int seats);//покупка билетов
	void Out_info_seat(int number_hall);
	bool Check_purchase_ticket(int number_hall, int seats);
	static Cinema_park* getInstance() {
		static Cinema_park instance;
		return &instance;
	}
	~Cinema_park()
	{
		Clear();
	}
};

/* Cinema_park* Cinema_park::GetInstance()
{
	if (cinema == nullptr)
		Cinema_park* cinema = new Cinema_park();
	return cinema;
}*/


void Cinema_park::Create(int number_hall, int number_seats, char name, char duration, int age_limit)
{
	IHall* NewHall = new IHall();
	IHallDecorator* NewDecorator = new IHallDecorator(NewHall);
	IKino* NewKino = new IKino();
	if (NewHall)  //  создания зала  и выхов созданя билетов
	{
		NewHall->number_seats = number_seats;
		NewHall->next = 0;
		NewHall->Create_full(number_hall, number_seats);

		if (hall == NULL)
		{
			hall = NewHall;
		}
		else
		{
			NewHall->next = hall;
			hall = NewHall;
		}
	}

	if (NewKino) // создание фильма для зала 
	{
		NewKino->Create(name, duration, age_limit);

		if (film == NULL)
		{
			film = NewKino;
		}
		else
		{
			NewKino->next = film;
			film = NewKino;
		}
	}
};

void Cinema_park::Delete()
{
	IHall* NewHall = new IHall();
	NewHall = hall;
	hall = NewHall->next;
	delete NewHall;

	IKino* NewKino = new IKino();
	NewKino = film;
	film = NewKino->next;
	delete NewKino;

}

bool Cinema_park::Empty()
{
	if (film or hall) return false;
	else return true;
}

void Cinema_park::Clear()
{
	while (film) Delete();
	while (hall) Delete();
}

void Cinema_park::View()
{
	IHall* Hall = hall;
	IKino* Kino = film;

	Kino->View();
	Hall->View();
}

void Cinema_park::Purchase_Ticket(int number_hall, int seats)
{
	int index = 1;
	for (IHall* Hall = hall; Hall != 0; Hall = Hall->next, index++)
	{
		Hall->Purchase(number_hall, seats);

	}
}

void Cinema_park::Out_info_seat(int number_hall)
{
	int full_hall = 0;
	IHallDecorator* Decorator = decorator;
	Decorator->Out_info_seat(Decorator, number_hall);
}

bool Cinema_park::Check_purchase_ticket(int number_hall, int seats)
{
	IHall* Hall = hall;
	if (Hall->Purchase_ticket_check(number_hall, seats) == 1)
		return 1;
	return 0;
}