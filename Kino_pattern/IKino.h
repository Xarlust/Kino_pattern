#pragma once
#include <iostream>
#include "IFilm.h"

class IKino {
private:
	IFilm* film;
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
	while (film) Delete();
}

void IKino::View()
{
	int index = 1;
	for (IFilm* Film = film; Film != 0; Film = Film->next, index++)
		printf("Фильм %d: '%c' \n Время: '%c' \n Возрастное ограничение: '%d' \n", index, Film->name, Film->duration, Film->age_limit);
}