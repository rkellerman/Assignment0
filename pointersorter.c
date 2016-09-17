/*
 * pointersorter.c
 *
 *  Created on: Sep 12, 2016
 *      Author: RyanMini
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node{ 													// struct used to store distinct words and link them together in a singly linked list
	struct Node *next;
	char *string;
};

/*
 * Method:  numberOfWords
 * Arguments:  char *string
 * Returns:  int
 * Summary:  method is passed the input string from the user, returns the number of distinct words found in this string...
 *           ... returns -1 if the string is empty, and 0 if there are no distinct words, or only non-alpha characters.
 */
int numberOfWords(char *string){
	if (strlen(string) < 1){
		return -1;
	}

	int counter = 0;											// return variable, holds the number of words
	int i = 0;  												// string iteration variable
	int word = 0; 												// boolean integer, used to check if currently in a word
	while (string[i] != '\0'){									// loop until we hit the escape character, indicating the end of the input string
		if (isalpha(string[i])){ 								// if the character is a letter, the loop is in a word, set word = 1
			word = 1;
		}
		else if (!isalpha(string[i]) && word == 1){  			// if the loop was in a word, and we find a non-letter, we have finished the word
			word = 0;
			counter++;
		}
		i++;
	}
	if (word == 1){  											// checks for a word that is followed by the terminating character at the end of the loop
		counter++;
	}
	return counter;
}

/*
 * Method:  createList
 * Arguments:  char *string, int numWords
 * Returns:  struct Node*
 * Summary:  method is passed the result of the numberOfWords method and the input string, loops through the number of words to save each...
 *           ... distinct word to an instance of a struct Node.  The struct Nodes are linked together as they are built, inserted into the ...
 *           ... linked list data structure in sorted order by performing a series of comparisons upon insert.  Returns a pointer to the front of the ...
 *           ... list.
 */
struct Node* createList(char* string, int numWords){

	struct Node *front = NULL; 									// pointer to front of the list is initialized to NULL, will be assigned to an existing pointer later
	int j; 														// iteration variable used to loop through the number of words
	int i = 0; 													// iteration variable used to loop through the input string
	int word = 0;												// integer bool to represent the status of the loop
	int count = 0; 												// variable used to store the number of letters in the current word
	int start = 0; 												// variable used to store the starting i-value of the current word

	for (j = 0; j < numWords; j++){ 							// for loop runs for each word
		while (1){
			if (isalpha(string[i])){							// check if current character is a letter, if so...
				if (word != 1){ 								// we check if currently in a word, if so we note the starting point
					start = i; 									// monitor the starting location so that we can return to it when copying to the temp char*
				}
				word = 1;
				count++;
				i++;
			}
			else if (!isalpha(string[i]) && word == 1){
				word = 0;
				i++;
				break; 											// break is called when the word is complete
			}
			else {
				i++;
			}
		}

		/*
		 * The following segment of code uses the information from count in order to save the word to a dynamically allocated string
		 */

		char *temp = malloc((count + 1)*sizeof(char)); 			// assign a pointer to a string that can hold the length that we calculated, include space for '\0'

		int k ; 												// iteration variable used to loop through letters on the word
		int p = 0; 												// variable used to store the current place in the created string
		for (k = start; k < i-1; k++){
			temp[p] = string[k];
			p++;
		}
		temp[p] = '\0'; 										// add terminating character to the end of the string, so that it can be used for comparison by string library
		count = 0; 												// reset count for next loop

		struct Node *ptr = front; 								// create a temporary pointer to point to front

		if (ptr == NULL){ 										// if no word has been assigned yet
			ptr = (struct Node*)malloc(sizeof(struct Node)); 	// dynamically allocate memory for the current Node to be created
			ptr->string = temp;
			ptr->next = NULL;
			front = ptr;
		}
		else {
			struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));	// dynamically allocate memory for the current Node to be created
			tempNode->string = temp;
			tempNode->next = NULL;

			int doNotTouch = 0; 								// integer bool used to prevent entering if statement after breaking
			while (ptr -> next != NULL){ 						// loop through list until we on the last item in the list
				if (ptr == front){ 								// checks whether we are pointing to the fist item in the list
					int compare = strcmp(tempNode->string, front->string);
					if (compare < 0){ 							// the temp string comes before front alphabetically, assign accordingly
						tempNode->next = front;
						front = tempNode;
						doNotTouch = 1;
						break;
					}
					else { 										// otherwise we need to check front before we start incrementing ptr to ptr->next
						int compare = strcmp(tempNode->string, front->next->string);
						if (compare < 0){						// the temp string comes before front->next alphabetically, assign accordingly
							tempNode->next = front->next;
							front->next = tempNode;
							doNotTouch = 1;
							break;
						}
						else {
							ptr = ptr->next;
						}
					}
				}
				else { 											// here we are no longer on the first item in the list
					int compare = strcmp(tempNode->string, ptr->next->string);
					if (compare < 0){ 							// temp string is before ptr->next string, assign accordingly
						tempNode->next = ptr->next;
						ptr->next = tempNode;
						doNotTouch = 1;
						break;
					}
					else {
						ptr = ptr->next;
					}
				}
			}
			if (ptr == front && doNotTouch != 1){ 				// no longer in the while loop, check if necessary
				int compare = strcmp(tempNode->string, ptr->string);
				if (compare < 0){ 								// front was the only item in the list, and temp string comes before
					tempNode->next = ptr;
					front = tempNode;
				}
				else {
					ptr->next = tempNode;
				}
			}
			else if (doNotTouch != 1){ 							// the remaining case to be checked
				int compare = strcmp(tempNode->string, ptr->string);
				if (compare >= 0){
					tempNode->next = NULL;
					ptr->next = tempNode;
				}
				else {
					// should have been checked
				}
			}
		}
	}
	return front;
}


/*
 * Method:  main
 * Summary:  The main method is passed the arguments argc and *argv, which are the number of inputs as well as the inputs themselves.
 *           ... The main method first calls numberOfWords, then uses the result to call createList and return a pointer to the front...
 *           ... of the data structure holding the list.  Then it prints out the result in sorted order.
 */
int main(int argc, char *argv[]){


	if (argc <= 1){
		printf("Error, no inputs\n");
		return 0;
	}
	else if (argc > 2){
		printf("Error, too many inputs\n");
		return 0;
	}
	char *string = argv[1];

	int numWords = numberOfWords(string);  							// generates the total number of distinct words found in the string
	if (numWords < 1){ 												// if the method returns a value less than 1, that means there were no words in the input
		printf("No words\n");
		return 0;
	}
	struct Node *front = createList(string, numWords); 				// returns a pointer to a list of sorted

	struct Node *ptr = front;
	if (ptr == NULL){ 												// should have been covered, just in case
		printf("No words\n");
		return 0;
	}

	struct Node *temp = ptr;
	while (ptr->next != NULL){ 										// this loop is used to traverse the linked list and print out the result

		printf("%s\n", ptr->string);
		temp = ptr;
		ptr = ptr->next;
		free(temp->string);
		free(temp);

	}
	printf("%s\n", ptr->string);
	free(ptr->string);
	free(ptr);

}

