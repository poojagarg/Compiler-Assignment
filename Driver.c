//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif
#include<stdlib.h>
#ifndef AST_H
#define AST_H
	#include"AST.h"
#endif
#include<stdlib.h>
#ifndef LEXER_H
#define LEXER_H
	#include"lexer.h"
#endif
#ifndef PARSER_H
#define PARSER_H
	#include"parser.h"
#endif
#ifndef SEMANTICS_H
#define SEMANTICS_H
	#include"Semantics.h"
#endif
#ifndef SYMBOLSTACK_H
#define SYMBOLSTACK_H 
	#include"SymbolStack.h"
#endif
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H 
	#include"SymbolTable.h"
#endif
#define numberOfSymbolTables 10
#define sizeOfSymbolTables 100
#define numberOfParameters 10
SymbolTable* S[numberOfSymbolTables];
int offset[numberOfSymbolTables]={0};
int counter=0;
parseTree root;
int SyntaxError=0;
int SemanticError=0;
int typeCounter=-1;
int type[numberOfParameters];
SymbolStack* symbolStack;
int matrixSize[2]={0};
int flag=0;
int sflag=0;
int matrixRow=-1,matrixCol=-1;
int firstMatrix=1;
ASTnode* mainAST;
//Matrix and String should be initialised before using in Arithmetic Expression
int main(int argv,char* args[]){
	int choice; int i;
	system("clear");
	printf("\t\t\t\tCompiler Project- Nikita Bhalla, Pooja Garg\n");
	printf("\t\t1- Print Token List\n");
	printf("\t\t2- Create and Print parse tree\n");
	printf("\t\t3- Print Abstract Syntax tree\n");
	printf("\t\t4- Print all the symbol tables(for all the scopes)\n");
	printf("\t\t5- Front end compile\n");
	printf("\t\t6- Produce assembly code\n");
	printf("\t\t7-Exit\n");
	grammar* g; parseTree  p;
	FILE *fp=fopen(args[1],"r");
	tokenInfo toklist; 
	table T;  
	int flag=1;
	g=createGrammar();
	createParseTable(g,T); 
	
while(flag){
	printf("\n\nEnter your choices\n"); scanf("%d",&choice);	
	switch(choice){
		case 1: toklist= getNextToken(fp); 
			display(toklist);
			break;
		case 2: 
		case 3:
		case 4:
		case 5:
		case 6:
			p=parseInputSourceCode(args[1],T,g);
			if(SyntaxError){
				printf("Syntax Error");
				break;
				}
			if(choice==2) {
				printParseTree(p,args[2]);
				break;
				}
			ASTnode* ASTroot=FindNPTR(p);
			mainAST=ASTroot;
			if(choice==3){		
				displayAST(ASTroot);
				break;
				}
			semantics(ASTroot);
			displaySemanticsSymboltable();
			//delSymbolTable();
			if(choice==6)
				;//codeGen(ASTroot);
			break;
		case 7: flag=0; break;
		}//end of switch
		counter=0;
		SyntaxError=0;
		SemanticError=0;
		typeCounter=-1;
		matrixSize[0]=0;
		matrixSize[1]=0;
		sflag=0;
		fclose(fp);
		fp=fopen(args[1],"r");
	}//end of while	
}// end of main
