#pragma once
#include <iostream>

class IFilm {			//�����
private:
	char name;
	char duration;
	int age_limit;
	IFilm* next;

	friend class IKino;
};