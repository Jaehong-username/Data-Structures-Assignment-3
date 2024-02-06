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



/********************************************************************************************************************
* Function: load_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/17/2023
* Description: This function loads data from csvfile into a data of struct, which is stored in doubled linked lists.
* Input parameters: infile: a pointer to the musicPlayList.csv file for reading what's inside of the file
*                           before loading it on the double linked lists.
*                   pList: a pointer to the header pointer of the linked list. Used double star signs, so that
*                          dereferencing the memory address value is possible.
* Returns: Nothing
* Preconditions: musicPlayList.csv File must be opened successfully to read the csv data before implementing the function.
*********************************************************************************************************************/
void load_func(FILE* infile, Node** pList)
{

	if (infile != NULL) //csv file opened successfully
	{
		//Node* pPrev = NULL;
		//Node* pCur = *pList;

		int how_many_songs = 1;
		char line[200];
		char name_with_double_quotes[200];

		while (fgets(line, 200, infile) != NULL)
		{

			Node* pMem = malloc(sizeof(Node));

			if (pMem != NULL) //node created successfully
			{
				if (line[0] == '\"')
				{
					name_with_double_quotes[0] = '"';
					strcpy(&name_with_double_quotes[1], strtok(&line[1], "\""));

					for (int i = 0;; i++)
					{
						if (name_with_double_quotes[i] == '\0')
						{
							name_with_double_quotes[i] = '"';
							name_with_double_quotes[i + 1] = '\0';
							break;
						}
					}

					strcpy(pMem->data.artist, name_with_double_quotes);
					//strcpy(pMem->data.artist, strtok(&line[1], "\"")); //this would output withot double quotes
				}

				else if (line[0] != '\"')
				{
					strcpy(pMem->data.artist, strtok(line, ","));
				}
				//strtok returns char* //first filling out the data first!!
				//const char* last_name = strtok(line, "\n,\":"); //delimiter: \n , "
				//const char* first_name = strtok(NULL, "\n,\":");
				//strcat(last_name, first_name);                       //how can I ignore ,????????????????????
				//strcpy(pMem->data.artist, last_name);
				strcpy(pMem->data.album_title, strtok(NULL, "\n,:"));
				strcpy(pMem->data.song_title, strtok(NULL, "\n,:"));
				strcpy(pMem->data.genre, strtok(NULL, "\n,\":"));
				pMem->data.song_length.minutes = atoi(strtok(NULL, "\n,:"));
				pMem->data.song_length.seconds = atoi(strtok(NULL, "\n,:"));
				pMem->data.numbers_times_played = atoi(strtok(NULL, "\n,:"));
				pMem->data.rating = atoi(strtok(NULL, "\n,:"));

				pMem->pNext = NULL;
				pMem->pPrev = NULL; //now this node has two dangling pointers pointing to NULL
			}


			//insertion in the first nodetakes place!!!

			if (*pList == NULL) // if if there is no preexisting node inserting in the first position.
			{
				*pList = pMem;
			}

			else if (*pList != NULL) //inserting in the first position
			{
				pMem->pNext = *pList;
				(*pList)->pPrev = pMem;
				*pList = pMem;
			}

		}

		printf("\n\nAll the songs from the csvfile are loaded on the Digital Music Manager successfully!!");

		//this comment goes to the display function!!!
		//Node* pCur = *pList; //pcur pointing to the head pointer right now.

		//while (pCur != NULL)
		//{
		//	printf("*******************************Music %d*******************************\n\n", how_many_songs);
		//	printf("Artist: %s\n", pCur->data.artist); //pMem->data.artist not defined error!!!!
		//	printf("Album Title: %s\n", pCur->data.album_title);
		//	printf("Song Title: %s\n", pCur->data.song_title);
		//	printf("Genre: %s\n", pCur->data.genre);
		//	printf("Song Duration Minutes: %d\n", pCur->data.song_length.minutes);
		//	printf("Song Duration Seconds: %d\n", pCur->data.song_length.seconds);
		//	printf("Number Time Played: %d\n", pCur->data.numbers_times_played);
		//	printf("Rating: %d\n\n", pCur->data.rating);
		//	printf("**********************************************************************\n\n");
		//	printf("                                     :\n");
		//	printf("                                     :\n");
		//	printf("                                     :\n");
		//	printf("                                     :\n\n");

		//	how_many_songs++;
		//	pCur = pCur->pNext;

		//}

	}

	else if (infile == NULL) //file never opened
	{
		printf("\n\nError occured in uploading music file. Please doublecheck your file");
		return;
	}

}




/********************************************************************************************************************
* Function: display_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function displays what's loaded inside of the linked lists in two different ways.
*              (1): Priting all the records of songs on the playlist. (2): Printing all records that match an artist typed.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void display_func(Node* pList)
{
	int how_many_songs = 1;
	//Node* pCur = pList; //pcur pointing to the head pointer right now.
	int method_choice = 0;

	char artist_name[100];
	//char* artist_name = malloc(sizeof(char) * 100);

	if (pList == NULL) //pointing to nothing (no preexisting nodes on the list)
	{
		printf("\n\nNo songs on the playlist!");
		printf("\n\nOr Make sure to load the songs first (go to menu 1 first to load the songs on the Digital Music Manager!)");
		return;
	}

	printf("\n\nFor display method, which one would you like to choose? Enter 1 or 2");
	printf("\n\n1. Print all records\n\n\n");
	printf("2. Print all records that match an artist\n\n");
	scanf(" %d", &method_choice);

	if (method_choice == 1)
	{
		system("cls");
		printf("\n\n\nChose Method 1: Print all records\n\n\n");

		printList(pList);

		printf("\n\n\nALright! These are all the songs displayed from the csv file!\n\n\n");

		return;
	}

	else if (method_choice == 2)
	{
		system("cls");
		printf("\n\n\nChose Method 2: Print all records that match an artist\n\n\n");

		search_func(pList, artist_name);

		printf("\n\n\nALright, the is the search result based on the song records from the csv file!\n\n\n");

		return;
	}

}




/********************************************************************************************************************
* Function: printList()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function displays all records of songs in the playlist from the Music Manager device.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void printList(Node* pList)
{
	Node* pCur = pList;
	int how_many_songs = 1;

	while (pCur != NULL)
	{
		printf("*******************************Music %d*******************************\n\n", how_many_songs);
		printf("Artist: %s\n", pCur->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", pCur->data.album_title);
		printf("Song Title: %s\n", pCur->data.song_title);
		printf("Genre: %s\n", pCur->data.genre);
		printf("Song Duration Minutes: %d\n", pCur->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", pCur->data.song_length.seconds);
		printf("Number Time Played: %d\n", pCur->data.numbers_times_played);
		printf("Rating: %d\n\n", pCur->data.rating);
		printf("**********************************************************************\n\n");
		printf("                                     :\n");
		printf("                                     :\n");
		printf("                                     :\n");
		printf("                                     :\n\n");

		how_many_songs++;
		pCur = pCur->pNext;

	}


}






/********************************************************************************************************************
* Function: search_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: THis function gives a search result of song based on the artist name from an user input.
*              Linked node pointer will traverse through each one untill the end of the node. In the meantime,
*              If the node pointer finds the match, this will printout what's stored in that particular node.
* Input parameters: pList: a pointer to the head node in the double linked lists.
*                   artist_name: This array accepts an array of chars based on the user input using fgets and stdin.
* Returns: This function returns the number of the songs found based on artist name match.
* Postconditions: If no song has been found in the list, this will print out "No songs found!".
*********************************************************************************************************************/
int search_func(Node* pList, char artist_name[100])
{

	Node* pCur = pList;
	int how_many_songs = 0;
	//char artist_name[100];
	printf("Type the name of the artist, whose songs from the Digital Music Manager\n");
	printf("\nLast name, First name order!!! Comma also matters!\n");


	printf("\n\nArtist name:");
	fgets(artist_name, 100, stdin);
	fgets(artist_name, 100, stdin);

	for (int i = 0;; i++)
		//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
	{
		if (artist_name[i] == '\n') //\n must right before the null terminator added by the fgets!
		{
			artist_name[i] = '\0';
			break;
		}
	}

	printf("\nSearching for: %s\n\n", artist_name);

	//char* artist_name = malloc(sizeof(char) * 100);
	//printf("\n\nArtis name: ");
	//scanf("%99[^\n]", artist_name);
	//printf("\n\nSearching for: %s\n", artist_name);

	while (pCur != NULL)
	{

		if (strcmp(pCur->data.artist, artist_name) == 0)  //gotta initialize this!!! by *pCur = pList;
		{
			how_many_songs++; //here so that first song index will be 1 instead of 0
			printf("*******************************Music %d*******************************\n\n", how_many_songs);
			printf("Artist: %s\n", pCur->data.artist); //pMem->data.artist not defined error!!!!
			printf("Album Title: %s\n", pCur->data.album_title);
			printf("Song Title: %s\n", pCur->data.song_title);
			printf("Genre: %s\n", pCur->data.genre);
			printf("Song Duration Minutes: %d\n", pCur->data.song_length.minutes);
			printf("Song Duration Seconds: %d\n", pCur->data.song_length.seconds);
			printf("Number Time Played: %d\n", pCur->data.numbers_times_played);
			printf("Rating: %d\n\n", pCur->data.rating);
			printf("**********************************************************************\n\n");
			printf("                                     :\n");
			printf("                                     :\n");
			printf("                                     :\n");
			printf("                                     :\n\n");
			//how_many_songs++;
			//pCur = pCur->pNext; //I cannot put it here! otherwise the loop never ends without traversign
			//if the first node doesn't match with the name.
		}

		pCur = pCur->pNext;

	}

	if (how_many_songs == 0) printf("\n\nNo songs found!");

	return how_many_songs;
}







/********************************************************************************************************************
* Function: store_func()
* Date Created: 9/17/2023
* Date Last Modified: 9/18/2023
* Description: This function will store all records of the songs that have been edited up to date on the playlist
*              into the outfile csv file named musicPlaylist.
* Input parameters: outfile: a output file pointer to the musicPlayList.csv in the writing mode.
*                   pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
* Preconditions: musicPlayList.csv file in the writing mode must be opened, so that what's inside of the doubled linked list
*                can be stored in the csv file through the stream.
* Postcondtions: musicPlayList.csv file in the writing mode must be closed to get access to the output.
*********************************************************************************************************************/
void store_func(FILE* outfile, Node* pList)
{
	//FILE* outfile = fopen("musicPlayList.csv", "w"); //I took it out to the main

	Node* pCur = pList;

	while (pCur->pNext != NULL)
	{
		pCur = pCur->pNext;
	}

	char integer_to_string[10];

	while (pCur != NULL)
	{
		fputs(pCur->data.artist, outfile);
		fputc(',', outfile);
		fputs(pCur->data.album_title, outfile);
		fputc(',', outfile);
		fputs(pCur->data.song_title, outfile);
		fputc(',', outfile);
		fputs(pCur->data.genre, outfile);
		fputc(',', outfile);
		//Why _itoa not working?????
		_itoa(pCur->data.song_length.minutes, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc(':', outfile);
		_itoa(pCur->data.song_length.seconds, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc(',', outfile);
		_itoa(pCur->data.numbers_times_played, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc(',', outfile);
		_itoa(pCur->data.rating, integer_to_string, 10);
		fputs(integer_to_string, outfile);
		fputc('\n', outfile);


		pCur = pCur->pPrev;
	}

	//fclose(outfile);  //I took it out to the main

	return;
}





/********************************************************************************************************************
* Function: edit_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function makes an user able to modify all attributes of a certain song searched by the user input.
*              After the modification, the edited values will replaced the old ones in the node of the field Record Struct.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void edit_func(Node* pList)
{
	Node* count_ptr = pList;
	int how_many_songs_found = 0;
	char song_search[100] = "";
	Node* search_ptr = pList;
	int new_rating = 0;
	bool again = false;

	char edited_artist[50] = "";
	char edited_album_title[50] = "";
	char edited_song_title[50] = "";
	char edited_genre[20] = "";
	int edited_song_length_minutes = 0; //struct duration song_length; ?? what's the difference??
	int edited_song_length_seconds = 0;
	int edited_numbers_times_played = 0;
	int edited_rating = 0; // 1 ~ 5

	char artist_name[100];

	if (pList == NULL) //pointing to nothing (no preexisting nodes on the list)
	{
		printf("\n\nNo songs on the playlist! for rating");
		printf("\n\nOr Make sure to load the songs first (go to menu 1 first to load the songs on the Digital Music Manager!)");
		return;
	}

	else if (pList != NULL) //songs loaded
	{
		how_many_songs_found = search_func(pList, artist_name);

		if (how_many_songs_found == 0)
		{
			printf("\n\nNo songs found matched with the name. Make sure to check the name of the song! before rating");
			return;
		}

		printf("\nALright this is the result we found for you!");


		if (how_many_songs_found != 1) // at least more than one song from the same artist
		{
			printf("\nWe found more than one song from the same artist!");
			printf("\nWhich song would you like to choose for editing the rating?");

			printf("\n\nType the song name:\n");
			fgets(song_search, 100, stdin);
			//fgets(song_search, 100, stdin); //only one line of fgets needed.

			for (int i = 0;; i++)
				//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
			{
				if (song_search[i] == '\n') //\n must right before the null terminator added by the fgets!
				{
					song_search[i] = '\0';
					break;
				}
			}

			while (strcmp(search_ptr->data.song_title, song_search) != 0)
			{
				search_ptr = search_ptr->pNext;
			}

		}

		//now search ptr currently pointing to the first node, need to get it to  move!
		while (strcmp(search_ptr->data.artist, artist_name) != 0)
		{
			search_ptr = search_ptr->pNext;
		}

		system("cls");
		printf("\n\nWe found the song match!\n\n");
		printf("\n\nThis is the record information within the manager device for this song\n\n");


		printf("**********************************************************************\n\n");
		printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", search_ptr->data.album_title);
		printf("Song Title: %s\n", search_ptr->data.song_title);
		printf("Genre: %s\n", search_ptr->data.genre);
		printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
		printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
		printf("Rating: %d\n\n", search_ptr->data.rating);
		printf("**********************************************************************\n\n");


		///////////editing takes place
		printf("\nCurrent Artist: %s", search_ptr->data.artist);
		printf("\n\nPlease type an edited artist:");
		fgets(edited_artist, 50, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_artist[i] == '\n')
			{
				edited_artist[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.artist, edited_artist);
		printf("\nEdited Artist: %s\n\n\n", search_ptr->data.artist);


		printf("\nCurrent Album Title: %s", search_ptr->data.album_title);
		printf("\n\nPlease type an edited album title:");
		fgets(edited_album_title, 50, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_album_title[i] == '\n')
			{
				edited_album_title[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.album_title, edited_album_title);
		printf("\nEdited Album Title: %s\n\n\n", search_ptr->data.album_title);

		printf("\nCurrent Song Title: %s", search_ptr->data.song_title);
		printf("\n\nPlease type an edited song title:");
		fgets(edited_song_title, 50, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_song_title[i] == '\n')
			{
				edited_song_title[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.song_title, edited_song_title);
		printf("\nEdited Song Title: %s\n\n\n", search_ptr->data.song_title);

		printf("\nCurrent Genre: %s", search_ptr->data.genre);
		printf("\n\nPlease type an edited genre:");
		fgets(edited_genre, 20, stdin);
		for (int i = 0;; i++) //gotta get rid of '\n' newline char from the fgets for the proper search.
		{
			if (edited_genre[i] == '\n')
			{
				edited_genre[i] = '\0';
				break;
			}
		}
		strcpy(search_ptr->data.genre, edited_genre);
		printf("\nEdited Genre: %s\n\n\n", search_ptr->data.genre);

		printf("\nCurrent Song Minutes: %d", search_ptr->data.song_length.minutes);
		printf("\n\nPleas type an edited song minute:");
		scanf("%d", &edited_song_length_minutes);
		search_ptr->data.song_length.minutes = edited_song_length_minutes;
		printf("\nEdited Song Minutes: %d\n\n\n", search_ptr->data.song_length.minutes);

		printf("\nCurrent Song Seconds: %d", search_ptr->data.song_length.seconds);
		printf("\n\nPleas type an edited song seconds:");
		scanf("%d", &edited_song_length_seconds);
		search_ptr->data.song_length.seconds = edited_song_length_seconds;
		printf("\nEdited Song Seconds: %d\n\n\n", search_ptr->data.song_length.seconds);

		printf("\nCurrent Number Times Played: %d", search_ptr->data.numbers_times_played);
		printf("\n\nPleas type an edited numbers times played:");
		scanf("%d", &edited_numbers_times_played);
		search_ptr->data.numbers_times_played = edited_numbers_times_played;
		printf("\nEdited Number Times Played: %d", edited_numbers_times_played);

		do
		{
			again = false;
			printf("\nCurrent Rating: %d", search_ptr->data.rating);
			printf("\n\nPleas type an edited rating:");
			scanf("%d", &edited_rating);

			if (edited_rating == 1 || edited_rating == 2 || edited_rating == 3 ||
				edited_rating == 4 || edited_rating == 5)
			{
				again = false;
				search_ptr->data.rating = edited_rating;
				printf("\nEdited Rating: %d", edited_rating);

			}

			else
			{
				again = true;
				printf("\n\nInvalid Rating! The rating number ranges from 1 to 5! Please type your rating again!");
			}
		} while (again == true);


		//what's the whole point of making the rating function?????????????????????????????


		printf("\n\n\n\n\nTHis is the edited version for this song!\n\n");
		printf("**********************************************************************\n\n");
		printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", search_ptr->data.album_title);
		printf("Song Title: %s\n", search_ptr->data.song_title);
		printf("Genre: %s\n", search_ptr->data.genre);
		printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
		printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
		printf("Rating: %d\n\n", search_ptr->data.rating);
		printf("**********************************************************************\n\n");



		return;
	}
}


/********************************************************************************************************************
* Function: rate_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/18/2023
* Description: This function enables an user to exaclusively access to the rating of the song selected from user input
*              and modifies the current rating. Then, the updated rating replaces old value in the node of the
*              field Record Struct.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void rate_func(Node* pList)
{

	Node* count_ptr = pList;
	int how_many_songs_found = 0;
	char song_search[100];
	Node* search_ptr = pList;
	Node* another_search_ptr = pList;
	int new_rating = 0;
	bool again = false;
	char artist_name[100];

	if (pList == NULL) //pointing to nothing (no preexisting nodes on the list)
	{
		printf("\n\nNo songs on the playlist! for rating");
		printf("\n\nOr Make sure to load the songs first (go to menu 1 first to load the songs on the Digital Music Manager!)");
		return;
	}

	else if (pList != NULL) //songs loaded
	{
		how_many_songs_found = search_func(pList, artist_name);

		if (how_many_songs_found == 0)
		{
			printf("\n\nNo songs found matched with the name. Make sure to check the name of the song! before rating");
			return;
		}

		printf("\nALright this is the result we found for you!");

		/*while (count_ptr != NULL)
		{
			how_many_songs_found++;
			count_ptr = pList->pNext;
		}*/

		if (how_many_songs_found != 1) // at least more than one song from the same artist
		{
			printf("\nWe found more than one song from the same artist!");
			printf("\nWhich song would you like to choose for editing the rating?");

			printf("\n\nType the song name:");
			fgets(song_search, 100, stdin);
			//fgets(song_search, 100, stdin); why is it here only one line of fgets needed!!??????????????????????

			for (int i = 0;; i++)
				//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
			{
				if (song_search[i] == '\n') //\n must right before the null terminator added by the fgets!
				{
					song_search[i] = '\0';
					break;
				}
			}

			while (strcmp(another_search_ptr->data.song_title, song_search) != 0)
			{
				another_search_ptr = another_search_ptr->pNext;
			}

			search_ptr = another_search_ptr;
		}


		//now search ptr currently pointing to the first node, need to get it to  move!
		while (strcmp(search_ptr->data.artist, artist_name) != 0)
		{
			search_ptr = search_ptr->pNext;
		}


		printf("\nSearched the song named: %s", search_ptr->data.song_title);
		printf("\nCurrent Rating for this song: %d", search_ptr->data.rating);

		do
		{
			printf("\n\nWhich new rating would you like to give to this song?: ");
			scanf("%d", &new_rating);

			if (new_rating == 1 || new_rating == 2 || new_rating == 3 ||
				new_rating == 4 || new_rating == 5)
			{
				again = false;
				search_ptr->data.rating = new_rating;
				printf("\n\nNew rating for the song named  %s: %d", search_ptr->data.song_title, new_rating);
			}

			else
			{
				printf("\nRating ranges from 1 to 5 Please type your rating again!\n");
				again = true;
			}


		} while (again == true);

	}
}



/********************************************************************************************************************
* Function: play_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/17/2023
* Description: This function lets an user decide which song to start from on the playlist. Based on the order of the
*              double linked nodes, the starting pointer to the node will traver through each node all the way to the
*              end of the linked list.
* Input parameters: pList: a pointer to the head node in the double linked lists.
* Returns: Nothing
*********************************************************************************************************************/
void play_func(Node* pList)
{
	Node* search_ptr = pList;
	char song_search[100];
	//Node* search_ptr = pList;

	printf("\nPlaying music on your list!!");
	printf("\n\nWhich song do you want to start playinf on the list?: ");
	printf("\n\nSong name:");
	fgets(song_search, 100, stdin);
	fgets(song_search, 100, stdin); //here two lines of fgets needed!!!

	for (int i = 0;; i++)
		//gotta get rid of '\n' char since I pressed Enter key from the fgets function before comparing two strings.
	{
		if (song_search[i] == '\n') //\n must right before the null terminator added by the fgets!
		{
			song_search[i] = '\0';
			break;
		}
	}

	while (strcmp(search_ptr->data.song_title, song_search) != 0) //not found the match
	{
		if (search_ptr->pNext == NULL) //pointing to the last song but still a mismatch of the song.
		{
			printf("\nThe song not found on the playlist");
			return;
		}
		search_ptr = search_ptr->pNext;
	}

	printf("\n\nPlaying the music list starting from %s", search_ptr->data.song_title); //found the song

	while (search_ptr != NULL) //song will be played until the end of the playlist
	{
		search_ptr->data.numbers_times_played++;

		printf("\n\n**********************Currently Playing the song************************\n\n");
		printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
		printf("Album Title: %s\n", search_ptr->data.album_title);
		printf("Song Title: %s\n", search_ptr->data.song_title);
		printf("Genre: %s\n", search_ptr->data.genre);
		printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
		printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
		printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
		printf("Rating: %d\n\n", search_ptr->data.rating);
		printf("**********************************************************************\n\n");
		Sleep(1000);
		printf("                                     :\n");
		Sleep(1000);
		printf("                                     :\n");
		Sleep(1000);
		printf("                                     :\n");
		Sleep(1000);
		printf("                                     :\n\n");

		
		search_ptr = search_ptr->pNext;

		Sleep(3000);
		system("cls");

	}

	printf("\n\nThe end of the song playlist!");

}






/********************************************************************************************************************
* Function: exit_func()
* Date Created: 9/15/2023
* Date Last Modified: 9/15/2023
* Description: This function lets an user terminate the Digital Music Manager program successfully.
* Input parameters: exit: a boolean data type variable to indicate whether to exit or not to the exit function.
* Returns: This function returns boolean values if it returns true, this will end the Digital Music Manager program.
*********************************************************************************************************************/
bool exit_func(bool exit)
{
	int yes_or_no = 0;
	int invalid_input = 0;

	do
	{
		invalid_input = 0;
		system("cls");
		printf("\n\nAre you sure you want to exit? Enter 1 if yes enter 2 otherwise");
		printf("\n\n(1): Yes        (2): No\n\n");
		scanf(" %d", &yes_or_no);

		if (yes_or_no == 1)
		{
			printf("\n\nSee you next time!!!");
			exit = true;
			return exit;
		}

		else if (yes_or_no == 2)
		{
			system("cls");
			exit = false;
			return exit;
		}

		else
		{
			printf("\n\nMake sure to enter either 1 or 2!\n\n");
			system("pause");
			invalid_input = 1;

		}

	} while (invalid_input == 1);

}




/********************************************************************************************************************
* Function: insert_at_front_func()
* Date Created: 9/25/2023
* Date Last Modified: 9/29/2023
* Description: This function inserts a whole node for a new song at the first position in the double linked list.
* All the fields from the struct record will be based on the user input.
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void insert_at_front_func(Node** pList)
{
	Node* pMem = malloc(sizeof(Node));
	pMem->pNext = NULL;
	pMem->pPrev = NULL;
	//pMem->data = record;

	//int again = 0;

	char line[100];

	printf("\nThe new artist name to be inserted: ");
	fgets(line, 100, stdin);
	fgets(line, 100, stdin);
	for (int i = 0;; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
		
	}
	strcpy(pMem->data.artist, line);
	printf("\nArtist name: %s", pMem->data.artist);

	printf("\nThe new album title to be inserted: ");
	fgets(line, 100, stdin);
	for (int i = 0;; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}

	}
	strcpy(pMem->data.album_title, line);
	printf("\nAlbum title: %s", pMem->data.album_title);

	printf("\nThe new song title to be inserted: ");
	fgets(line, 100, stdin);
	for (int i = 0;; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}

	}
	strcpy(pMem->data.song_title, line);
	printf("\nSong title: %s", pMem->data.song_title);

	printf("\nThe new genre to be inserted: ");
	fgets(line, 100, stdin);
	for (int i = 0;; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}

	}
	strcpy(pMem->data.genre, line);
	printf("\nGenre: %s", pMem->data.genre);

	printf("\nThe new song length in minutes (only type numbers!): ");
	fgets(line, 100, stdin);
	pMem->data.song_length.minutes = atoi(line);
	printf("\nDuration of a song in minutes: %d", pMem->data.song_length.minutes);

	printf("\nThe new song length in seconds (only type numbers!): ");
	fgets(line, 100, stdin);
	pMem->data.song_length.seconds = atoi(line);
	printf("\nDuration of a song in seconds: %d", pMem->data.song_length.minutes);

	
		
	printf("\nThe number of times played for the new song: ");
	fgets(line, 100, stdin);
	pMem->data.numbers_times_played = atoi(line);
	printf("\nNumber of times played in the new song: %d", pMem->data.numbers_times_played);

	
	printf("\nThe rating for the new song: ");
	fgets(line, 100, stdin);
	pMem->data.rating = atoi(line);
	printf("\nThe rating for the new song: %d", pMem->data.rating);

	//doing the insertion at the front!

	if (*pList != NULL) //there are already pre existing nodes.
	{
		pMem->pNext = *pList;
		(*pList)->pPrev = pMem;
		*pList = pMem;
	}
	
	else //inserting the first node in the list
	{
		*pList = pMem;
	}
}



/********************************************************************************************************************
* Function: delete_func()
* Date Created: 9/25/2023
* Date Last Modified: 9/29/2023
* Description: This function deletes a whole node from the doubled linked list. Based on the user input of the
* song title, the program will find a node from the linked list that matches with the name of the song.
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void delete_func(Node** pList)
{
	char line[100];

	Node* search_ptr = *pList;

	if (*pList != NULL)
	{
		printf("\nPlease enter the song title you would like to have it removed from the playlist: ");
		fgets(line, 100, stdin);
		fgets(line, 100, stdin);
		for (int i = 0;; i++)
		{
			if (line[i] == '\n') //to remove the newline char with a null terminator.
			{
				line[i] = '\0';
				break; //make sure these codes are within the if statement!
			}
			//break; !! ow it is an infinite loop
		}

		//when deleting the first node
		while (strcmp((search_ptr->data).song_title, line) != 0)
		{
			search_ptr = search_ptr->pNext;
		}

		//out of the loop if found the match!
		if (search_ptr->pPrev == NULL && search_ptr->pNext != NULL)
		{
			*pList = search_ptr->pNext;
			search_ptr->pNext->pPrev = NULL;
			free(search_ptr); //will deallocated the node  pointed to by the address.
		}
		
		else if (search_ptr->pPrev == NULL && search_ptr->pNext == NULL)
		{
			*pList = search_ptr->pNext;
			free(search_ptr);
		}

		//deleting the node in the middle
		else if (search_ptr->pNext != NULL && search_ptr->pPrev != NULL)
		{
			search_ptr->pPrev->pNext = search_ptr->pNext;
			search_ptr->pNext->pPrev = search_ptr->pPrev;
			free(search_ptr);
		}

		//deleting the node at the end
		else if (search_ptr->pNext == NULL)
		{
			search_ptr->pPrev->pNext = NULL;
			free(search_ptr);
		}
	}

	else
	{
		printf("\nThe list is empty. There is nothing to delete!\n");
	}
	

}





/********************************************************************************************************************
* Function: sort_artist()
* Date Created: 9/27/2023
* Date Last Modified: 9/30/2023
* Description: This function sorts the current order of songs in the playlist based on Artist name (A to Z).
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void sort_artist(Node** pList) //A to Z
{

	Node* pCur1 = *pList;
	Node* pCur2 = (*pList)->pNext;

	char min_artist[100];
	Node* min_node_ptr = NULL;

	if (*pList != NULL)
	{
		while (pCur1->pNext != NULL)
		{
			strcpy(min_artist, pCur1->data.artist);
			min_node_ptr = pCur1;

			while (pCur2 != NULL)
			{
				if (min_artist[0] == '\"' && pCur2->data.artist[0] == '\"')
				{
					if (strcmp(&(pCur2->data.artist)[1], &min_artist[1]) < 0)
					{
						strcpy(min_artist, pCur2->data.artist);
						min_node_ptr = pCur2;
					}
				}

				else if (min_artist[0] == '\"' && pCur2->data.artist[0] != '\"')
				{
					if (strcmp(pCur2->data.artist, &min_artist[1]) < 0)
					{
						strcpy(min_artist, pCur2->data.artist);
						min_node_ptr = pCur2;
					}
				}

				else if (min_artist[0] != '\"' && pCur2->data.artist[0] == '\"')
				{
					if (strcmp(&(pCur2->data.artist)[1], min_artist) < 0)
					{
						strcpy(min_artist, pCur2->data.artist);
						min_node_ptr = pCur2;
					}
				}

				else if (min_artist[0] != '\"' && pCur2->data.artist[0] != '\"')
				{
					if (strcmp(pCur2->data.artist, min_artist) < 0)
					{
						strcpy(min_artist, pCur2->data.artist);
						min_node_ptr = pCur2;
					}
				}

				pCur2 = pCur2->pNext;
			}

			//Updating the list!!
			Record temp_record = pCur1->data;
			pCur1->data = min_node_ptr->data;
			min_node_ptr->data = temp_record;

			//updating the pointer
			pCur1 = pCur1->pNext;
			pCur2 = pCur1;
			pCur2 = pCur2->pNext;
		}
	}

	else printf("\nThere is no song to sort on the playlist!\n");
	
	//int index = 0;
	//Node* search_ptr = *pList;
	//Node* starting_ptr = *pList;
	//Record min_name_node = (*pList)->data;
	//Record temp_name_node = (*pList)->data; //a good idea to initialize???
	//strcmp(min_name_node.artist, (*pList)->data.artist);

	//while (starting_ptr->pNext->pNext != NULL)
	//{
	//	while (search_ptr->pNext != NULL)
	//	{
	//		if (strcmp(min_name_node.artist, search_ptr->data.artist) > 0)
	//		{
	//			min_name_node = search_ptr->data;
	//		}
	//		search_ptr = search_ptr->pNext;
	//	}

	//	search_ptr = *pList;

	//	temp_name_node = search_ptr->data;
	//	search_ptr->data = min_name_node;
	//	while (strcmp(search_ptr->data.artist, min_name_node.artist) != 0)
	//	{
	//		search_ptr = search_ptr->pNext;
	//	}

	//	search_ptr->data = temp_name_node;

	//	starting_ptr = starting_ptr->pNext;
	//	search_ptr = starting_ptr;
	//}


}




/********************************************************************************************************************
* Function: sort_album_title()
* Date Created: 9/27/2023
* Date Last Modified: 9/30/2023
* Description: This function sorts the current order of songs in the playlist based on Album title (A to Z).
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void sort_album_title(Node** pList)
{
	Node* pCur1 = *pList;
	Node* pCur2 = (*pList)->pNext;

	char min_album_title[100];
	Node* min_node_ptr = NULL;

	if (*pList != NULL)
	{
		while (pCur1->pNext != NULL)
		{
			strcpy(min_album_title, pCur1->data.album_title);
			min_node_ptr = pCur1;

			while (pCur2 != NULL)
			{

				if (strcmp(pCur2->data.album_title, min_album_title) < 0)
				{
					strcpy(min_album_title, pCur2->data.album_title);
					min_node_ptr = pCur2;
				}

				pCur2 = pCur2->pNext;
			}

			//Updating the list!!
			Record temp_record = pCur1->data;
			pCur1->data = min_node_ptr->data;
			min_node_ptr->data = temp_record;

			//updating the pointer
			pCur1 = pCur1->pNext;
			pCur2 = pCur1;
			pCur2 = pCur2->pNext;
		}

	}

	else printf("\nThere is no song to sort on the playlist!\n");


	//Node* pCur1 = *pList;
	//Node* pCur2 = pCur1;

	//int min_album_title = pCur2->data.album_title;
	//Node* min_node_ptr = NULL;

	//while (pCur1->pNext != NULL)
	//{
	//	while (pCur2 != NULL)
	//	{
	//		if (pCur2->data.album_title < min_album_title)
	//		{
	//			min_album_title = pCur2->data.album_title;
	//			min_node_ptr = pCur2;
	//		}

	//		pCur2 = pCur2->pNext;
	//	}



	//	if (pCur1 == *pList && min_node_ptr != NULL) //just dragging the node to the front!!
	//	{
	//		if (min_node_ptr->pNext == NULL) //dragging the last node to the front
	//		{
	//			min_node_ptr->pPrev->pNext = NULL;
	//			min_node_ptr->pNext = *pList; //chagning the node ptr to the front
	//			min_node_ptr->pPrev = NULL; //chagning the node ptr to the front
	//			min_node_ptr->pNext->pPrev = min_node_ptr;
	//			*pList = min_node_ptr; //updating the head pointer
	//		}

	//		else //dragging none lat node to the front
	//		{
	//			min_node_ptr->pPrev->pNext = min_node_ptr->pNext;
	//			min_node_ptr->pNext->pPrev = min_node_ptr->pPrev;
	//			min_node_ptr->pNext = *pList;
	//			min_node_ptr->pPrev = NULL;
	//			min_node_ptr->pNext->pPrev = min_node_ptr;
	//			*pList = min_node_ptr;
	//		}

	//	}

	//	else if (pCur1 != *pList && min_node_ptr != NULL) //just dragging the node to the middle
	//	{
	//		if (min_node_ptr->pNext == NULL) //dragging the last node
	//		{
	//			min_node_ptr->pPrev->pNext = min_node_ptr->pNext; //which is pointin to NULL;
	//			min_node_ptr->pNext = pCur1;
	//			min_node_ptr->pPrev = pCur1->pPrev;
	//			pCur1->pPrev = min_node_ptr;
	//			pCur1->pPrev->pNext = min_node_ptr;
	//		}

	//		else //dragging non lat node to the front
	//		{
	//			min_node_ptr->pPrev = min_node_ptr->pNext;
	//			min_node_ptr->pNext->pPrev = min_node_ptr->pPrev;

	//			min_node_ptr->pNext = pCur1;
	//			min_node_ptr->pPrev = pCur1->pPrev;

	//			pCur1->pPrev->pNext = min_node_ptr;
	//			pCur1->pPrev = min_node_ptr;

	//		}


	//	}

	//	//updating the pointers!
	//	pCur1 = pCur1->pNext;
	//	pCur2 = pCur1;

	//	min_album_title = pCur2->data.album_title;
	//	min_node_ptr = NULL;

	//}
}



/********************************************************************************************************************
* Function: sort_rating()
* Date Created: 9/28/2023
* Date Last Modified: 9/30/2023
* Description: This function sorts the current order of songs in the playlist based on rating of rach song (1 to 5).
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void sort_rating(Node** pList)
{

	Node* pCur1 = *pList;
	Node* pCur2 = (*pList)->pNext;
	
	int min_rating = 7;
	Node* min_node_ptr = NULL;
	
	if (*pList != NULL)
	{
		while (pCur1->pNext != NULL)
		{
			min_rating = pCur1->data.rating;
			min_node_ptr = pCur1;

			while (pCur2 != NULL)
			{

				if (pCur2->data.rating < min_rating)
				{
					min_rating = pCur2->data.rating;
					min_node_ptr = pCur2;
				}

				pCur2 = pCur2->pNext;
			}

			//Updating the list!!
			Record temp_record = pCur1->data;
			pCur1->data = min_node_ptr->data;
			min_node_ptr->data = temp_record;

			//updating the pointer
			pCur1 = pCur1->pNext;
			pCur2 = pCur1;
			pCur2 = pCur2->pNext;
		}

	}

	else printf("\nThere is no song to sort on the playlist!\n");
	//Node* pCur1 = *pList;
	//Node* pTemp1 = (*pList)->pNext;

	//while (pCur1->pNext != NULL)
	//{
	//	if (pCur1->data.rating > pCur1->pNext->data.rating) //if so lets's swap.
	//	{

	//		if (pCur1 == *pList && pTemp1->pNext != NULL) //at the first node
	//		{
	//			pCur1->pNext->pNext->pPrev = pCur1;
	//			pCur1->pNext = pCur1->pNext->pNext;

	//			pTemp1->pNext = pCur1;
	//			pTemp1->pPrev = NULL;

	//			pCur1->pPrev = pTemp1;
	//			*pList = pTemp1;

	//		}

	//		else if (pCur1 != *pList && pTemp1->pNext != NULL) //not at the first node
	//		{
	//			pCur1->pNext = pTemp1->pNext;
	//			pTemp1->pNext->pPrev = pCur1;

	//			pTemp1->pNext = pCur1;
	//			pTemp1->pPrev = pCur1->pPrev;
	//			
	//			pCur1->pPrev = pTemp1;
	//			pTemp1->pPrev->pNext = pTemp1;

	//		}

	//		else if (pCur1 != *pList && pTemp1->pNext == NULL) //not at the first node
	//		{
	//			pTemp1->pPrev->pNext = NULL;

	//			pTemp1->pNext = pCur1;
	//			pTemp1->pPrev = pCur1->pPrev;

	//			pCur1->pPrev = pTemp1;
	//			pTemp1->pPrev->pNext = pTemp1;
	//		}

	//		else if (pCur1 == *pList && pTemp1->pNext == NULL) //only two nodes to swap.
	//		{
	//			pCur1->pNext = NULL;
	//			pTemp1->pNext = *pList;
	//			pTemp1->pPrev = NULL;
	//			pCur1->pPrev = pTemp1;
	//			*pList = pTemp1;
	//			return;
	//		}

	//		pTemp1 = pCur1;; //updating the pCur1 ptr!

	//	}

	//	else
	//	{
	//		pTemp1 = pTemp1->pNext;
	//	}

	//	pCur1 = pCur1->pNext;
	//	pTemp1 = pTemp1->pNext->pNext;
	//}

}




/********************************************************************************************************************
* Function: sort_number_times_played()
* Date Created: 9/28/2023
* Date Last Modified: 9/30/2023
* Description: This function sorts the current order of songs in the playlist based on the number of times played for
* each song from largest to smallest.
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void sort_number_times_played(Node** pList)
{
	//Node* pCur1 = *pList;
	//Node* pCur2 = (*pList)->pNext;

	//int max_numbers_times_played = -1;
	//Node* max_node_ptr = NULL;

	//if (*pList != NULL)
	//{
	//	while (pCur1->pNext != NULL)
	//	{
	//		max_numbers_times_played = pCur1->data.numbers_times_played;
	//		max_node_ptr = pCur1;

	//		while (pCur2 != NULL)
	//		{

	//			if (pCur2->data.numbers_times_played > max_numbers_times_played)
	//			{
	//				max_numbers_times_played = pCur2->data.numbers_times_played;
	//				max_node_ptr = pCur2;
	//			}

	//			pCur2 = pCur2->pNext;
	//		}

	//		//Updating the list!!
	//		Record temp_record = pCur1->data;
	//		pCur1->data = max_node_ptr->data;
	//		max_node_ptr->data = temp_record;

	//		//updating the pointer
	//		pCur1 = pCur1->pNext;
	//		pCur2 = pCur1;
	//		pCur2 = pCur2->pNext;
	//	}
	//}

	//else printf("\nThere is no song to sort on the playlist!\n");


	Node* pCur1 = *pList;
	Node* pCur2 = (*pList)->pNext;

	int max_times_played = 0;
	Node* max_node_ptr = NULL;
	Node* temp_node = NULL;

	while (pCur1->pNext != NULL)
	{
		max_times_played = pCur1->data.numbers_times_played;
		max_node_ptr = pCur1;

		while (pCur2 != NULL)
		{
			
			if (pCur2->data.numbers_times_played > max_times_played)
			{
				max_times_played = pCur2->data.numbers_times_played;
				max_node_ptr = pCur2;
			}

			pCur2 = pCur2->pNext;
		}

		

		if (pCur1 == *pList && max_node_ptr != pCur1) //just dragging the node to the front!!
		{
			if (max_node_ptr->pNext == NULL) //dragging the last node to the front
			{
				max_node_ptr->pPrev->pNext = NULL; //dissociating the node
				
				max_node_ptr->pNext = *pList; //chagning the node ptr to the front
				max_node_ptr->pPrev = NULL; //chagning the node ptr to the front

				max_node_ptr->pNext->pPrev = max_node_ptr;

				*pList = max_node_ptr; //updating the head pointer
			}

			else //dragging the middle node to the front
			{
				max_node_ptr->pPrev->pNext = max_node_ptr->pNext;//dissociating the node
				max_node_ptr->pNext->pPrev = max_node_ptr->pPrev; //dissociating the node

				max_node_ptr->pNext = *pList;
				max_node_ptr->pPrev = NULL;

				max_node_ptr->pNext->pPrev = max_node_ptr;

				*pList = max_node_ptr;
			}

		}



		else if (pCur1 != *pList && max_node_ptr != pCur1) //just dragging the node to the middle
		{
			if (max_node_ptr->pNext == NULL) //dragging the last node to the middle.
			{
				max_node_ptr->pPrev->pNext = NULL; //which is pointin to NULL;

				max_node_ptr->pNext = pCur1;
				max_node_ptr->pPrev = pCur1->pPrev;

				max_node_ptr->pNext->pPrev = max_node_ptr;
				max_node_ptr->pPrev->pNext = max_node_ptr;
			}

			else //dragging non late node to the middle
			{
				max_node_ptr->pPrev->pNext = max_node_ptr->pNext;
				max_node_ptr->pNext->pPrev = max_node_ptr->pPrev;
				
				max_node_ptr->pNext = pCur1;
				max_node_ptr->pPrev = pCur1->pPrev;

				max_node_ptr->pPrev->pNext = max_node_ptr;
				max_node_ptr->pNext->pPrev = max_node_ptr;

			}


		}
		
		if (max_node_ptr == pCur1) //nothing changes
		{
			//updating the pointers!
			pCur1 = pCur1->pNext;
			pCur2 = pCur1;
			pCur2 = pCur2->pNext;
		}
		
		else // nodes location changed
		{
			pCur2 = pCur1;
			pCur2 = pCur2->pNext;
		}

		printList(pList);
		/*max_times_played = pCur2->data.numbers_times_played;
		max_node_ptr = NULL;*/

	}

}


/********************************************************************************************************************
* Function: choose_sorting_methods()
* Date Created: 9/29/2023
* Date Last Modified: 9/30/2023
* Description: This function prompts the user to choose which sorting method to be utilized for the rearrgangement of
* the songs in the playlist.
* Input parameters: A pointer to a head pointer to a double-linked list.
* Returns: Nothing
*********************************************************************************************************************/
void choose_sorting_methods(Node** pList)
{
	int choose_method = 0;
	int again = 0;

	/*Node* pCur1 = *pList;
	Node* pCur2 = (*pList)->pNext;
	char min_artist[100];
	Node* node_ptr = NULL;
	char min_album_title[100];
	int min_rating = 7;
	int max_numbers_times_played = -1;*/

	do
	{
		again = 0;
		printf("\nChoose a method 1 ~ 4 to sort the record in the playlist!\n");
		
		printf("\nMethod 1: Sort based on Artist (A-Z)\n");
		printf("\nMethod 2: Sort based on Album Title (A-Z)\n");
		printf("\nMethod 3: Sort based on Rating (1-5)\n");
		printf("\nMethod 4: Sort based on times played (largest - smallest)\n");

		printf("\nEnter 1 ~ 4:");
		scanf("%d", &choose_method);

		switch (choose_method)
		{

		case 1:

			sort_artist(pList);
			printList(*pList);
			break;

		case 2:

			sort_album_title(pList);
			printList(*pList);
			break;

		case 3:
			
			sort_rating(pList);
			printList(*pList);
			break;

		case 4:

			sort_number_times_played(pList); //why is it not &&?????
			printList(*pList);
			break;

		}

		if (choose_method != 1 && choose_method != 2 && choose_method != 3 && choose_method != 4)
		{
			printf("\nIvnvalid Number! Please type 1, 2, 3 or 4 for choosing the sorting method!\n");
			again = 1;
			putchar('\n');
			system("pause");
			system("cls");
		}
	} while (again == 1);

}



/********************************************************************************************************************
* Function: making_random_order_array()
* Date Created: 9/29/2023
* Date Last Modified: 9/30/2023
* Description: This function fills each index of the array with the random number through 1 to n, without any overlapping
* numbers. This will set up a foundation for shuffle music playlist function.
* Input parameters: A pointer to a head pointer to a double-linked list, An integer array of play_order_array,
* how many elements in the array.
* Returns: Nothing
*********************************************************************************************************************/
void making_random_order_array(Node** pList, int play_order_array[], int n)
{
	int again = 0;

	/*int n = 0;
	Node* count_ptr = *pList;

	while (count_ptr->pNext != NULL)
	{
		n++;
		count_ptr = count_ptr->pNext;
	}*/

	for (int i = 0; i < n; i++)
	{
		do
		{
			again = 0;
			play_order_array[i] = (rand() % n) + 1;

			for (int j = 0; j < i /*9*/; j++)
			{
				if (play_order_array[j] == play_order_array[i]) again = 1;
			}
		} while (again == 1);
	}

	
}



/********************************************************************************************************************
* Function: shuffle_func()
* Date Created: 9/29/2023
* Date Last Modified: 9/30/2023
* Description: Based on the value n for each cell of play_order_array, the pointer will travere through the nth node in the
* double linked list and play that particular song. Based on the distance between the current pointer and the next song node
* to play, the pointer can either go backwards or go front.
* Input parameters: A pointer to a head pointer to a double-linked list, An integer array of play_order_array,
* how many elements in the array.
* Returns: Nothing
* Preconditions: Each cell of play_order_array must be filled with a random integer through 1 to n only once with the implementation
* of making_random_order_array() function.
*********************************************************************************************************************/
void shuffle_func(Node** pList, int play_order_array[], int n) //precondition the current array size is 9
{
		
	//making_random_order_array(&pList, play_order_array, n);
	//int again = 0;

	//for (int i = 0; i < n; i++)
	//{
	//	do
	//	{
	//		again = 0;
	//		play_order_array[i] = (rand() % n) + 1;

	//		for (int j = 0; j < i /*9*/; j++)
	//		{
	//			if (play_order_array[j] == play_order_array[i]) again = 1;
	//		}
	//	} while (again == 1);
	//}
	

	if (*pList != NULL) //not empty
	{
		Node* search_ptr = *pList;
		int current_search_order = 1; 
		int how_many_songs = 1;

		for (int i = 0; i < n; i++)
		{
			if (current_search_order < play_order_array[i])
			{
				for (int j = play_order_array[i] - current_search_order; j > 0; j--)
				{
					search_ptr = search_ptr->pNext;
				}
				
			}

			else if ((current_search_order > play_order_array[i]))
			{
				for (int j = current_search_order - play_order_array[i]; j > 0; j--)
				{
					search_ptr = search_ptr->pPrev;
				}
				
			}

			current_search_order = play_order_array[i];

			search_ptr->data.numbers_times_played++;

			printf("*******************************Music %d*******************************\n\n", how_many_songs);
			printf("Artist: %s\n", search_ptr->data.artist); //pMem->data.artist not defined error!!!!
			printf("Album Title: %s\n", search_ptr->data.album_title);
			printf("Song Title: %s\n", search_ptr->data.song_title);
			printf("Genre: %s\n", search_ptr->data.genre);
			printf("Song Duration Minutes: %d\n", search_ptr->data.song_length.minutes);
			printf("Song Duration Seconds: %d\n", search_ptr->data.song_length.seconds);
			printf("Number Time Played: %d\n", search_ptr->data.numbers_times_played);
			printf("Rating: %d\n\n", search_ptr->data.rating);
			printf("**********************************************************************\n\n");
			printf("                                     :\n");
			printf("                                     :\n");
			printf("                                     :\n");
			printf("                                     :\n\n");

			Sleep(1000);
			printf("                                     :\n");
			Sleep(1000);
			printf("                                     :\n");
			Sleep(1000);
			printf("                                     :\n");
			Sleep(1000);
			printf("                                     :\n\n");

			Sleep(3000);
			system("cls");

			how_many_songs++;
		}


	}

	else
	{
		printf("\nCan't Shuffle! There are no nodes in the list\n");
	}

	return;
}