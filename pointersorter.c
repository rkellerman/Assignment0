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

struct Node{
	struct Node *next;
	char *string;
};

int numberOfWords(char *string){
	int counter = 0;
	int i = 0;
	int word = 0;
	while (string[i] != '\0'){
		if (isalpha(string[i])){  // if the character is a letter, the loop is in a word
			word = 1;
		}
		else if (!isalpha(string[i]) && word == 1){  // if the loop was in a word, and we find a non-letter, we have finished the word
			word = 0;
			counter++;
		}
		i++;
	}
	if (word == 1){  // checks for a word that is followed by the terminating character
		counter++;
	}
	return counter;
}

struct Node* createList(char* string, int numWords){

	struct Node *front = NULL;
	int j;
	int i = 0;
	int word = 0;					// integer bool to represent the status of the loop
	int count = 0;
	int start = 0;

	for (j = 0; j < numWords; j++){ 			// for loop runs for each word
		while (1){
			if (isalpha(string[i])){
				if (word != 1){
					start = i; 					// monitor the starting location so that we can return to it when copying to the temp char*
				}
				word = 1;
				count++;
				i++;
			}
			else if (!isalpha(string[i]) && word == 1){
				word = 0;
				i++;
				break; 							// break is called when the word is complete
			}
			else {
				i++;
			}
		}

		char *temp = malloc((count + 1)*sizeof(char)); 			// assign a pointer to a string that can hold the length that we calculated

		int k ;
		int p = 0;
		for (k = start; k < i-1; k++){
			temp[p] = string[k];
			p++;
		}
		temp[p] = '\0';
		count = 0;

		struct Node *ptr = front;

		if (ptr == NULL){
			ptr = (struct Node*)malloc(sizeof(struct Node));
			ptr->string = temp;
			ptr->next = NULL;
			front = ptr;
		}
		else {

			struct Node *tempNode = (struct Node*)malloc(sizeof(struct Node));
			tempNode->string = temp;
			tempNode->next = NULL;


			while (ptr->next != NULL){
				ptr = ptr->next;
			}
			ptr->next = tempNode;



			/*
			 *

			// at this point, ptr = front, which does not equal NULL
			while (ptr -> next != NULL){
				printf("sup\n");
				if (ptr == front){
					int compare = strcmp(tempNode->string, front->string);
					if (compare < 0){
						tempNode->next = front;
						front = tempNode;
					}

					else {
						int compare = strcmp(tempNode->string, front->next->string);
						if (compare < 0){
							tempNode->next = front->next;
							front->next = tempNode;
						}
						else {
							ptr = ptr->next;
						}
					}
				}

				else {
					printf("Hello\n");
					int compare = strcmp(tempNode->string, ptr->next->string);
					if (compare < 0){
						tempNode->next = ptr->next;
						ptr->next = tempNode;
					}
					else {
						printf("yo\n");
						ptr = ptr->next;
					}
				}
			}
			if (ptr == front){
				int compare = strcmp(tempNode->string, ptr->string);
				if (compare < 0){
					tempNode->next = ptr;
					front = tempNode;
					// complete
				}
				else {
					ptr->next = tempNode;
					// complete
				}
			}
			else {
				int compare = strcmp(tempNode->string, ptr->string);
				if (compare >= 0){
					tempNode->next = NULL;
					ptr->next = tempNode;
				}
				else {
					// should have been checked
				}

			}


			*/

		}
	}
	return front;
}



int main(int argc, char *argv[]){


    // if a is alphabetically before d, it returns a negative number

	char *string = argv[1];
	struct Node *front = NULL;
	int numWords = numberOfWords(string);  				// generates the total number of distinct words found in the string

	front = createList(string, numWords); 		// returns a pointer to a list of unsorted words



	struct Node *ptr = front;
    printf("\n");
	while (ptr->next != NULL){

		printf("%s --> ", ptr->string);

		ptr = ptr->next;
	}
	printf("%s\n\n", ptr->string);
}

