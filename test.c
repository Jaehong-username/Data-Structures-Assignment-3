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


/********************************************************************************************************************
* Function: test_insert_func()
* Date Created: 9/29/2023
* Date Last Modified: 9/30/2023
* Description: This will test for the correct implementation of insert_func().
* Input parameters: Nothing
* Returns: Nothing
*********************************************************************************************************************/
void test_insert_func(void)
{
	Node* pList = NULL;
	
	char start = NULL;

	printf("\nEnter one keyboard and press enter to continue: ");
	scanf("%c ", &start);

	insert_at_front_func(&pList);

	if (pList->data.numbers_times_played < 0)
	{
		printf("\nThe number of times played for the inserted song cannot be less than zero!\n");
	}
	else printf("\nThe number of times played for the inserted song is valid!\n");

	if (pList->data.rating < 0 || pList->data.rating < 6)
	{
		printf("\nThe rating for the inserted song cannot be either more than 5 or less than 0\n");
	}
	else printf("\nThe rating for the inserted song is valid!\n");

	if (pList == NULL)
	{
		printf("\nThe head pointer of the list is not updated!\n");
	}
	else printf("\nThe head pointer of the list is updated!\n");
}



/********************************************************************************************************************
* Function: test_delete_func()
* Date Created: 9/29/2023
* Date Last Modified: 9/30/2023
* Description: This will test for the correct implementation of delete_func().
* Input parameters: Nothing
* Returns: Nothing
*********************************************************************************************************************/
void test_delete_func(void)
{
	Node* pList = NULL;

	char start = NULL;

	printf("\nEnter one keyboard and press enter to continue: ");
	scanf("%c", &start);

	insert_at_front_func(&pList);

	if (pList != NULL) printf("\nAfter the insertion the head pointer is updated!\n");
	else printf("\nThe head pointer is not updated\n");

	printf("\nEnter one keyboard to and enter to continue: ");
	scanf("%c", &start);

	delete_func(&pList);

	if (pList == NULL) printf("\nAfter deletion, The head pointer of the list has been updated! It is a NULL pointer. \nThe memory successfully got released (deallocated)!\n");
	else printf("\nThe head pointer of the list has not been updated! It is not a NULL pointer. \nThe memory successfully got released (deallocated)!\n");


}


/********************************************************************************************************************
* Function: test_shuffle_func()
* Date Created: 9/29/2023
* Date Last Modified: 9/30/2023
* Description: This will test for the correct implementation of shuffle_func() with the play order 3, 1, 2
* Input parameters: Nothing
* Returns: Nothing
*********************************************************************************************************************/
void test_shuffle_func(void)
{
	                              //3   2  1
	int test_play_order_array[3] = { 3, 1, 2 };  //1 3 2     //3 1 2  //3 1 2   now it is 1 3 2

	Node* pList = NULL;

	char start = NULL;

	printf("\nEnter one keyboard and press enter to continue: ");
	scanf("%c", &start);

	insert_at_front_func(&pList);

	printf("\nEnter one keyboard and press enter to continue: ");
	scanf("%c", &start);

	insert_at_front_func(&pList);

	printf("\nEnter one keyboard and press enter to continue: ");
	scanf("%c", &start);

	insert_at_front_func(&pList);
	putchar('\n');
	putchar('\n');
	shuffle_func(&pList, test_play_order_array, 3);
	//since inserting from the front!!!
}