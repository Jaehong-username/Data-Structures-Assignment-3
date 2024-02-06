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


#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdbool.h>

#include <windows.h>

#include <time.h>

typedef struct duration
{
	int seconds;
	int minutes;

} Duration;


typedef struct record
{
	char artist[50];
	char album_title[50];
	char song_title[50];
	char genre[20];
	Duration song_length; //struct duration song_length; ?? what's the difference??
	int numbers_times_played;
	int rating; // 1 ~ 5

} Record;

typedef struct node
{
	Record data;
	struct node* pNext;  //vs Node* pNext;
	struct node* pPrev;  //vs Node* pPrev;

} Node;


void load_func(FILE* infile, Node** pList);

void display_func(Node* pList);

void printList(Node* pList);

int search_func(Node* pList, char artist_name[100]);

void store_func(FILE* outfile, Node* pList);

void edit_func(Node* pList);

void rate_func(Node* pList);

void play_func(Node* pList);

bool exit_func(bool exit);

void insert_at_front_func(Node** pList);

void delete_func(Node** pList);

void sort_artist(Node** pList);

void sort_album_title(Node** pList);

void sort_rating(Node** pList);

void sort_number_times_played(Node** pList);

void choose_sorting_methods(Node** pList);

void making_random_order_array(Node** pList, int play_order_array[], int n);

void shuffle_func(Node** pList, int play_order_array[], int n);


#endif
