/******************************************************************************************************************
* Programmer: Jaehong Lee
* Class: CptS 122, Fall 2023; Lab Section 3 (Tuesday 1:30PM - 4:20PM)
* Programming Assignment: PA3
* Date: September 30, 2023
* Description: This PA assignment is continuation of creating a Digital Music Manager program. Several new functionalities
* such as insert, delete, sort, shuffle have been added to the device. Also, on a sperate file: test.c, test.h,
* test functions for insertion, deletion and shuffle have been created as well in order to check for the correct
* implementation of each function.
******************************************************************************************************************/


#include "function.h"

#include "test.h";

int main(void)
{

	srand(time(0));
	//test_insert_func();
	//test_delete_func();
	//test_shuffle_func();
	
	//putchar('\n');
	//system("pause");

	//Enter you clicked right before running into fgets func. '\n' automatically filled in fgets that's why
	// it does not wait for the user input. simply way of solving this issue.
	//char testing_line[10];
	//printf("\nEnter a string input: ");
	//fgets(testing_line, 100, stdin);
	//printf("\n\nString output %s\n", testing_line);
	//putchar('\n');
	//system("pause");

	int menu = 0;
	bool exit = false;;
	FILE* infile = fopen("musicPlayList.csv", "r");
	Node* pList = NULL; //head ptr initially pointing to NULL


	int play_order_array[9] = { 0 };

	do
	{
		printf("\n\n*********************************************************\n\n");
		printf("\n\nWelcome to the Digital Music Manager!!");
		printf("\n\n\nMenu of options:\n\n"); //PA2
		printf("(1) load\n"); //pa2
		printf("(2) store\n"); //pa2
		printf("(3) display\n"); //pa2
		printf("(4) insert\n");
		printf("(5) delete\n");
		printf("(6) edit\n"); //pa2
		printf("(7) sort\n");
		printf("(8) rate\n"); //pa2
		printf("(9) play\n"); //pa2
		printf("(10) shuffle\n");
		printf("(11) exit\n"); //pa2
		printf("\n\n*********************************************************\n\n");
		printf("Enter the number 1 ~ 11 to run your music manager device: ");
		scanf("%d", &menu);



		switch (menu)
		{
		case 1:
			system("cls");
			load_func(infile, &pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 2:
			system("cls");
			FILE* outfile = fopen("musicPlayList.csv", "w"); //writing mode!
			store_func(outfile, pList);
			fclose(outfile);
			printf("\nThe updated Music Playlisted stored on the musicPlayList.csv file complete!");
			system("pause");
			system("cls");
			break;

		case 3:
			system("cls");
			display_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 4:
			system("cls");
			insert_at_front_func(&pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 5:
			system("cls");
			delete_func(&pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 6:
			system("cls");
			edit_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 7:
			system("cls");
			sort_number_times_played(&pList);
			//printList(pList);
			//choose_sorting_methods(&pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 8:
			system("cls");
			rate_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 9:
			system("cls");
			play_func(pList);
			putchar('\n');
			system("pause");
			system("cls");
			break;

		case 10:
			system("cls");
			making_random_order_array(&pList, play_order_array, 9);
			shuffle_func(&pList, play_order_array, 9);
			break;

		case 11:
			exit = exit_func(exit);
			break;

		}

	} while (!exit);

	fclose(infile);


	return 0;
}