//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
/*#ifndef _STDIO_H
	#define _STDIO_H*/
	#include<stdio.h>
//#endif
#ifndef _STDLIB_H
	#define _STDLIB_H
	#include<stdlib.h>
#endif
#ifndef _LINKEDLISTSTACKDEF_H
	#define _LINKEDLISTSTACKDEF_H
	#include"linkedlistStackDef.h"
#endif
linkedlistStack* create(){
	linkedlistStack* s=(linkedlistStack*)malloc(sizeof(linkedlistStack));
	if(!s) return NULL;
	s->count=0;
	s->top=NULL;
	return s;
}
void push(parseTreeNode* value,linkedlistStack* s){
	node* n=(node*)malloc(sizeof(node));
	n->value=value;
	n->next=s->top;
	s->top=n;
	s->count++;	
}
parseTreeNode* pop(linkedlistStack* s){
	if(s==NULL) {printf("bogus"); return NULL;}
	if(s->top==NULL) {printf("2"); return NULL;}
	else{	
		//printf("3");
		node* tmp=s->top;
		parseTreeNode* temp=tmp->value;
		s->top=tmp->next;
		s->count--;
		//free(tmp);
		return temp;		
	}
}
parseTreeNode* top(linkedlistStack* s){
	if(s->top==NULL) return NULL;
	else{
		return s->top->value;}
}
void displayStack(linkedlistStack* st){
	linkedlistStack* s=st;
	if(s){
		node* tmp;
		tmp=s->top;
		while(tmp!=NULL){
			if(tmp->value->value.isLeafNode){
				printf("Leaf:%d\n",tmp->value->value.p.name.tokenIndex);}
			else{printf("NT:%d\n",tmp->value->value.p.NonTerminalSymbol);}
			tmp=tmp->next;
			}//end of while		
		}//end of if
	printf("Displayed the stack");
}
void deleteStack(linkedlistStack* s){
	if(s){
		node* tmp;
		tmp=s->top;
		while(tmp!=NULL){
			tmp=s->top;	
			s->top=s->top->next;
			free(tmp);
			}//end of while
		free(s);
		}//end of if
}
