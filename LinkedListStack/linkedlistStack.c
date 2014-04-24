#ifndef _STDIO_H
	#include<stdio.h>
#endif
#ifndef _STDLIB_H
	#include<stdlib.h>
#endif
#ifndef  _LINKEDLISTSTACKDEF_H
	#include"linkedlistStackDef.h"
#endif
SymbolTable* popSymbolStack(SymbolStack* s);
int isEmptyStack(SymbolStack* s);
void deleteSymbolStack(SymbolStack* s);
SymbolStack* createSymbolStack(){
	SymbolStack* s=(SymbolStack*)malloc(sizeof(SymbolStack));
	if(!s) return NULL;
	s->count=0;
	s->top=NULL;
	return s;
}
int isEmptyStack(linkedlistStack* s){
	if(s->top==NULL) return 1;
	else return 0;
}
void pushSymbolStack(SymbolTable* value,SymbolStack* s){
	SymbolStackNode* n=(node*)malloc(sizeof(node));
	n->value=value;
	n->next=s->top;
	s->top=n;
}
SymbolTable* popSymbolStack(SymbolStack* s){
	if(s->top==NULL) return -1;
	else{
		SymbolTable* value=s->top->value;
		SymbolStackNode* tmp=s->top;
		s->top=s->top->next;
		free(tmp);
		return value;		
	}
}
void deleteSymbolStack(SymbolTable* s){
	if(s){
		SymbolStackNode* tmp;
		tmp=s->top;
		while(tmp!=NULL){
			tmp=s->top;	
			s->top=s->top->next;
			free(tmp);
			}//end of while
		free(s);
		}//end of if
}
