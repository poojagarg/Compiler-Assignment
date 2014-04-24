#ifndef _STDIO_H
	#include<stdio.h>
#endif
#ifndef _STDLIB_H
	#include<stdlib.h>
#endif
#ifndef  _POSTFIXSTACKDEF_H
	#include"postfixStackDef.h"
#endif
postfixStack* createpostfixStack(){
	postfixStack* s=(postfixStack*)malloc(sizeof(postfixStack));
	if(!s) return NULL;
	s->count=0;
	s->top=NULL;
	return s;
}
int isEmptypostfixStack(postfixStack* s){
	if(s->top==NULL) return 1;
	else return 0;
}
void pushpostfixStack(int value,postfixStack* s){
	postnode* n=(postnode*)malloc(sizeof(postnode));
	n->value=value;
	n->next=s->top;
	s->top=n;
}
int poppostfixStack(postfixStack* s){
	if(s->top==NULL) return -1;
	else{
		int temp=s->top->value;
		postnode* tmp=s->top;
		s->top=s->top->next;
		free(tmp);
		return temp;		
	}
}
void deletepostfixStack(postfixStack* s){
	if(s){
		postnode* tmp;
		tmp=s->top;
		while(tmp!=NULL){
			tmp=s->top;	
			s->top=s->top->next;
			free(tmp);
			}//end of while
		free(s);
		}//end of if
}
