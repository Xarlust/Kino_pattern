#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include "Cinema_park.h"




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
			//Cinema_park::getInstance()->											//вызов декоратора
 			Cinema_park::getInstance()->Out_info_seat(number_hall);
			break;
		default:
			return 0;
		}

	} while (exit != 1); 

	return 0;
}