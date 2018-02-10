#include "Header.h"

int printMenu()
{
	int choice = 0;

	printf(" (1)   load\n (2)   store\n (3)   display\n (4)   insert\n (5)   delete\n (6)   edit\n (7)   sort\n (8)   rate\n (9)   play\n (10) shuffle\n (11) exit\n ");
	scanf(" %d", &choice);

	return choice;
}

void decision(int choice, FILE *infile, Record *data, Node **pList)
{
	Record newRecord = { "A","a","a","a","a",1,1,1 };
	switch (choice)
	{
	case 1:
	{
		printf("loaded \n");
		load(&(*pList),infile);
		break;
	}

	case 2:
	{
		store(infile,(*pList));
		break;
	}

	case 3:
	{
		// Display by artist or display every song.
		makeDecision(&(*pList)); 
		break;
	}

	case 4:
	{
		insert(&(*pList),&newRecord);
		break;
	}

	case 5:
	{
		removeSong((*pList));
		break;
	}

	case 6:
	{
		edit(*pList);
		break;
	}

	case 7:
	{
		sort();
		break;
	}

	case 8:
	{
		rate(*pList);
		break;
	}

	case 9:
	{
		play((*pList),&newRecord);
		break;
	}

	case 10:
	{
		shuffle();
		break;
	}

	case 11:
	{
		quit(&(*pList),infile);
		break;
	}

	default: printMenu();
		break;
	}
}

void load(Node **pList, FILE *infile)
{
	printf("loading \n");
	Record newRecord = {"A","a","a","a","a",1,1,1 };

	stringTok(&newRecord,&(*pList),infile);
}

void runApp()
{
	FILE *infile;
	infile = fopen("musicPlayList.csv", "r");

	int choice;
	Record data[] = { NULL, NULL, NULL };
	Node *pList = NULL;

	choice = printMenu();
	
	//decision(choice, infile, data, pList);
	while (choice != 13)
	{
		decision(choice, infile, data, &pList);
		choice = printMenu();
	}
	exit(1);
}

void store(FILE *outfile, Node *pList)
{
	while (pList != NULL)
	{
		for (int i = 0; pList != NULL; i++)
		{
			if (i == 0)
			{
				fprintf(outfile, pList->Data->Artist);
				fprintf(outfile, ",");
			}

			else if (i == 1)
			{
				fprintf(outfile, pList->Data->Album);
				fprintf(outfile, ",");
			}

			else if (i == 2)
			{
				fprintf(outfile, pList->Data->Song);
				fprintf(outfile, ",");
			}

			else if (i == 3)
			{
				fprintf(outfile, pList->Data->Genre);
				fprintf(outfile, ",");
			}

			else if (i == 4)
			{
				fprintf(outfile, pList->Data->length.minutes);
				fprintf(outfile, ",");
			}

			else if (i == 5)
			{
				fprintf(outfile, pList->Data->timesPlayed);
				fprintf(outfile, ",");
			}

			else if (i == 6)
			{
				fprintf(outfile, pList->Data->Rating);
				fprintf(outfile, ",");
			}
			printf(" completed \n");
		}
		pList = pList->pNext;
	}
}

void display(Node *pHead)
{
	printf(" \n");

	while (pHead != NULL)
	{
		printf("Artist: %s \n", pHead->Data->Artist);
		printf("Album: %s \n", pHead->Data->Album);
		printf("Song: %s \n", pHead->Data->Song);
		printf("Genre: %s \n", pHead->Data->Genre);
		printf("Length: %d \n", pHead->Data->length.minutes);
		printf("Times Played: %d \n", pHead->Data->timesPlayed);
		printf("Rating %d \n", pHead->Data->Rating);
		printf("\n");
		pHead = pHead->pNext;
	}

}

void insert(Node **pHead, Record *newRecord)
{
	Node *pNew = makeNode(newRecord);

	char scannedData[100] = { NULL };
	int scannedIntegers = 0;
		
	printf("Please enter the new Artist Name \n");
	scanf(" %s", scannedData);
	strcpy(pNew->Data->Artist, scannedData);

	printf("Please enter the new Album Name \n");
	scanf(" %s", scannedData);
	strcpy(pNew->Data->Album, scannedData);

	printf("Please enter the new Song Name \n");
	scanf(" %s", scannedData);
	strcpy(pNew->Data->Song, scannedData);

	printf("Please enter the new Genre Name \n");
	scanf(" %s", scannedData);
	strcpy(pNew->Data->Genre, scannedData);

	printf("Please enter the new Length in minutes \n");
	scanf(" %d", &scannedIntegers);
	pNew->Data->length.minutes = scannedIntegers;

	printf("Please enter the new Length in seconds \n");
	scanf(" %d", &scannedIntegers);
	pNew->Data->length.seconds = scannedIntegers;

	printf("Please enter the new TImes Played in minutes \n");
	scanf(" %d", &scannedIntegers);
	pNew->Data->timesPlayed = scannedIntegers;

	printf("Please enter the new Rating \n");
	scanf(" %d", &scannedIntegers);
	pNew->Data->Rating = scannedIntegers;


	pNew->pNext = *pHead;
	(*pHead)->pPrev = pNew;
	*pHead = pNew;
}

void removeSong(Node *pHead)
{
	Record newRecord = { "A","a","a","a","a",1,1,1 };
	char artistName[100] = { NULL };
	char newString[100] = { NULL };
	int input = 0, newRating = 0;

	printf("Please enter the Artists name (case sensetive!) \n");
	scanf(" %s", newString);

	while (pHead != NULL)
	{
		if (strcmp(newString, pHead->Data->Artist) == 0)
		{
			printf("Artist: %s \n", pHead->Data->Artist);
			printf("Album: %s \n", pHead->Data->Album);
			printf("Song: %s \n", pHead->Data->Song);
			printf("Genre: %s \n", pHead->Data->Genre);
			printf("Length: %d \n", pHead->Data->length.minutes);
			printf("Times Played: %d \n", pHead->Data->timesPlayed);
			printf("Rating %d \n", pHead->Data->Rating);
			printf("\n");

			printf("Would you like to remove this song? \n Type 1 for yes and o for no ");
			scanf(" %d", &input);

			if (input == 1)
			{
				Node *pTemp = makeNode(&newRecord);
				Node *pPrevv = makeNode(&newRecord);
				pPrevv = pHead->pPrev;
				pTemp = pHead->pNext;

				pTemp->pPrev = pPrevv;
				pPrevv->pNext = pTemp;

				free(pHead);

				return;
			}
		}
		pHead = pHead->pNext;
	}
}

void edit(Node *pHead)
{
	char decision[100] = { NULL };
	int yes = 1, no = 0;
	int scannedResult = 0;

	printf(" Would you like to edit the artists name ? \n Type y for yes and n for no! \n");
	scanf(" %d", &scannedResult);

	if (scannedResult == yes)
	{
		printf("What do you want the artist name to be? \n");
		scanf(" %s", decision);
		strcpy(pHead->Data->Artist, decision);
	}

	printf(" Would you like to edit the album name ? \n Type 1 for yes and 0 for no \n");
	scanf(" %d", &scannedResult);

	if (scannedResult == yes)
	{
		printf("What do you want the Album name to be? \n");
		scanf( "%s", decision);
		strcpy(pHead->Data->Album, decision);
	}

	printf(" Would you like to edit the Song name ? \n  Type 1 for yes and 0 for no \n");
	scanf(" %d", &scannedResult);

	if (scannedResult == yes)
	{
		printf("What do you want the Song name to be? \n");
		scanf(" %s", decision);
		strcpy(pHead->Data->Song, decision);
	}

	printf(" Would you like to edit the Genre ? \n  Type 1 for yes and 0 for no \n");
	scanf(" %d", &scannedResult);

	if (scannedResult == yes)
	{
		printf("What do you want the Genre to be? \n");
		scanf(" %s", decision);
		strcpy(pHead->Data->Genre, decision);

	}

	printf(" Would you like to edit the Length ? \n  Type 1 for yes and 0 for no \n");
	scanf(" %d", &scannedResult);

	if (scannedResult == yes)
	{
		printf("What do you want the length in minutes to be? \n");
		scanf(" %d", &scannedResult);
		pHead->Data->length.minutes = scannedResult;

		printf("What do you want the length in seconds to be? \n");
		scanf(" %d", &scannedResult);
		pHead->Data->length.seconds = scannedResult;

	}

	printf(" Would you like to edit the times played ? \n  Type 1 for yes and 0 for no \n");
	scanf(" %d", &scannedResult);

	if (scannedResult == yes)
	{
		printf("What do you want the times played to be? \n");
		scanf(" %d", &scannedResult);
		pHead->Data->timesPlayed = scannedResult;
	}

	printf(" Would you like to edit the Rating ? \n  Type 1 for yes and 0 for no \n");
	scanf(" %d", &scannedResult);

	if(scannedResult == yes)
	{
		printf("What do you want the rating to be? \n");
		scanf(" %d", &scannedResult);
		pHead->Data->Rating = scannedResult;
	}

}

void sort()
{

}

void rate(Node *pHead)
{
	char artistName[100] = { NULL };
	char newString[100] = { NULL };
	int input = 0, newRating = 0;

	printf("Please enter the Artists name (case sensetive!) \n");
	scanf(" %s", newString);

	while (pHead != NULL)
	{

		if (strcmp(newString, pHead->Data->Artist) == 0)
		{
			printf("Artist: %s \n", pHead->Data->Artist);
			printf("Album: %s \n", pHead->Data->Album);
			printf("Song: %s \n", pHead->Data->Song);
			printf("Genre: %s \n", pHead->Data->Genre);
			printf("Length: %d \n", pHead->Data->length.minutes);
			printf("Times Played: %d \n", pHead->Data->timesPlayed);
			printf("Rating %d \n", pHead->Data->Rating);
			printf("\n");

			printf("Would you like to rate this song? \n Type 1 for yes and o for no ");
			scanf(" %d", &input);

			if (input == 1)
			{
				printf("What would you like the rating to be ? \n");
				scanf(" %d", &newRating);

				pHead->Data->Rating = newRating;
				return;
			}
		}
		pHead = pHead->pNext;
	}
}

void play(Node *pHead, Record *newRecord)
{
	char newString[100] = { NULL };
	int playing = 0;

	printf("Please enter the Artists name (case sensetive!) \n");
	scanf(" %s", newString);

	while (pHead != NULL)
	{
		if (strcmp(newString, pHead->Data->Artist) == 0)
		{
			printf("Do you want to play ");
			printf("Artist: %s \n", pHead->Data->Artist);
			printf("Album: %s \n", pHead->Data->Album);
			printf("Song: %s \n", pHead->Data->Song);
			printf("Genre: %s \n", pHead->Data->Genre);
			printf("Length: %d \n", pHead->Data->length.minutes);
			printf("Times Played: %d \n", pHead->Data->timesPlayed);
			printf("Rating %d \n", pHead->Data->Rating);
			printf("\n Type 1 for yes and 0 for no \n");
			scanf(" %d", &playing);

		}

		if (playing == 1)
		{
			printf("Currently Playing: %s \n", pHead->Data->Song);
			printf("By: %s \n", pHead->Data->Artist);
			_sleep(1000);
			system("cls");
		}

		pHead = pHead->pNext;
	}

}

void shuffle()
{

}

void quit(Node **pList, FILE *infile)
{
	load(&(*pList), infile);
	exit(0);
}

Node *makeNode(Record *newRecord)
{
	Node *newNode = NULL;
	newNode = (Node*)malloc(sizeof(Node));

	if (newNode != NULL)
	{
		newNode->pNext = NULL;
		newNode->pPrev = NULL;
		newNode->Data = (Record*)malloc(sizeof(Record));
		initalizeRecord(newRecord, newNode);
	}
	return newNode;
}

void stringTok(Record *newRecord, Node **pList, FILE *infile)
{
	char delimiter[2] = ",";
	char *tok = "";
	char stringLine[2000] = "";
	int k = 0, i = 0;

	while (fgets(stringLine, 100, infile) != NULL)
	{
		tok = strtok(stringLine, delimiter);
		Node *inputRecord = makeNode(newRecord);
		k = 0;

		for (int j = 0; tok != NULL; j++)
		{

			if (j == 0)
			{
				if (k == 0)
				{
					strcpy(inputRecord->Data->Artist, tok); //Copying the string of any length	
				}
			}

			if (j == 1)
			{
				if ((int)*tok == 32 && k == 0)
				{
					j--;
					k++;
					strcat(inputRecord->Data->Artist, tok);
				}

				else
				{
					strcpy(inputRecord->Data->Album, tok);
				}

			}

			if (j == 2)
			{
				strcpy(inputRecord->Data->Song, tok);
			}

			if (j == 3)
			{
				strcpy(inputRecord->Data->Genre, tok);
			}

			if (j == 4)
			{
				inputRecord->Data->length.minutes = atoi(tok);
			}

			if (j == 5)
			{
				inputRecord->Data->timesPlayed = atoi(tok);
			}

			if (j == 6)
			{
				inputRecord->Data->Rating = atoi(tok);
			}

			tok = strtok(NULL, delimiter);
		}
		insertAtFront(pList, inputRecord->Data);
		i++;
	}
	system("cls");
	printf("Loaded! \n");
}

void insertAtFront(Node **pList, Record *newRecord)
{
	Node *pMem = NULL;

	pMem = makeNode(newRecord);

	if (pMem != NULL) // we allocated space for a Node and initialized it
	{
		// connect the new Node/container to the list
		if (*pList != NULL) // not empty list
		{
			pMem->pNext = *pList;
			(*pList)->pPrev = pMem; // doubly linked list
			*pList = pMem;
		}
		else // empty list
		{
			//pMem->pNext = *pList;
			//*pList)->pPrev = pMem;
			*pList = pMem;
		}
	}
}

void initalizeRecord(Record *newRecord, Node *newNode)
{
	newNode->Data->Rating = newRecord->Rating;
	strcpy(newNode->Data->Album, newRecord->Album);
	strcpy(newNode->Data->Artist, newRecord->Artist);
	strcpy(newNode->Data->Genre, newRecord->Genre);
	newNode->Data->length = newRecord->length;
	strcpy(newNode->Data->Song, newRecord->Song);
	newNode->Data->timesPlayed = newRecord->timesPlayed;
}

// By artist or all songs.
void makeDecision(Node **pList)
{
	int decision = 0 ;
	char *artistName = NULL;
	system("cls");
	printf("For Display By artist, enter 0, else enter 1 \n");
	scanf(" %d", &decision);

	if (decision != 0)
	{
		display(*pList);
	}

	else
	{
		getArtist(artistName, *pList);
	}
}

void getArtist(char artistName[], Node *pHead)
{
	char newString[100] = { artistName };
	int input = 0;
	if (artistName == NULL)
	{
		printf("Please enter the Artists name (case sensetive!) \n");
		scanf(" %s", newString);
	//	getArtist(newString, pHead);
	}

	while (pHead != NULL)
	{

		if (strcmp(newString, pHead->Data->Artist) == 0)
		{
			printf("Artist: %s \n", pHead->Data->Artist);
			printf("Album: %s \n", pHead->Data->Album);
			printf("Song: %s \n", pHead->Data->Song);
			printf("Genre: %s \n", pHead->Data->Genre);
			printf("Length: %d \n", pHead->Data->length.minutes);
			printf("Times Played: %d \n", pHead->Data->timesPlayed);
			printf("Rating %d \n", pHead->Data->Rating);
			printf("\n");

			printf("Would you like to modify this song? \n Type 1 for yes and o for no ");
			scanf(" %d", &input);
			
			if (input == 1)
			{
				edit(pHead);
				return;
			}
		}
		pHead = pHead->pNext;
	}

}