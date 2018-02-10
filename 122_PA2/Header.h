
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef enum menuOption {
	LOAD = 1,
	STORE = 2,
	UNKNOWN = 3,
	INSERT = 4,
	REMOVE_SONG = 5,
	EDIT = 6,
	SORT = 7,
	RATE = 8,
	PLAY = 9,
	SHUFFLE = 10,
	QUIT = 11
} MenuOption;

typedef struct duration {
	int minutes;
	int seconds;
} Duration;

typedef struct record {
	char Artist[100];
	char Album[100];
	char Song[50];
	char Genre[30];
	Duration length;
	int timesPlayed;
	int Rating;
} Record;

typedef struct node {
	Record *Data;
	struct node *pNext;
	struct node *pPrev;
} Node;

int printMenu();
void load(Node **pList, FILE *outfile);
void decision(int choice, FILE *infile, Record *data, Node **pList);
void store(FILE *outfile, Node *pList);
void display(Node *pList);
void insert(Node **pHead, Record *newRecord);
void removeSong(Node *pHead);
void edit(Node *pHead);
void sort();
void rate(Node *pHead);
void play(Node *pHead, Record *newRecord);
void shuffle();
void insertAtFront(Node **pList, Record *newRecord);
void quit(Node **pList, FILE *infile);
void makeDecision(Node **pList);
void getArtist(char artistName[], Node *pHead);
void runApp();
Node* makeNode(Record *newRecord);
void stringTok(Record *newRecord, Node **pList, FILE *infile);
void initalizeRecord(Record *newRecord, Node *newNode);