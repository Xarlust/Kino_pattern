#pragma once
#include <iostream>
#include "ITicket.h"


class IHall {			//зал
private:
	ITicket* ticket;
	int number_seats;	//кол. мест
	IHall* next;

public:
	void Create(int number_hall, int seats);
	void Create_full(int number_hall, int number_seats);
	void Delete();
	bool Empty();
	void Clear();
	void View();
	void Purchase(int number_hall, int seats);
	int  Full_hall(int number_hall);
	bool Purchase_ticket_check(int number_hall, int seats);
	void Out_info_seat( int number_hall);

	IHall()
	{
		ticket = 0;
		number_seats = 0;
		next = 0;
	}
	~IHall()
	{
		Clear();
	}

	friend class Cinema_park;

};


void IHall::Create(int number_hall, int seats)
{
	ITicket* NewTicket = new ITicket();
	if (NewTicket)
	{
		NewTicket->number_hall = number_hall;
		NewTicket->seats = seats;
		NewTicket->reservation = 0;
		NewTicket->next = 0;

		if (ticket == NULL)
		{
			ticket = NewTicket;
		}
		else
		{
			NewTicket->next = ticket;
			ticket = NewTicket;
		}
	}
}

void IHall::Create_full(int number_hall, int number_seats)
{
	int index = 1;
	for (index; index != number_seats + 1; index++)
	{
		ITicket* NewTicket = new ITicket();
		if (NewTicket)
		{
			NewTicket->number_hall = number_hall;
			NewTicket->seats = index;
			NewTicket->reservation = 0;
			NewTicket->next = 0;

			if (ticket == NULL)
			{
				ticket = NewTicket;
			}
			else
			{
				NewTicket->next = ticket;
				ticket = NewTicket;
			}

		}

	}
}

void IHall::Delete()
{
	ITicket* NewTicket = new ITicket();
	NewTicket = ticket;
	ticket = NewTicket->next;
	delete NewTicket;
}

bool IHall::Empty()
{
	if (ticket) return false;
	else return true;
}

void IHall::Clear()
{
	while (ticket) Delete();
}

void IHall::View()
{
	int index = 1;
	for (ITicket* Ticket = ticket; Ticket != 0; Ticket = Ticket->next, index++)
		printf("number_hall'%d' \n seats : '%d' \n ", Ticket->number_hall, Ticket->seats);
}

void IHall::Purchase(int number_hall, int seats)
{
	int index = 1;
	for (ITicket* Ticket = ticket; Ticket != 0; Ticket = Ticket->next, index++)
	{
		if ((Ticket->number_hall == number_hall) and (Ticket->seats == seats))
		{
			Ticket->reservation = 1;
			printf("Куплен билет с hall %d \n seats: '%d' \n ", Ticket->number_hall, Ticket->seats);
		}
	}
}

int IHall::Full_hall(int number_hall)
{
	int index = 1;
	int seats_empty = 0;
	for (ITicket* Ticket = ticket; Ticket != 0; Ticket = Ticket->next, index++)
	{
		if (Ticket->reservation == 0 and Ticket->number_hall == number_hall)
			seats_empty++;
	}
	return seats_empty;
}

bool IHall::Purchase_ticket_check(int number_hall, int seats)
{
	int index = 0;
	for (ITicket* Ticket = ticket; Ticket != 0; Ticket = Ticket->next, index++)
	{
		if ((Ticket->number_hall == number_hall) and (Ticket->seats == seats) and Ticket->reservation == 1)
		{
			printf("невозможно купить билет в hall %d \n с seats: '%d' \n ", Ticket->number_hall, Ticket->seats);
			return 1;
		}
	}
	return 0;

}

void IHall::Out_info_seat( int number_hall)
{
	int full_hall = 0;
	full_hall = Full_hall(number_hall);
	if (full_hall != 0) {
		printf("В зале №%d:\n свободно %d мест \n ", number_hall, full_hall);
	}
	else
	{
		printf("Зал полон!!");
	}
}