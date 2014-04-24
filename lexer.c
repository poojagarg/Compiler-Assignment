//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
#ifndef STDIO_H
	#define STDIO_H
	#include<stdio.h>
#endif
#include<stdlib.h>
#include<string.h>
#ifndef LEXERDEF_H
	#define LEXERDEF_H
	#include"lexerDef.h"
#endif
char *words[]=  {"mainFunction","functionDef","ifStmt","funCallStmt","type","remainingList","var_list","more_ids","leftHandSide_singleVar","leftHandSide_listVar","sizeExpression","B","C","var","listVar","operator_lowPrecedence","operator_highPrecdence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","row" ,"F","remainingColElements","booleanExpression","ioStmt","stmtsAndFunctionDefs","stmtOrFunctionDef","A","stmt","declarationStmt","assignmentStmt_type1","assignmentStmt_type2","parameter_list","rightHandSide_type1","rightHandSide_type2" ,"arithmeticExpression" ,"otherStmts","inputParameterList","arithmeticTerm","D","factor","E","rows","G","MAIN","SQO","SQC","SEMICOLON","FUNCTION","ASSIGNOP","FUNID","END","ID","INT","REAL","STRING","MATRIX","COMMA","SIZE","IF","OP","CL","ELSE","ENDIF","PRINT","READ","PLUS","MINUS","MUL","DIV","NUM","RNUM","STR","AND","OR","LT","LE","EQ","GT","GE","NE","NOT","EPSILON"};

int isalphabet(char c)
{
	if(c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='f'||c=='g'||c=='h'||c=='i'||c=='j'||c=='k'||c=='l'||c=='m'||c=='n'||c=='o'||c=='p'||c=='q'||c=='r'||c=='s'||c=='t'||c=='u'||c=='v'||c=='w'||c=='x'||c=='y'||c=='z'||c=='A'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F'||c=='G'||c=='H'||c=='I'||c=='J'||c=='K'||c=='L'||c=='M'||c=='N'||c=='O'||c=='P'||c=='Q'||c=='R'||c=='S'||c=='T'||c=='U'||c=='V'||c=='W'||c=='X'||c=='Y'||c=='Z')		
		return 1;
	else
		return 0;

}
int isDelimiter(char c){
	if(c==' ') return 1;
	if(c=='\t') return 1;
	if(c=='\n') return 1;
	else return 0;
}
int isDelimiter2(char c){
	if(c==' ') return 1;
	if(c=='\t') return 1;
	else return 0;
}

void show(buffer B){
	int i=0;
	while(B[i]!='~'){
		printf("%c",B[i]);
		i++;
		}
		printf("%c",B[i]);
}
FILE *getStream(FILE *fp, buffer B, buffersize k){
	char c=fgetc(fp); 
	while(isDelimiter2(c)) {c=fgetc(fp);}
	int bufferIndex=0; 
	if(c=='#'){do{c=fgetc(fp);}while(c!='\n'); }
	B[bufferIndex++]=c; int flagFirstDelimiter=1;
	while(bufferIndex!=k-1){
		if(feof(fp)) {B[bufferIndex-1]='~';  return fp;}
		c=fgetc(fp);
		if(c=='#'){do{c=fgetc(fp);}while(c!='\n'); B[bufferIndex++]=c; continue;}
		if(isDelimiter2(c)&&flagFirstDelimiter==0) continue;	
		if(isDelimiter2(c)) {c=' ';flagFirstDelimiter=0;}
		else flagFirstDelimiter=1;
		B[bufferIndex++]=c;
	}
	B[bufferIndex]='~';	
	show(B[bufferIndex]);
	bufferIndex++;
	return fp;
}
		

int isdigit(char c)
{
	if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
		return 1;
	else
		return 0;
}


tokenQueue* createQueue(){
	tokenQueue* t=(tokenQueue*)malloc(sizeof(tokenQueue));
	t->Result=NULL; t->Last=NULL;
}
void deleteQueue(tokenInfo q){
	tokenInfo tmp,ftmp;
	if(q!=NULL){tmp=q;
	while(tmp!=NULL){ftmp=tmp; tmp=tmp->next; free(ftmp);}
}
}
void insertQueue(token* t,tokenQueue* q){
if(strcmp(t->lexeme, "function")==0) t->tokenIndex=50;
if(strcmp(t->lexeme, "-")==0) t->tokenIndex=69;
//printf("%s %s\t",words[t->tokenIndex], t->lexeme);
	if(t->tokenIndex>84)
		return;
	t->next=NULL;
	if(q->Result==NULL){// first element
		q->Result=t; q->Last=t;
	}//end of if
	else{
		q->Last->next=t; q->Last=t;}//end of else
//int a;  scanf("%d", &a);
	//printf("<%s>",q->Last->lexeme);
	
}
void display(token* t){
	if(t==NULL)
		return;
	while(t!=NULL){
		//debug();
		
		printf("<Token: %s, Lexeme:%s> \n ",words[t->tokenIndex],t->lexeme);
		
		t=t->next;	
		}//end of while
}
FILE* increement(FILE* fp){
	char c;
	while(!isDelimiter(c)) c=fgetc(fp);
	return fp;}

tokenInfo getNextToken(FILE *fp){
	char tmp;
	int flagError=0;
	tokenInfo Result=NULL; tokenInfo Last=Result;	
	int state=0; tokenInfo t; tokenQueue* q=createQueue();
	int i=0; int flag=0; //maintains if begin and forward are in same buffer (if yes, 0), else 1
	buffer B[2];
	char lexeme[sizeBuffer]; char c='a';
	int lineNumber=1;
	buffersize k=sizeBuffer;
		fp= getStream(fp,B[i%2], k); //printf("Buffer: %s \n",B[i%2] );
		char* begin; char* forward;
		begin=forward=B[i%2]; //points to first element of B
		int count=0;
		while(1){
		//printf("\n%d\n",state);
		if(count==k||c=='~'){
			if(!feof(fp)){
				//printf("2nd buffer\n");
				fp= getStream(fp,B[(++i)%2], k); count=0; forward=B[(i)%2]; flag=1; 
				state=0;
				//printf("%s state: %d\n",B[i%2], state);
}//end of first if
			else if(feof(fp)) break;
			}//end of if
		if(*forward=='\n') {lineNumber++; forward++; count++;}
		
		switch(state)
		{ // 1 letter token
			case 0:
				c=*forward;
	if(c=='~') break;
				if(c=='#')
				{
					forward++; count++; 
					state=1;
				}
				
				else if(c==' ')
				{
					forward++; count++; begin=forward; flag=0;
					}
				else if(c=='+')
				{
					forward++; count++;
					state=2;
				}
				else if(c=='-')
				{
					forward++; count++;
					state=3;
				}
				else if(c=='*')
				{
					forward++; count++;
					state=4;
				}
				else if(c=='/')
				{
					forward++; count++;
					state=5;
				}
				else if(c=='@')
				{	
					forward++; count++;
					state=6;
				}
				else if(c=='[')
				{
					forward++; count++;
					state=7;
				}

				else if(c==']')
				{
					forward++; count++;
					state=8;
				}
				else if(c=='(')
				{
					forward++; count++;
					state=9;
				}
				else if(c==')')
				{
					forward++; count++;
					state=10;
				}
				else if(c==';')
				{
					forward++; count++;
					state=11;
				}
				else if(c==',')
				{
					forward++; count++;
					state=12;
				}
				else if(c=='=')
				{	
					forward++; count++;
					state=13;
				}	
				else if(c=='>')
				{	
					forward++; count++;
					state=17;
				}		
				else if(c=='<')
				{
					forward++; count++;
					state=19;
				}
				else if(c=='.')
				{
					forward++; count++;
					state=21;
				}	
				else if(c=='_')
				{
					forward++; count++; //printf("state %d\n",state);
					state=33; //printf("state %d\n",state);
				}
				else if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					forward++; count++;
					state=39;
				}
				else if(c=='e')
				{
					forward++; count++;
					state=42;
				}	
				else if(c=='i')
				{
					forward++; count++;
					state=50;
				}
				else if(c=='r')
				{
					forward++; count++;
					state=54;
				}
				else if(c=='m')
				{
					forward++; count++;
					state	=59;
				}
				else if(c=='s')
				{
					forward++; count++;
					state	=113;
				}
				else if(c=='p')
				{	
					forward++; count++;
					state=65;
				}
				else if(isalphabet(c )&&c!='s'&&c!='e'&&c!='i'&&c!='r'&&c!='m'&&c!='p')
				{
					forward++; count++;
					state=70;
				}
				else if(c=='"')
				{
					forward++; count++;
					state=91;
				}
else if(c=='\n')
				{
					forward++; count++;
					state=0;
				}
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(*forward!=' ') {forward++; count++;}forward++; count++; begin=forward;			
				}
				break;
			case 1:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "#", 85,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "#"); t->tokenIndex=85; t->lineNumber=lineNumber; insertQueue(t, q);
				begin=forward; flag=0;
				break;
			case 2:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "+", 68,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "+"); t->tokenIndex=68; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 3:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "-", 73,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "-"); t->tokenIndex=73; t->lineNumber=lineNumber;insertQueue(t,q);

				begin=forward; flag=0;
				break;
			case 4:
				state=0;
				//fill in the symbol table
                                ////InsertSymbolTable((s, "*", 70,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "*"); t->tokenIndex=70; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 5:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "/", 71,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "/"); t->tokenIndex=71; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 6:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "@", 60,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "@"); t->tokenIndex=60; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 7:
				state=0;
				//fill in the symbol table
				//InsertSymbolTable((s, "[", 47,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "["); t->tokenIndex=47; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 8:
				state=0;
				//fill in the symbol table
				//InsertSymbolTable((s, "]", 48,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "]"); t->tokenIndex=48; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 9:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "(", 62,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "("); t->tokenIndex=62; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 10:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, ")", 63,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, ")"); t->tokenIndex=63; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 11:
				state=0;
				//fill in the symbol table
				
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, ";"); t->tokenIndex=49; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 12:
				state=0;
				//fill in the symbol table
				
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, ","); t->tokenIndex=59; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 13:
				c=*forward;
				if(c=='/')
				{
					forward++; count++;
					state=15;
				}
				else if(c=='=')
				{
					forward++; count++;
					state=14;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "=", 51,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "="); t->tokenIndex=51; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
	
				}
				break;
			case 14:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "==", 79,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "=="); t->tokenIndex=79; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 15:
				c=*forward;
				if(c=='=')
				{
					forward++; count++;
					state=16;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d \n",lexeme, lineNumber);
					while(*forward!=' ') {forward++; count++;}forward++; count++; begin=forward;
				}
				break;
			case 16:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, "=/=", 82,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, "=/="); t->tokenIndex=82; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 17:
				c=*forward;
				if(c=='=')
				{
					forward++; count++;
					state=18;
				}
				if(c!='=')
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, ">", 77,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, ">"); t->tokenIndex=77; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}

				break;
			case 18:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, ">=", 78,lineNumber);
				t=(tokenInfo)malloc(sizeof(token));
				strcpy(t->lexeme, ">="); t->tokenIndex=78; t->lineNumber=lineNumber;insertQueue(t,q);
				begin=forward; flag=0;
				break;
			case 19:
				c=*forward;
				if(c=='=')
				{
					forward++; count++;
					state=20;
				}
				if(c!='=')
				{
					state=0;
					//fill in the symbol table
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "<", 80,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "<"); t->tokenIndex=80; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
					begin=forward; flag=0;
				}
					
				break;
			case 20:
				state=0;
				//fill in the symbol table
				state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "<=", 81,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "<="); t->tokenIndex=81; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
					begin=forward; flag=0;
				break;
			case 21:
				c=*forward;
				if(c=='a')
				{
					forward++; count++;
					state=22;
				}
				else if(c=='o')
				{
					forward++; count++;
					state=26;
				}
				else if(c=='n')
				{
					forward++; count++;
					state=29;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme, lineNumber);
					while(*forward!=' ') {forward++; count++; }forward++; count++; begin=forward;
				}
				break;
			case 22:
				c=*forward;
				if(c=='n')
				{
					forward++; count++;
					state=23;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d \n",lexeme,lineNumber);
					while(*forward!=' ') {forward++; count++;}forward++; count++; begin=forward;
				}
				break;
			case 23:
				c=*forward;
				if(c=='d')
				{
					forward++; count++;
					state=24;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 24:
				c=*forward;
				if(c=='.')
				{
					forward++; count++;
					state=25;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 25:
				state=0;
				//fill in the symbol table
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, ".and.", 75,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, ".and."); t->tokenIndex=75; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				break;
			case 26:
				c=*forward;
				if(c=='r')
				{
					forward++; count++;
					state=27;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 27:
				c=*forward;
				if(c=='.')
				{
					forward++; count++;
					state=28;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;			
			case 28:
				state=0;
				//fill in the symbol table
				state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, ".or.", 76,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, ".or."); t->tokenIndex=76; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				break;
			case 29:
				c=*forward;
				if(c=='o')
				{
					forward++; count++;
					state=30;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 30:
				c=*forward;
				if(c=='t')
				{
					forward++; count++;
					state=31;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 31:
				c=*forward;
				if(c=='.')
				{
					forward++; count++;
					state=28;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s  %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 32:
				state=0;
				//fill in the symbol table
				////InsertSymbolTable((s, ".not.", 83,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, ".not."); t->tokenIndex=83; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				break;			
			case 33://printf("%d hey m here", state);
				c=*forward;
				if(c=='m')
				{
					forward++; count++;
					state=34;
				}
				else if(c!='m'&&isalphabet(c))//and cud be an alphabet only
				{
					forward++; count++;
					state=38;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s  %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}

				break;
			case 34:
				c=*forward;
				if(c=='a')
				{
					forward++; count++;
					state=35;
				}
				else if(c!='a')
				{
					forward++; count++;
					state=38;			
				}
else if(c=='~') break;
				break;
			case 35:
				c=*forward;
				if(c=='i')
				{
					forward++; count++;
					state=36;
				}
				else if(c!='i')
				{
					forward++; count++;
					state=38;			
				}
else if(c=='~') break;
				break;
			case 36:
				c=*forward;
				if(c=='n')
				{
					forward++; count++;
					state=37;
				}
				else if(c!='n')
				{
					forward++; count++;
					state=38;			
				}
else if(c=='~') break;
				break;
			case 37:
				c=*forward;
				if(isalphabet(c))
				{
					forward++; count++;
					state=38;
				}
				else
				{
					state=0;
					//fill in the symbol table
//					printf("insert");
			//InsertSymbolTable((s, "_main", 46,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "_main"); t->tokenIndex=46; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0; //printf("proper");
					
				}
				break;
			case 38:
				c=*forward;
				if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'||isalphabet(c))
				{
					forward++; count++;
					state=38;
				}
				else if(c!='0'||c!='1'||c!='2'||c!='3'||c!='4'||c!='5'||c!='6'||c!='7'||c!='8'||c!='9')
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					////InsertSymbolTable((s, lexeme, 52,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=52; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s  %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 39:
				c=*forward;
				if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					forward++; count++;
					state=39;
				}
				else if(c=='.')
				{
					forward++; count++;
					state=40;
				}
				else
				{
					state=0;
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					////InsertSymbolTable((s, lexeme, 72,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=72; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 40:
				c=*forward;
				if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					forward++; count++;
					state=41;
				}
else if(c=='~') break;
				else
				{
					int b=0; if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';	
					flagError=1; printf("ERROR_3:  Unknown pattern %s  %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 41:
				c=*forward;
				if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					forward++; count++;
					state=41;
				}
				if(c!='0'||c!='1'||c!='2'||c!='3'||c!='4'||c!='5'||c!='6'||c!='7'||c!='8'||c!='9')
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					////InsertSymbolTable((s,lexeme, 73,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=73; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;begin=forward; flag=0;
				}
				break;
			case 42:
				c=*forward;
				if(c=='l')
				{
					forward++; count++;
					state=43;
				}
				else if(c=='n')
				{
					forward++; count++;
					state=46;
				}
				else if(isalphabet(c )&&c!='l'&&c!='n')
				{
					forward++; count++;
					state=71;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					//printf("%s",lexeme);
					debug();
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 43:
				c=*forward;
				if(c=='s')
				{
					forward++; count++;
					state=44;
				}
				else if(isalphabet(c )&&c!='s')
				{
					forward++; count++;
					state=72;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 44:
				c=*forward;
				if(c=='e')
				{
					forward++; count++;
					state=45;
				}
				else if(isalphabet(c )&&c!='e')
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 45:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "else", 64,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "else"); t->tokenIndex=64; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 46:
				c=*forward;
				if(c=='d')
				{
					forward++; count++;
					state=47;
				}
				else if(isalphabet(c )&&c!='s')
				{
					forward++; count++;
					state=72;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
		
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;			
			case 47:
				c=*forward;
				if(c=='i')
				{
					forward++; count++;
					state=48;
				}
				else if(isalphabet(c )&&c!='i')
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "end", 53,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "end"); t->tokenIndex=53; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;			
			case 48:
				c=*forward;
				if(c=='f')
				{
					forward++; count++;
					state=49;
				}
				else if(isalphabet(c )&&c!='f')
				{
					forward++; count++;
					state=74;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 49:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=75;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "endif", 65,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "endif"); t->tokenIndex=65; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 50:
				c=*forward;
				if(c=='f')
				{
					forward++; count++;
					state=51;
				}
				else if(c=='n')
				{
					forward++; count++;
					state=52;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else if(isalphabet(c )&&c!='f'&&c!='n')
				{
					forward++; count++;
					state=71;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 51:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=72;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					
					////InsertSymbolTable((s, "if", 61,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "if"); t->tokenIndex=61; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 52:
				c=*forward;
				if(c=='t')
				{
					forward++; count++;
					state=53;
				}
				else if(isalphabet(c )&&c!='t')
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}				break;				
			case 53:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "int", 55,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "int"); t->tokenIndex=55; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 54:
				c=*forward;
				if(c=='e')
				{
					forward++; count++;
					state=55;
				}
				else if(isalphabet(c )&&c!='e')
				{
					forward++; count++;
					state=71;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 55:
				c=*forward;
				if(c=='a')
				{
					forward++; count++;
					state=56;
				}
				else if(isalphabet(c )&&c!='a')
				{
					forward++; count++;
					state=72;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 56:
				c=*forward;
				if(c=='d')
				{
					forward++; count++;
					state=57;
				}
				else if(c=='l')
				{
					forward++; count++;
					state=58;
				}
				else if(isalphabet(c )&&c!='d'&&c!='l')
				{
					forward++; count++;
					state=73;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 57:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "read", 67,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "read"); t->tokenIndex=67; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 58:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "real", 56,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "real"); t->tokenIndex=56; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;			
			case 59:
				c=*forward;
				if(c=='a')
				{
					forward++; count++;
					state=60;
				}
				else if(isalphabet(c )&&c!='a')
				{
					forward++; count++;
					state=71;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++; //printf("%d %c",state, c);
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 60:
				c=*forward;
				if(c=='t')
				{
					forward++; count++;
					state=61;
				}
				else if(isalphabet(c )&&c!='t')
				{
					forward++; count++;
					state=72;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 61:
				c=*forward;
				if(c=='r')
				{
					forward++; count++;
					state=62;
				}
				else if(isalphabet(c )&&c!='r')
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 62:
				c=*forward;
				if(c=='i')
				{
					forward++; count++;
					state=63;
				}
				else if(isalphabet(c )&&c!='i')
				{
					forward++; count++;
					state=74;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;	
			case 63:
				c=*forward;
				if(c=='x')
				{
					forward++; count++;
					state=64;
				}
				else if(isalphabet(c )&&c!='x')
				{
					forward++; count++;
					state=75;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;			
			case 64:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=76;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "matrix", 58,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "matrix"); t->tokenIndex=58; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;			
			case 65:
				c=*forward;
				if(c=='r')
				{
					forward++; count++;
					state=66;
				}
				else if(isalphabet(c )&&c!='r')
				{
					forward++; count++;
					state=71;
				}
else if(c=='~') break;
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 66:
				c=*forward;
				if(c=='i')
				{
					forward++; count++;
					state=67;
				}
				else if(isalphabet(c )&&c!='i')
				{
					forward++; count++;
					state=72;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 67:
				c=*forward;
				if(c=='n')
				{
					forward++; count++;
					state=68;
				}
				else if(isalphabet(c )&&c!='n')
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 68:
				c=*forward;
				if(c=='t')
				{
					forward++; count++;
					state=69;
				}
				else if(isalphabet(c )&&c!='t')
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 69:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=75;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					////InsertSymbolTable((s, "print", 66,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "print"); t->tokenIndex=66; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 70:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=71;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 71:
				c=*forward;
				if(isalphabet(c))
				{
					forward++; count++;
					state=72;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 72:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;					
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 73:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;					
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 74:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=75;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 75:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=76;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;				
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 76:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=77;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 77:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=78;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 78:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=79;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 79:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=80;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 80:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=81;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;			
			case 81:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=82;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 82:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=83;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 83:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=84;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 84:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=85;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;				}
				break;
			case 85:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=86;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 86:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=87;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 87:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=88;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 88:
				c=*forward;
				if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					forward++; count++;
					state=89;
				}
				else if(isalphabet(c ))
				{
					forward++; count++;
					state=90;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 89:
				c=*forward;
				if(isalphabet(c )||c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					flagError=1; printf("ERROR_3:  Unknown pattern %s  %d\n",lexeme,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
					
					
					//show(B[0]);
					//printf("I am begin<:%c:>",*begin);
					//debug();
					}
				else
				{
					
					state=0;
					//printf("State:%d", state);
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;				}
				break;
			case 90:
				c=*forward;
				if(isalphabet(c )||c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
				{
					flagError=1; 
					printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",lineNumber);
					
					while(!isDelimiter(*forward)&&*forward!='~') {
						//show(B[0]);
						//debug();
						forward++;  
						count++;
						}
					//debug();
					if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
					forward++; count++; begin=forward;
				}
				else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;
			case 91:
				c=*forward;
				while(c==' ') {forward++; c=*forward; count++;} 
				if(isalphabet( c))
				{
					forward++; count++;
					state=92;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
				else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 92:
				c=*forward;
				
				if(isalphabet( c))
				{
					forward++; count++;
					state=93;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 93:
				c=*forward; 
					/*{int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){
	while(*begin!='~'){lexeme[b++]=*begin; begin++; printf("while %c",lexeme[b]);}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0'; printf("Lexeme: %s for state 92\n",lexeme);}*/
				
				if(isalphabet( c))
				{
					forward++; count++;
					state=94;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				
				break;
			case 94:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=95; 
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 95:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=96;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;			
			case 96:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=97;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 97:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=98;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 98:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=99;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 99:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=100;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 100:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=101;
				}
				else if( c=='"')
				{
					forward++; count++; //printf("state 100 %c end",*forward);
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 101:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=102;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 102:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=103;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}				}
				break;
			case 103:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=104;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 104:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=105;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 105:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=106;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 106:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=107;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 107:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=108;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 108:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=109;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 109:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=110;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 110:
				c=*forward;
				if(isalphabet( c))
				{
					forward++; count++;
					state=111;
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 111:
				c=*forward;
				printf("<Hope:%c>",*forward);
				if(isalphabet(c))
				{
					flagError=1; printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n",lineNumber);
										while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							printf("<%c>",*forward);
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				else if( c=='"')
				{
					forward++; count++;
					state=112;
				}
else if(c=='~') break;
				else
				{
					flagError=1; printf("ERROR_2: Unknown Symbol %c at line %d \n",*forward,lineNumber);
					while(!isDelimiter(*forward)){
						if(*forward=='~') {fp=increement(fp); begin=forward=0; c='~'; break;}
						else{
							forward++;  
							count++;
						}
						}
						if(c!='~'){
						forward++; 
						count++; 
						begin=forward;
						}
				}
				break;
			case 112:
				state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){//printf("flag 1");
while(begin!=B[(i+1)%2]+k){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					
					}lexeme[b++]='\0';
					
					////InsertSymbolTable((s,lexeme, 74,lineNumber);
					t=(tokenInfo)malloc(sizeof(token)); 
//printf("hello State %d %s forward:%c hello\n",state, lexeme, *forward);
					strcpy(t->lexeme, lexeme); t->tokenIndex=74; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
					break;
			case 113:
				c=*forward;
				if(c=='t')
				{
					forward++; count++;
					state=114;
				}
				else if(isalphabet(c )&&c!='a')
				{
					forward++; count++;
					state=71;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 114:
				c=*forward;
				if(c=='r')
				{
					forward++; count++;
					state=115;
				}
				else if(isalphabet(c )&&c!='t')
				{
					forward++; count++;
					state=72;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 115:
				c=*forward;
				if(c=='i')
				{
					forward++; count++;
					state=116;
				}
				else if(isalphabet(c )&&c!='r')
				{
					forward++; count++;
					state=73;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;
			case 116:
				c=*forward;
				if(c=='n')
				{
					forward++; count++;
					state=117;
				}
				else if(isalphabet(c )&&c!='i')
				{
					forward++; count++;
					state=74;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;	
			case 117:
				c=*forward;
				if(c=='g')
				{
					forward++; count++;
					state=118;
				}
				else if(isalphabet(c )&&c!='x')
				{
					forward++; count++;
					state=75;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
else if(c=='~') break;
				else
				{
					state=0;
					//fill in the symbol table
					int b=0;
					if(flag==0)while(begin!=forward){lexeme[b++]=*begin; begin++;}
					if(flag==1){while(*begin!='~'){lexeme[b++]=*begin; begin++;}
							begin=B[(i)%2]; while(begin!=forward){lexeme[b++]=*begin; begin++;}
					}lexeme[b++]='\0';
					//InsertSymbolTable((s,lexeme, 54,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, lexeme); t->tokenIndex=54; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;

				}
				break;			
			case 118:
				c=*forward;
				if(isalphabet(c ))
				{
					forward++; count++;
					state=76;
				}
				else if(isdigit(c)){
					forward++; count++;
					state=89;
				}
				else
				{
					state=0;
					//fill in the symbol table
					//InsertSymbolTable((s, "string", 57,lineNumber);
					t=(tokenInfo)malloc(sizeof(token));
					strcpy(t->lexeme, "string"); t->tokenIndex=57; t->lineNumber=lineNumber;insertQueue(t,q);
					begin=forward; flag=0;
				}
				break;	
			
		}//end of switch
	}// end of while
	if(flagError==1) {exit(0);}
	
	return q->Result;
}
