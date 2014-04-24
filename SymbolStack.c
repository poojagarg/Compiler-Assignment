#ifndef STDIO_H
	#include<stdio.h>
#endif
#ifndef STDLIB_H
	#include<stdlib.h>
#endif
#ifndef SYMBOLSTACKDEF_H
	#include"SymbolStackDef.h"
#endif

SymbolStack* createSymbolStack(){
	SymbolStack* s=(SymbolStack*)malloc(sizeof(SymbolStack));
	if(!s) return NULL;
	s->count=0;
	s->top=NULL;
	return s;
}
int isEmptySymbolStack(SymbolStack* s){
	if(s->top==NULL) return 1;
	else return 0;
}
void pushSymbolStack(SymbolTable* value,SymbolStack* s){
	SymbolStackNode* n=(SymbolStackNode*)malloc(sizeof(SymbolStackNode));
	n->value=value;
	n->next=s->top;
	s->top=n;
}
SymbolTable* popSymbolStack(SymbolStack* st){
	if(st->top==NULL) return NULL;
	else{
		SymbolTable* value=st->top->value;
		SymbolStackNode* tmp=st->top;
		st->top=st->top->next;
		free(tmp);
		return value;		
	}
}
SymbolTable* topSymbolStack(SymbolStack* s){
	if(s->top==NULL) return NULL;
	else{
		SymbolTable* value=s->top->value;
		
		return value;		
	}
}
void deleteStackSymbolStack(SymbolStack* s){
	if(s!=NULL){
		SymbolStackNode* tmp;
		while(s->top!=NULL){
			tmp=s->top;	
			s->top=s->top->next;
			free(tmp);
			}//end of while
		free(s);
		}//end of if
}
