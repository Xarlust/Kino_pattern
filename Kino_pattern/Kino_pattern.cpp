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
	bool reservation = false;	//бронь места
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
		NewTicket->reservation = false;
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
			NewTicket->reservation = false;
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
		printf("index %d: number_hall'%d' \n seats: '%d' \n ", index, Ticket->number_hall, Ticket->seats);
}

class Cinema_park : public IKino {
private:
	IHall* hall;
	IKino* film;
public:
	void Create(int number_hall, int number_seats, char name, char duration, int age_limit);
	void Delete();
	bool Empty();
	void Clear();
	void View();
	Cinema_park()
	{
		hall = 0;
		film = 0;
	}
	~Cinema_park()
	{
		Clear();
	}
};

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




int main()
{
	setlocale(LC_ALL, "Russian");
	Cinema_park cinema;
	int choice, age_limit, name, duration, exit = 0;


	/*do
	{
		do {
			printf("==================\n1.-add film \n2.-del last film \n3.-Clear film\n4.-is empty film\n5.-view all film\n0.-Exit\nAction:");
			scanf("%d", &choice);
		} while (choice < 0 || choice>5);

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
			film.Create(name, duration, age_limit);
			printf("add completed!\n");
			break;

		case 2:
			if (film.Empty())
				printf("empty!\ndelete not execute!\n");
			else
			{
				film.Delete();
				printf("delete last completed!\n");
			}
			break;

		case 3:
			film.Clear();
			printf("Film Clear!\n");
			break;
		
		case 4:
			if (film.Empty())
				printf("Stack empty!\n");
			else
				printf("Stack no empty!\n");
			break;

		case 5:
			printf("View all film\n");
			if (film.Empty())
				printf("empty!\n");
			else
				film.View();
			break;


		default:
			return 0;
		}

	} while (exit != 1); */

	return 0;
}