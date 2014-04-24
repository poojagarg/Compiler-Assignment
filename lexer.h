//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
#ifndef LEXERDEF_H
	#define LEXERDEF_H
	#include"lexerDef.h"
#endif
#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif
FILE *getStream(FILE *fp, buffer B, buffersize k);
tokenInfo  getNextToken( FILE *fp);
int isAlphabet(char c);
void insertQueue(token* t,tokenInfo Result,tokenInfo Last);
void display(tokenInfo t);
void deleteQueue(tokenInfo q);

