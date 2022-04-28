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
	IFilm* film;
public:
	void Create(char name, char duration, int age_limit);
	void Delete();
	bool Empty();
	void Clear();
	void View();
	IKino()
	{
		film = 0;
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

class ITicket {			//билет
private:
	int number_hall;	//номер зала
	int seats;          
	ITicket* next;

	friend class IHall;
};

class IHall {			//зал
private:
	ITicket* ticket;
	int reservation;
	int number_seats;	//кол. мест
	IHall* next;
public:
	void Create(int number_hall, int seats);
	void Create_full(int number_hall, int number_seats);
	void Delete();
	bool Empty();
	void Clear();
	void View();
};

void IHall::Create(int number_hall, int seats)
{
	ITicket* NewTicket = new ITicket();
	if (NewTicket)
	{
		NewTicket->number_hall = number_hall;
		NewTicket->seats = seats;
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
	for (index; index != number_seats; index++)
	{
		ITicket* NewTicket = new ITicket();
		if (NewTicket)
		{
			NewTicket->number_hall = number_hall;
			NewTicket->seats = index;
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
		NewTicket = NewTicket->next;
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
		printf("index %d: number_hall'%d' \n seats: '%d' \n", index, Ticket->number_hall, Ticket->seats);
}

class Cinema_park : public IKino {
private:
	IHall* hall;
	IKino* film;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	IKino film;
	int choice, age_limit, name, duration, exit = 0;
	//char name, duration = 0;
	IHall ticket;
	printf("Film:");
	scanf("%d", &name);
	printf("Duration:");
	scanf("%d", &duration);
	printf("Age_limit:");
	scanf("%d", &age_limit);
	ticket.Create_full(name, duration);
	printf("add completed!\n");
	ticket.View();
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