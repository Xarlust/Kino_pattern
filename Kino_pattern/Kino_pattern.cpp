#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

class IFilm {			//фильм
private:
	char name;
	char duration;
	int age_limit;
	IFilm* next;

	friend class IKino;
};


class IKino {
private:
	IFilm* film ;
	IKino* next;
public:
	void Create(char name, char duration, int age_limit);
	void Delete();
	bool Empty();
	void Clear();
	void View();
	IKino()
	{
		film = 0;
		next = 0;
	}
	~IKino()
	{
		Clear();
	}

	friend class Cinema_park;
};

void IKino::Create(char name, char duration, int age_limit)
{
	IFilm* NewFilm = new IFilm();
	if (NewFilm)
	{
		NewFilm->name = name;
		NewFilm->duration = duration;
		NewFilm->age_limit = age_limit;
		NewFilm->next = 0;

		if (film == NULL)
		{
			film = NewFilm;
		}
		else
		{
			NewFilm->next = film;
			film = NewFilm;
		}
	}
}

void IKino::Delete()
{
	IFilm* NewFilm = new IFilm();
	NewFilm = film;
	film = NewFilm->next;
	delete NewFilm;
}

bool IKino::Empty()
{
	if (film) return false;
	else return true;
}

void IKino::Clear()
{
	while(film) Delete();
}

void IKino::View()
{
	int index = 1;
	for (IFilm* Film = film; Film!= 0; Film = Film->next, index++)
		printf("Фильм %d: '%c' \n Время: '%c' \n Возрастное ограничение: '%d' \n", index, Film->name , Film->duration, Film->age_limit);
}

class ITicket {					//билет
private:
	int number_hall;			//номер зала
	int seats;					//место
	bool reservation = 0;	//бронь места
	ITicket* next;

	friend class IHall;
};

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
	for (index; index != number_seats+1; index++)
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
	for (ITicket* Ticket = ticket; Ticket != 0; Ticket = Ticket->next , index++)
		printf("number_hall'%d' \n seats : '%d' \n ",  Ticket->number_hall, Ticket->seats);
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
		if (Ticket->reservation == 0 and Ticket->number_hall ==number_hall)
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

class Cinema_park : public IKino {
private:
	IHall* hall;
	IKino* film;
	Cinema_park()
	{
		hall = 0;
		film = 0;
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
	void Purchase_Ticket(int number_hall,int seats);//покупка билетов
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
	IHall* Hall = hall;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	full_hall = Hall->Full_hall(number_hall);
	if (full_hall != 0) {
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		printf("В зале №%d:\n свободно %d мест \n ", number_hall, full_hall);
	}
	else
	{
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		printf("Зал полон!!");
	}
}

bool Cinema_park::Check_purchase_ticket(int number_hall, int seats)
{
	IHall* Hall = hall;
	if (Hall->Purchase_ticket_check(number_hall, seats) == 1)
		return 1;
	return 0;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int choice, age_limit, number_hall, number_seats,seats, exit = 0;
	char name, duration = 0;

	do
	{
		do {
			printf("==================\n1.-add hall + film \n2.-del last hall + film \n3.-Clear full hall + film\n4.-is empty hall + film\n5.-view all hall + film\n6.-Purchase_Ticket\n7.-Out info seat to hall\n0.-Exit\nAction:");
			scanf("%d", &choice);
		} while (choice < 0 || choice>7);

		switch (choice)
		{
		case 0:
			exit = 1;
			break;

		case 1:
			printf("Film:");
			scanf("%s", &name);
			printf("Duration:");
			scanf("%s", &duration);
			printf("Age_limit:");
			scanf("%i", &age_limit);
			printf("number_hall:");
			scanf("%i", &number_hall);
			printf("number_seats:");
			scanf("%i", &number_seats);
			Cinema_park::getInstance()->Create(number_hall, number_seats, name, duration, age_limit);
			printf("add completed!\n");
			break;
		case 2:
			if (Cinema_park::getInstance()->Empty())
				printf("empty!\ndelete not execute!\n");
			else
			{
				Cinema_park::getInstance()->Delete();
				printf("delete last completed!\n");
			}
			break;

		case 3:
			Cinema_park::getInstance()->Clear();
			printf("Cinema Clear!\n");
			break;
		
		case 4:
			if (Cinema_park::getInstance()->Empty())
				printf("Empty Cinema!\n");
			else
				printf("Cinema no empty!\n");
			break;

		case 5:
			printf("View all film\n");
			if (Cinema_park::getInstance()->Empty())
				printf("empty!\n");
			else
				Cinema_park::getInstance()->View();
			break;
		case 6:
			printf("number_hall:");
			scanf("%i", &number_hall);
			printf("seats:");
			scanf("%i", &seats);
			if(Cinema_park::getInstance()->Check_purchase_ticket(number_hall, seats) == 0)
					Cinema_park::getInstance()->Purchase_Ticket(number_hall, seats);
			break;
		case 7:
			printf("number_hall:");
			scanf("%i", &number_hall);
			Cinema_park::getInstance()->Out_info_seat(number_hall);
			break;
		default:
			return 0;
		}

	} while (exit != 1); 

	return 0;
}