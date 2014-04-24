#ifndef ASTDEF_H
#define ASTDEF_H 
	#include"ASTDef.h"
#endif
#ifndef LEXER_H
#define LEXER_H
	#include"lexer.h"
#endif
#ifndef PARSER_H
#define PARSER_H
	#include"parser.h"
#endif
#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif

extern char *words[];
ASTnode* FindNPTR(parseTreeNode* p);
ASTnode* makeNode1(int label,ASTnode* p);//1 pointer
ASTnode* makeLeaf(token label);
ASTnode* FindNPTR(parseTreeNode* PT);
void displayAST(ASTnode* root);
ASTnode* makeNode2(int label,ASTnode* p1,ASTnode* p2);
ASTnode* makeNode1(int label, ASTnode* p){//1 pointer
	int size=1;
	ASTnode* a=(ASTnode*)malloc(sizeof(ASTnode));
	a->arraySize=size;
	a->label=label;
	a->array=(ASTnode**)malloc(size*sizeof(ASTnode*));
	a->array[0]=p;	
	return a;
	}
ASTnode* makeNode2(int label,ASTnode *p1,ASTnode *p2){//2 pointers
	int size=2;
	ASTnode* a=(ASTnode*)malloc(sizeof(ASTnode));	
	a->arraySize=size;
	a->array=(ASTnode**)malloc(size*sizeof(ASTnode*));
	a->array[0]=p1;
	a->array[1]=p2;	
	a->label=label;
	return a;	
	}
ASTnode* makeNode3(int label,ASTnode *p1,ASTnode *p2,ASTnode *p3){//2 pointers
	int size=3;
	ASTnode* a=(ASTnode*)malloc(sizeof(ASTnode));	
	a->arraySize=size;
	a->array=(ASTnode**)malloc(size*sizeof(ASTnode*));
	a->array[0]=p1;
	a->array[1]=p2;
	a->array[2]=p3;
	a->label=label;
	return a;	
	}
ASTnode* makeNode4(int label,ASTnode *p1,ASTnode *p2,ASTnode *p3,ASTnode *p4){//2 pointers
	int size=4;
	ASTnode* a=(ASTnode*)malloc(sizeof(ASTnode));	
	a->arraySize=size;
	a->array=(ASTnode**)malloc(size*sizeof(ASTnode*));
	a->array[0]=p1;
	a->array[1]=p2;
	a->array[2]=p3;
	a->array[3]=p4;		
	a->label=label;
	return a;	
	}		
ASTnode* makeLeaf(token t){
	ASTnode* a=(ASTnode*)malloc(sizeof(ASTnode));
	a->array=NULL;
	a->arraySize=0;
	a->label=t.tokenIndex;
	strcpy(a->t.lexeme,t.lexeme);
	a->t.tokenIndex=t.tokenIndex;
	a->t.lineNumber=t.lineNumber;
	return a;
}
extern parseTree root;
parseTreeNode* findParseTreeNode(parseTreeNode* p, int r){
	parseTreeNode* PT=p;
	while(PT!=NULL){
		if(PT->value.isLeafNode==0){
		if(PT->value.p.NonTerminalSymbol==r){
			return PT;
			}}
		else{
			if(PT->value.p.name.tokenIndex==r){
			return PT;
			}
		
		}
		PT=PT->nextSibling;
	}
	
	return NULL;
}


ASTnode* FindNPTR(parseTreeNode* PT){

	if(PT==NULL){	
		return NULL;
	}
	//printParseTree(root,"p.txt");
	ASTnode *a;
	parseTreeNode *tmp1,*tmp2,*tmp3, *tmp4;
	ASTnode *t1,*t2,*t3, *t4;
	if(PT->value.isLeafNode==1){//PT is terminal
		token t=PT->value.p.name; int value;
		return makeLeaf(t);	 	
	}//end of if
	
	else{ //PT is non-Terminal
	int z;//buffer
		switch(PT->value.p.NonTerminalSymbol){
			case 0:	tmp1=findParseTreeNode(PT->children,27);
				return FindNPTR(tmp1);
				break;
			
			case 1:	tmp1=findParseTreeNode(PT->children,34);
				tmp2=findParseTreeNode(PT->children,52);
				tmp3=findParseTreeNode(tmp2,34);
				tmp4=findParseTreeNode(PT->children,27);
			        t1=FindNPTR(tmp1);
			        t2=FindNPTR(tmp2);
			        t3=FindNPTR(tmp3);
			        t4=FindNPTR(tmp4);
			       	return makeNode4(PT->value.p.NonTerminalSymbol,t1,t2,t3,t4);
			        break;
			case 2:  tmp1=findParseTreeNode(PT->children,25);
				tmp2=findParseTreeNode(PT->children,30);
				tmp3=findParseTreeNode(PT->children,38);
				tmp4=findParseTreeNode(PT->children,11);
			        t1=FindNPTR(tmp1);
			        t2=FindNPTR(tmp2);
			        t3=FindNPTR(tmp3);
			        t4=FindNPTR(tmp4);
			       	return makeNode4(2,t1,t2,t3,t4);
			       	
			case 3:tmp1=findParseTreeNode(PT->children,52);
			        t1=FindNPTR(tmp1);
				tmp2=findParseTreeNode(PT->children,39);
			        t2=FindNPTR(tmp2);
			       	return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
			        break;
			case 4:	return FindNPTR(PT->children);
				break;
			case 5:	if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,34);
					return FindNPTR(tmp1);
					}
				break;
				
			case 6:	tmp1=findParseTreeNode(PT->children,54);
				t1=FindNPTR(tmp1);
				tmp2=findParseTreeNode(PT->children,7);
			        t2=FindNPTR(tmp2);
			       	return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
			        break;
			case 7:	if(PT->children->value.p.name.tokenIndex==84){
					//printf("NULL");
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,6);
					return FindNPTR(tmp1);
					}
				break;
			case 8:return makeLeaf(PT->children->value.p.name); 
				break;
			case 9:tmp1=findParseTreeNode(PT->children,6);
				return FindNPTR(tmp1);
				break;
			case 10:tmp1=findParseTreeNode(PT->children,54);
				t1=FindNPTR(tmp1);
				return makeNode1(60,t1);
				break;

			case 11:if(PT->children->value.p.name.tokenIndex==64){
					tmp1=findParseTreeNode(PT->children,30);
					tmp2=findParseTreeNode(PT->children,38);
					t1=FindNPTR(tmp1);				
					t2=FindNPTR(tmp2);
					return makeNode2(11,t1,t2);					

				}
				else	{					
						return NULL;
					}
					break;
			case 12:return makeLeaf(PT->children->value.p.name);
				break;
			case 13:
				if(PT->children->value.isLeafNode==1){
					z=PT->children->value.p.name.tokenIndex;
					switch(z){
					case 54:tmp1=findParseTreeNode(PT->children,54);
						tmp2=findParseTreeNode(tmp1->nextSibling,20);
						t1=FindNPTR(tmp1);				
						t2=FindNPTR(tmp2);
						return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					case 72:
					case 73:
					case 74:return makeLeaf(PT->children->value.p.name);
					}
				}
				else {
					return FindNPTR(PT->children);
				}
				break;
				
			case 14:if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,39);					
					return FindNPTR(tmp1);
					}
				 break;	
			case 15:
			case 16:
			case 17:
			case 18:
			case 19: return makeLeaf(PT->children->value.p.name);	
			case 20:
				if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,72);
					tmp2=findParseTreeNode(tmp1->nextSibling,72);
					t1=FindNPTR(tmp1);				
					t2=FindNPTR(tmp2);
					return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					}
				break;
			case 21:tmp1=findParseTreeNode(PT->children,44);
					return FindNPTR(tmp1);
			case 22:
				tmp1=findParseTreeNode(PT->children,72);
				tmp2=findParseTreeNode(tmp1->nextSibling,45);
				t1=FindNPTR(tmp1);				
				t2=FindNPTR(tmp2);
				return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
			case 23:
				if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,44);
					return FindNPTR(tmp1);				
					}
				break;
					
			case 24:
				if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,72);
					tmp2=findParseTreeNode(tmp1->nextSibling,24);
					t1=FindNPTR(tmp1);				
					t2=FindNPTR(tmp2);
					return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					}
				break;
			case 25:

				if(PT->children->value.isLeafNode==1){
				z=PT->children->value.p.name.tokenIndex;
				switch(z){
				case 62:tmp1=findParseTreeNode(PT->children,25);
					tmp2=findParseTreeNode(tmp1->nextSibling,25);
					t1=FindNPTR(tmp1);				
					t2=FindNPTR(tmp2);
					tmp3=findParseTreeNode(PT->children,17);
					return makeNode2(tmp3->children->value.p.name.tokenIndex,t1,t2);
				case 83:tmp1=findParseTreeNode(PT->children,25);
					t1=FindNPTR(tmp1);				
					return makeNode1(83,t1);				
				}
				}
			else {
					tmp1=findParseTreeNode(PT->children,18);
					tmp2=findParseTreeNode(tmp1->nextSibling,18);
					t1=FindNPTR(tmp1);				
					t2=FindNPTR(tmp2);
					tmp3=findParseTreeNode(PT->children,19);
					return makeNode2(tmp3->children->value.p.name.tokenIndex,t1,t2);
			}
			
			case 26:tmp1=findParseTreeNode(PT->children,12);
					tmp2=findParseTreeNode(PT->children,54);
					t1=FindNPTR(tmp1);				
					t2=FindNPTR(tmp2);
				return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
				break;	
			case 27:tmp1=findParseTreeNode(PT->children,28);
				tmp2=findParseTreeNode(PT->children,29);
				t1=FindNPTR(tmp1);				
				t2=FindNPTR(tmp2);
				return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
				break;
			case 28:if(PT->children->value.p.NonTerminalSymbol==30){
					tmp1=findParseTreeNode(PT->children,30);
					}
				else
					tmp1=findParseTreeNode(PT->children,1);
				return FindNPTR(tmp1);
				break;
			case 29:if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,27);
					return FindNPTR(tmp1);
					}
				break;
			case 30:z=PT->children->value.p.NonTerminalSymbol;
				switch(z){
				
					case 2:tmp1=findParseTreeNode(PT->children,2); 
						break;
					case 3:tmp1=findParseTreeNode(PT->children,3);
						break;
					case 26:tmp1=findParseTreeNode(PT->children,26);
						break;
					case 31:tmp1=findParseTreeNode(PT->children,31);
						break;
					case 32:tmp1=findParseTreeNode(PT->children,32);
						break;
					case 33:tmp1=findParseTreeNode(PT->children,33);
						break;
				}				
				return FindNPTR(tmp1);
				break;
			case 31: tmp1=findParseTreeNode(PT->children,4);
				 tmp2=findParseTreeNode(PT->children,6);
				 t1=FindNPTR(tmp1);
				 t2=FindNPTR(tmp2);
				 return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
				 break;
				 
		 	case 32:tmp1=findParseTreeNode(PT->children,8);
				 tmp2=findParseTreeNode(PT->children,35);
				 t1=FindNPTR(tmp1);
				 t2=FindNPTR(tmp2);
				 return makeNode2(51,t1,t2);//AssignOp
				 break;
			case 33:tmp1=findParseTreeNode(PT->children,9);
				 tmp2=findParseTreeNode(PT->children,36);
				 t1=FindNPTR(tmp1);
				 t2=FindNPTR(tmp2);
				 return makeNode2(51,t1,t2);//AssignOp
				 break;
				 
			case 34: tmp1=findParseTreeNode(PT->children,4);
				tmp2=findParseTreeNode(PT->children,54);
				tmp3=findParseTreeNode(PT->children,5);
				t1=FindNPTR(tmp1);				
				t2=FindNPTR(tmp2);
				t3=FindNPTR(tmp3);
				return makeNode3(PT->value.p.NonTerminalSymbol,t1,t2,t3);
				break;
			case 35:z=PT->children->value.p.NonTerminalSymbol;
				switch(z){
					case 37:tmp1=findParseTreeNode(PT->children,37); 
						break;
					case 10:tmp1=findParseTreeNode(PT->children,10);
						break;
					case 3:tmp1=findParseTreeNode(PT->children,3);
						break;
				}
				return FindNPTR(tmp1);
				break;	
			case 36:return FindNPTR(PT->children);
				break;
			case 37:tmp1=findParseTreeNode(PT->children,40);
				tmp2=findParseTreeNode(PT->children,41);					
				t1=FindNPTR(tmp1);
				 t2=FindNPTR(tmp2);
				 return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
				break;
			case 38:if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,30);
					tmp2=findParseTreeNode(PT->children,38);					
					t1=FindNPTR(tmp1);
				 	t2=FindNPTR(tmp2);
				 	return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					}
				break;
			case 39:if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,13);
					tmp2=findParseTreeNode(PT->children,14);					
					t1=FindNPTR(tmp1);
				 	t2=FindNPTR(tmp2);
				 	return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					}
				break;	
			case 40:tmp1=findParseTreeNode(PT->children,42);
				tmp2=findParseTreeNode(PT->children,43);					
				t1=FindNPTR(tmp1);
				 t2=FindNPTR(tmp2);
				 return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
				break;
				
			case 41:if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,15);
					tmp2=findParseTreeNode(PT->children,37);					
					t1=FindNPTR(tmp1);
				 	t2=FindNPTR(tmp2);
				 	return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					}
				break;	
			case 42:
				if(PT->children->value.isLeafNode==0){
					return FindNPTR(PT->children);
				}
				else
				{
					
					tmp1=findParseTreeNode(PT->children,37); 
					return FindNPTR(tmp1);					
				}
				break;	
			case 43:
				if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					tmp1=findParseTreeNode(PT->children,16);
					tmp2=findParseTreeNode(PT->children,40);					
					t1=FindNPTR(tmp1);
				 	t2=FindNPTR(tmp2);
				 	return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);
					}
				break;	
			case 44:
				 tmp1=findParseTreeNode(PT->children,22);
				 tmp2=findParseTreeNode(PT->children,23);
				 t1=FindNPTR(tmp1);
				 t2=FindNPTR(tmp2);
				 return makeNode2(PT->value.p.NonTerminalSymbol,t1,t2);//AssignOp
				 break;
			case 45: 
				if(PT->children->value.p.name.tokenIndex==84){
					return NULL;
					}
				else {
					
					return FindNPTR(PT->children);	
					}
				break;	 
			default: return NULL;			 
		
		}
		
	}
	
	return a;
}
static int stint=0;
void displayAST(ASTnode* root){
	if(root==NULL)
		return;
	printf("\n<%s>",words[root->label]);
	if(root->arraySize==0){
		printf("-%s>",root->t.lexeme);
	}
	int i;
	if(root->array==NULL) return;
	for(i=0; i<root->arraySize; i++){
		displayAST(root->array[i]);
	}
}
