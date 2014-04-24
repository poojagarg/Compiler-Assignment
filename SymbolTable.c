#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H 
	#include"SymbolTableDef.h"
#endif
#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif
#ifndef ASTDEF_H
#define ASTDEF_H 
	#include"ASTDef.h"
#endif
int typeSize[2]={2,4};
//typeSize[0]=2//for int
//typeSize[1]=4; //for Real
#define maxMatrixRowSize 10
#define maxMatrixColSize 10
#define maxStringSize 20
extern char* words[];
extern ASTnode* mainAST;
SymbolTable* CreateSymbolTable(int size,SymbolTable* parent, char* name);
int SearchHashTable(SymbolTable* h, char* lexeme);
int InsertSymbolTableFun(SymbolTable* h, ASTnode* ASTroot);
int InsertSymbolTable(SymbolTable* h, ASTnode* ASTroot);
int HashKey(char* lexeme, int size);
void displayST(SymbolTable* h);

SymbolTable* createSymbolTable(int size,SymbolTable* parent, char* name){
	SymbolTable* s;
	s=(SymbolTable*)malloc(sizeof(SymbolTable));
	if(!s)
		return NULL; // symbol table could not be created
	s->size=size;
	s->count=0;
	s->table=(SymbolTableEntry*)malloc(size*sizeof(SymbolTableEntry));
	int i;	
	for(i=0; i<size; i++){
		s->table[i].count=0;
		s->table[i].next=NULL;
	}
	strcpy(s->symbolTableName, name);
	s->parentTable=parent;
	s->offset=0;
	s->outputParameter=0;
	return s;
	}
int SearchHashTable(SymbolTable* h, char* lexeme){
	if(h==NULL){
		return -1;
		}	
	int index=HashKey(lexeme, h->size);
	if(index>=h->size) return -1;
	SymbolTableEntryNode* tmp=h->table[index].next;
	if(tmp==NULL)
		return -1;
	while(tmp!=NULL){
		if(!strcmp(tmp->lexeme,lexeme))
			return index;
		tmp=tmp->next;
	}//end of while
	return -1; // not found
}
int ASTlabelType(int label){
	switch(label){
	case 44:// rows, for matrix
		return 58;
	case 72://NUM
		return 55;
	case 73://RNUM
		return 56;
	case 74://STR
		return 57;
	default: return label;
	}
}		
int InsertSymbolTableFun(SymbolTable* h, ASTnode* ASTroot){
		ASTnode* pl1=ASTroot->array[0];
			
		char* lexeme;
		do{
			int type=ASTlabelType(pl1->array[0]->label);
			ASTnode* p=pl1->array[1];
			strcpy(lexeme,p->t.lexeme);
			SymbolTable* tmp=h;
			while(tmp!=NULL){
	 			int z=SearchHashTable(tmp,lexeme);
				if(z!=-1)
					break;
				else tmp=tmp->parentTable;
				}
			if(tmp!=NULL){
				semanticError(0,p->t);
			}
			else{
				SymbolTableEntryNode* newNode;
				newNode=(SymbolTableEntryNode*)malloc(sizeof(SymbolTableEntryNode));
				newNode->i=1;
				strcpy(newNode->lexeme,lexeme);
				newNode->type.id.type=type;
				newNode->type.id.offset=h->offset;
				if(type==55||type==56){
					h->offset+=typeSize[type-55];
					}
				else{// is a string or Matrix which should have been initialized in functionCall statement
					if(type==57){
						h->offset+=maxStringSize;
					}
					else if(type==58){//matrix
						h->offset+=maxMatrixRowSize*maxMatrixColSize;
					}
				}
				int index=HashKey(lexeme, h->size);
				newNode->next=h->table[index].next; //making a stack
				h->table[index].next=newNode;
				h->table[index].count++;
				h->count++;
				strcpy(h->outputParameterLexeme[h->outputParameter],lexeme);
				h->outputParameter++;
			}
			if(pl1->array[2]==NULL){
				break;
			}
			else{
				pl1=pl1->array[2];
			}
		}while(1);
		pl1=ASTroot->array[2];
		do{
			int type=ASTlabelType(pl1->array[0]->label);
			ASTnode* p=pl1->array[1];
			strcpy(lexeme,p->t.lexeme);
			SymbolTable* tmp=h;
			while(tmp!=NULL){
	 			int z=SearchHashTable(tmp,lexeme);
				if(z!=-1)
					break;
				else tmp=tmp->parentTable;
				}
			if(tmp!=NULL){
				semanticError(0,p->t);
			}
			else{
				SymbolTableEntryNode* newNode;
				newNode=(SymbolTableEntryNode*)malloc(sizeof(SymbolTableEntryNode));
				newNode->i=1;
				strcpy(newNode->lexeme,lexeme);
				newNode->type.id.type=type;
				newNode->type.id.offset=h->offset;
				if(type==55||type==56){
					h->offset+=typeSize[type-55];//for int, type=55
					}
				else{// is a string or Matrix which should have been initialized in functionCall statement
					if(type==57){
						h->offset+=maxStringSize;
					}
					else if(type==58){//matrix
						h->offset+=maxMatrixRowSize*maxMatrixColSize;
					}
				}
				newNode->type.id.initialized=1;
				if(type==58){//matrix
					newNode->type.id.length[0]=-1;//any dummy
					newNode->type.id.length[1]=-1;//any dummy
				}
				int index=HashKey(lexeme, h->size);
				newNode->next=h->table[index].next; //making a stack
				h->table[index].next=newNode;
				h->table[index].count++;
				h->count++;
			}
			if(pl1->array[2]==NULL){
				break;
			}
			else{
				pl1=pl1->array[2];
			}
		}while(1);
		return 1; //added successfully in the table
}
int InsertSymbolTable(SymbolTable* h, ASTnode* ASTroot){
	char lexeme[50];
	if(ASTroot->label==1){
		strcpy(lexeme,ASTroot->array[1]->t.lexeme);//storing funID as lexeme
		SymbolTable* tmp=h;
		while(tmp!=NULL){
	 		int z=SearchHashTable(tmp,lexeme);
			if(z!=-1)
				break;
			else tmp=tmp->parentTable;
			}
		if(tmp!=NULL){
			semanticError(0,ASTroot->array[1]->t);
			return 0; //exists already
		}
		SymbolTableEntryNode* newNode;
		newNode=(SymbolTableEntryNode*)malloc(sizeof(SymbolTableEntryNode));
		strcpy(newNode->lexeme,lexeme);
		newNode->i=0;
		ASTnode* pl1=ASTroot->array[0];
		int inputSize=-1,outputSize=-1;
		do{		
		outputSize++;
		newNode->type.fid.output[outputSize]=ASTlabelType(pl1->array[0]->label);
		if(pl1->array[2]!=NULL){
			pl1=pl1->array[2];
		}
		else break;		
		}while(1);
		ASTnode* pl2=ASTroot->array[2];
		do{		
		inputSize++;
		newNode->type.fid.input[inputSize]=ASTlabelType(pl2->array[0]->label);
		if(pl2->array[2]!=NULL){
			pl2=pl2->array[2];
		}
		else break;		
		}while(1);	
		newNode->type.fid.inputSize=inputSize;
		newNode->type.fid.outputSize=outputSize;
		int index=HashKey(lexeme, h->size);
		newNode->next=h->table[index].next; //making a stack
		h->table[index].next=newNode;
		h->table[index].count++;
		h->count++;
		return 1; //added successfully in the table
	}//end of filling ASTroot
	else{
		int type=ASTlabelType(ASTroot->array[0]->label);//type leaf is array 0
		ASTnode* vl=ASTroot->array[1];;//varlist
		do{
			
			strcpy(lexeme,vl->array[0]->t.lexeme);
			SymbolTable* tmp=h;
			while(tmp!=NULL){
	 			int z=SearchHashTable(tmp,lexeme);
				if(z!=-1)
					break;
				else tmp=tmp->parentTable;
				}
			if(tmp!=NULL){
				semanticError(0,vl->array[0]->t);
			}
			else{
				SymbolTableEntryNode* newNode;
				newNode=(SymbolTableEntryNode*)malloc(sizeof(SymbolTableEntryNode));
				newNode->i=1;
				strcpy(newNode->lexeme,lexeme);
				newNode->type.id.type=type;
				newNode->type.id.offset=h->offset;
				if(type==55||type==56){
					h->offset+=typeSize[type-55];
					}
				else{// is a string or Matrix which should have been initialized in functionCall statement
					if(type==57){
						newNode->type.id.offset=-1;
					}
					else if(type==58){//matrix
						newNode->type.id.offset=-1;
					}
				}
				int index=HashKey(lexeme, h->size);
				newNode->next=h->table[index].next; //making a stack
				h->table[index].next=newNode;
				h->table[index].count++;
				h->count++;
				}
			vl=vl->array[1];
	}while(vl!=NULL);
	return 2; //added ID list in the table
	}//end of else	
}
int HashKey(char* lexeme, int size){
	int i,sum=0;
	int length=strlen(lexeme);
	for(i=0; i<length; i++)sum+=lexeme[i];
	return sum%size;
}
void freeSymbolTable(SymbolTable* h){
	if(h==NULL)
		return;
	int i;
	for(i=0; i<h->size; i++){
		SymbolTableEntryNode* f;
		SymbolTableEntryNode* t=h->table[i].next;
		while(t!=NULL){
			f=t;
			t=t->next;
			free(f);
		}
	}
	free(h);
}
void displayST(SymbolTable* h){
	if(h==NULL) return;
	int i;
	for(i=0; i<h->size; i++){
		SymbolTableEntryNode* t=h->table[i].next;
		while(t!=NULL){
			if(t->i==1){//id
				if(t->type.id.offset!=-1)
				printf("\n%s\t%s\t%d\t%d\n",t->lexeme,h->symbolTableName,t->type.id.type,t->type.id.offset);	
				/*if(t->type.id.offset==-1){
				//not initialized therefore no need to show
				printf("\n%s\t%s\t%d\t%d%d\n",t->lexeme,h->symbolTableName,t->type.id.type,t->type.id.offset,t->type.id.initialized);	
				}*/
			}
			/*else{//fid
				int tmp;
				printf("<%s,%s>",t->lexeme,h->symbolTableName);	
				printf("\tInput Arguments:");
				for(tmp=0; tmp<=t->type.fid.inputSize; tmp++){
					printf("<%s>",words[t->type.fid.input[tmp]]);
				}
				printf("\n");
				printf("\tOutput Arguments:");
				for(tmp=0; tmp<=t->type.fid.outputSize; tmp++){
					printf("<%s>",words[t->type.fid.output[tmp]]);
				}
				printf("\n");
			}*/
			t=t->next;
		}
		
	}
}
FILE* populate(FILE* codeFile,SymbolTable* h){	
	int i;
	displayST(h);
	for(i=0; i<h->size; i++){
		SymbolTableEntryNode* t=h->table[i].next;
		while(t!=NULL){
			if(t->i==1){//id
				if(t->type.id.type==55){
					fprintf(codeFile, "%s db ?\n",t->lexeme);
					}
				if(t->type.id.type==56){
					fprintf(codeFile, "%s dd ?\n",t->lexeme);
					}
			}
			t=t->next;
		}
		
	}
		fprintf(codeFile, "maximumInputValue dd 32\n");
		fprintf(codeFile, "Temp db 10dup(0)\n");
	return codeFile;
}
void deleteUninitVar(SymbolTable* h){//deletes those string and matrix whose offset=-1;

}
