#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif
#ifndef AST_H
#define AST_H
	#include"AST.h"
#endif
#ifndef ASTDEF_H
#define ASTDEF_H 
	#include"ASTDef.h"
#endif
#ifndef SYMBOLSTACK_H
#define SYMBOLSTACK_H 
	#include"SymbolStack.h"
#endif
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H 
	#include"SymbolTable.h"
#endif
#ifndef LEXER_H
#define LEXER_H
	#include"lexer.h"
#endif
#ifndef PARSER_H
#define PARSER_H
	#include"parser.h"
#endif
#ifndef POSTFIXSTACK_H
#define POSTFIXSTACK_H
	#include"postfixStack.h"
#endif
#define numberOfSymbolTables 10
extern SymbolTable* S[numberOfSymbolTables];
FILE *dataFile,*codeFile;
void dataDeclare(){
	fprintf(dataFile,"%s\n%s\n%s\n",".Model  Tiny",".486",".Data");
	debug("data");
	dataFile=populate(dataFile,S[0]);				
}
char lastVar[256]={"a"};
char* variableGenerator(char lastVar[]){
	int length=strlen(lastVar);
	
	int i=0;
	for(i=0; i<length; i++){
		if(lastVar[i]<'z'){
			lastVar[i]+=1;
			return lastVar;
			}
		/*else{
			printf("come to me");
		}*/
	}
	char newVar[256]={"a"};
	if(i==length){
		return strcat(newVar,lastVar);;
	}	
}
FILE* readDataStmt(FILE* dataFile){
	//lea si,Temp
	
	fprintf(dataFile,"%s db ?\n",lastVar);
	strcpy(lastVar,variableGenerator(lastVar));	 
	fprintf(dataFile,"%s db 32 dup(0)\n",lastVar);
	return dataFile;
	}
FILE* readCodeStmt(FILE* codeFile,ASTnode* t){
	fprintf(codeFile,"LEA DX, maximumInputValue \n");
	fprintf(codeFile,"MOV AH, OAh\n");
	fprintf(codeFile,"INT 21h\n");
	// take String value from lastVar, convert it to integer and then put it into t->t.lexeme Int Type Variable
	return codeFile;							
	}
FILE* printCodeStmt(FILE* codeFile,ASTnode* t){
	fprintf(codeFile,"LEA DX, %s \n",t->t.lexeme);
	fprintf(codeFile,"MOV AH, OAh\n");
	//convert Int value in AH to string and then print
	fprintf(codeFile,"INT 21h\n");
	return codeFile;
}
char* intToString(int n){
	int i=n;
	int digitCount=0;
	while(i!=0){
		digitCount++;
		i=i/10;	
	}
	char string[20];
	if(n==0){
		strcpy(string,"0");
		return string;
		}
	string[digitCount]='\0';
	while(n){
		int d=n%10;
		digitCount--;
		string[digitCount]=d+'0';
		n=n/10;
		}
	return string;
}
void stringCompute(ASTnode* ASTroot){}
void matrixCompute(ASTnode* ASTroot){}
token* t[100];
token* postfixToken[100];
int counterToken=0;
void generatePostfix(ASTnode* ASTroot){
	if(ASTroot==NULL)
		return;
	if(ASTroot->arraySize==0){//leaf
		t[counterToken]=&(ASTroot->t);
		counterToken++;
		return;
	}
	int i;
	for(i=0; i<ASTroot->arraySize; i++){
		if(ASTroot->array[i]!=NULL){
			generatePostfix(ASTroot->array[i]);
			}
		}

}
void infixToPostfix(){
	int i;
	
}
void postFix(ASTnode* ASTroot,FILE* codeFile,FILE* dataFile){
//An assignment statement, make an array of tokens that keep assignment statement
//it would be infix notation, so convert it into posfix
	int i;
	generatePostfix(ASTroot);
	//There is no assignOP after LHS, so take care
	postfixStack* PostfixStack=createpostfixStack();
	pushpostfixStack(51,PostfixStack);	
	infixToPostfix();
}
void createASM(ASTnode* ASTroot){
	ASTnode* t1,*t2;
	int z;
	switch(ASTroot->label){
		case 26:t1=ASTroot->array[0];
			t2=ASTroot->array[1];
			if(t1->label==66){//PRINT
				codeFile= printCodeStmt(codeFile,t2);
			}
			else if(t1->label==67){//READ
					//dataFile=readDataStmt(dataFile);
					codeFile=readCodeStmt(codeFile,t2);
			}
			break;
		case 51:	if(ASTroot->array[1]->label==37){//Arithmetic Expression
				t1=ASTroot->array[0];
				z=findTypeST(t1,0,S[0]);
				if(t1->label==54){//LHS is a single ID, now work on it iff it is of type int or Real
					if(z==55||z==56){
						postFix(ASTroot,codeFile, dataFile);
						//debug();
					}
					if(z==57){//String
						//stringCompute(ASTroot);//to compute in Symbol Table itself
					}
					if(z==58){//Matrix
						//MatrixCompute(ASTroot);//to compute in Symbol Table itself
					}
			}
			}
			break;
		default: break;
		}//end of switch
	
	int i;
	for( i=0; i<ASTroot->arraySize; i++){
			if(ASTroot->array[i]!=NULL){
				createASM(ASTroot->array[i]);
			}
		}
}
void codeGen(ASTnode* ASTroot){
	dataFile=fopen("code.asm","w");
	dataDeclare();
	codeFile=fopen("codeFile.asm","w");
	fprintf(codeFile,"%s\n%s\n",".Code",".Startup");
	//createASM(ASTroot);
	fprintf(codeFile,"%s\n%s\n",".exit","end");
	//cat codeFile dataFile >dataFile
	fclose(codeFile);
	fclose(dataFile);
}
