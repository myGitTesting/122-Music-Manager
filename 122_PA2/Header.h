
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct Duration {
	int minutes;
	int seconds;
} duration;

typedef struct Record {

	char Artist[100];
	char Album[100];
	char Song[50];
	char Genre[30];
	duration length;
	int timesPlayed;
	int Rating;

}record;

typedef struct Node {

	record *Data;
	struct node *pNext;
	struct node *pPrev;

}node;


int printMenu();
void load(node **pList, FILE *outfile);
void decision(int choice, FILE *infile, record *data, node **pList);
void store(FILE *outfile, node *pList);
void display(node *pList);
void insert(node **pHead, record *newRecord);
void removeSong(node *pHead);
void edit(node *pHead);
void sort();
void rate(node *pHead);
void play(node *pHead, record *newRecord);
void shuffle();
void insertAtFront(node **pList, record *newRecord);
void quit(node **pList, FILE *infile);
void makeDecision(node **pList);
void getArtist(char artistName[], node *pHead);
void runApp();
node *makeNode(record *newRecord);
void stringTok(record *newRecord, node **pList, FILE *infile);
void initalizeRecord(record *newRecord, node *newNode);