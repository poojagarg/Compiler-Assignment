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
#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif
#include<string.h>
#define numberOfSymbolTables 10
#define size 100
#define sizeOfSymbolTables 100
#define numberOfParameters 10
extern int sflag;
extern int counter;
extern SymbolStack* symbolStack;
extern char* words[];
extern SymbolTable* S[numberOfSymbolTables];
extern int offset[numberOfSymbolTables];
extern int type[numberOfParameters];
extern int typeCounter;
extern int matrixRow,matrixCol;
extern int firstMatrix;
extern int SemanticError;
SymbolTableEntryNode* getSymbolTableNode(ASTnode* ID);
void semanticError(int i, token t){
	if(SemanticError==0){
		SemanticError=1;
		printf("\t\t\t\tSemantic Errors:\n\n");
	}
	switch(i){
	case 0: printf("line number %d:Already declared:%s on line number \n",t.lineNumber,t.lexeme); break;
	case 1: printf("line number %d:Variable %s not declared\n",t.lineNumber,t.lexeme); break;
	case 3: printf("line number %d:recursive function definitions are not allowed, called for function ID: %s \n",t.lineNumber,t.lexeme); break;
	case 4: printf("Wrong Matrix initialization on line number %d\n",  t.lineNumber); break;
	case 5: printf("Mismatch number of output parameters for function call of ID: %s on line number %d\n",t.lexeme, t.lineNumber); break;
	case 6: printf("Wrong LHS for function call of size:%s on line number %d\n",t.lexeme, t.lineNumber); break;	
	case 7: printf("Invalid Print call on line number %d\n",t.lineNumber); break;
	case 8: printf("Wrong input arguments(other than String or Matrix) for size function:%s on line number %d\n",t.lexeme, t.lineNumber); break;
	case 9: printf("String %s is not initialized in Arithmetic Expression on line number%d\n",t.lexeme, t.lineNumber); break;
	case 10: printf("In Assignment statement, LHS and RHS do not match on line number %d\n",t.lineNumber);	break;
		//2 reasons- either items used 	are not initialized, or inappropriate type
	case 11: printf("Matrix %s is not initialized in Arithmetic Expression on line number%d\n",t.lexeme, t.lineNumber); break;
	case 12: printf("Size of matrices in Arithmetic Expression are inconsistent on line number%d\n",t.lineNumber); break;
	case 13: printf("Output parameters are not initialized on line number %d\n",t.lineNumber); break;
	case 14: printf("type mismatch function call of ID: %s on line number %d\n",t.lexeme, t.lineNumber); break;
		}
}
int computeColSize(ASTnode* row){
	if(row==NULL) return 0;
	int count=1;
	ASTnode* G=row->array[1];
	while(G!=NULL){
		count++;
		G=G->array[1];
	}
	return count;
}

SymbolTableEntryNode* findSymbolTableNode(SymbolTableEntryNode* tmp,char* lexeme){
	while(strcmp(tmp->lexeme,lexeme)!=0)
		tmp=tmp->next;
	return tmp;	
}
void delSymbolTable(){
	int i;
	for(i=0; i<counter; i++){
		freeSymbolTable(S[i]);
	}
	counter=0;
}
SymbolTableEntryNode* outputParameterInitCheck(SymbolTable* h,char* lexeme){
	int z=SearchHashTable(h,lexeme);
	if(z==-1) return NULL;//should never be null anyway
	SymbolTableEntryNode *t=findSymbolTableNode(h->table[z].next,lexeme);
	return t;
}
int outputCheck(ASTnode* l){//receives leaf
	do{
		if(!isDeclared(l->array[0])){
			semanticError(1,l->array[0]->t);
			return 0;
		}
		typeCounter++;
		type[typeCounter]=findType(l->array[0],1);
		SymbolTableEntryNode* t=getSymbolTableNode(l->array[0]);
		t->type.id.initialized=1;
		l=l->array[1];		
		}while(l->array[1]!=NULL);
	}
int outputCheck1(ASTnode* leaf){//listVar
	if(!isDeclared(leaf)){
		semanticError(1,leaf->t);
		return 0;
		}
	typeCounter++;
	type[typeCounter]=findType(leaf,1);
	SymbolTableEntryNode* t=getSymbolTableNode(leaf);
	t->type.id.initialized=1;
	}
int findType(ASTnode* ID, int isLHS){//tells type of id
	if(ID==NULL)
		return -1;
	SymbolTable *tmp;	
	int z;
	tmp=topSymbolStack(symbolStack);
	while(tmp!=NULL){
	 	z=SearchHashTable(tmp,ID->t.lexeme);
		if(z!=-1)
			break;
		else tmp=tmp->parentTable;
		}
	if(tmp==NULL){
		semanticError(1,ID->t);
		return -1;
	}
	SymbolTableEntryNode *t=findSymbolTableNode(tmp->table[z].next,ID->t.lexeme);
	if(isLHS)
		return t->type.id.type;//do not check for initialization
	switch(t->type.id.type){
		case 57: if(t->type.id.initialized==1)
				return t->type.id.type;
			else{
				semanticError(9,ID->t);
				return -1;
				}
		case 58:if(t->type.id.initialized==1){
				if(t->type.id.length[0]==-1&&t->type.id.length[1]==-1){
						return t->type.id.type;//size can not be pre-determined
						}
				if(firstMatrix){
					firstMatrix=0;
					matrixRow=t->type.id.length[0];
					matrixCol=t->type.id.length[1];
					return t->type.id.type;
				}
				else if(t->type.id.length[0]==matrixRow&&t->type.id.length[1]==matrixCol)
						return t->type.id.type;
					else{
						semanticError(12,ID->t);
						return -1;
					}
				}
			else
				semanticError(11,ID->t);
		default: return t->type.id.type;	
	}	
}
int findTypeF(ASTnode* F){
	if(F->label==37)//(AE)
		return findTypeAE(F);
	else{
		if(F->label==13){//ID or matrix element
			if(F->array[1]==NULL){
				/*SymbolTableEntryNode *t=getSymbolTableNode(F->array[0]);
				if(t==NULL)
					return -1;
				if(t->type.id.initialized!=1)
					return -1;*/
				return findType(F->array[0],0);
				}
			return 55;// INT, if matrix element then has to be int! Not checking array out of bounds here!
		}
		if(F->label==21){
			//matrixSize[0]=0;
			//matrixSize[1]=0;
		}
		return ASTlabelType(F->label);
		}
}
int findTypeE(ASTnode* E){
	if(E->array[1]==NULL)
		return -1;
	return findTypeAT(E->array[1]);
}
int findTypeAT(ASTnode* AT){
	int l,r;
	if(AT->array[1]==NULL)
		return findTypeF(AT->array[0]);
	else
		if((l=findTypeF(AT->array[0]))==(r=findTypeE(AT->array[1]))){
			if(AT->array[1]->array[0]->label==70||AT->array[1]->array[0]->label==71){
				if(r==57||r==58)//string or matrix in mul or div
					return -1;
				else {
					if(AT->array[1]->array[0]->label==71){//div, so if both type int then return Real
						if(r==55){
						printf("I am where I should be");
							return 56;//return Real instead of int
					}		}		
			
				return l;
			}
			}
			}
			return -1;
}
int findTypeD(ASTnode* D){
	if(D->array[1]==NULL)
		return -1;
	return findTypeAE(D->array[1]);
}
int findTypeAE(ASTnode* AE){
	int l, r;
	if(AE->array[1]==NULL)
		return findTypeAT(AE->array[0]);
	else
		if((l=findTypeAT(AE->array[0]))==(r=findTypeD(AE->array[1]))){
			if(AE->array[1]->array[0]->label==69&&r==57)//if - and type is string, wrong!!
				return -1;
			else return l;
			}
		else 
			return -1;
	}
int findTypeVar(ASTnode* var){
	if(var->label==13){
		if(var->array[1]==NULL)
			return findType(var->array[0],0);
		return 55;//int for matrix element
	}
	return ASTlabelType(var->label);
}
void debug2(char* print){
	int i;
	printf("<%s>",print);
	scanf("%d",&i);
}
int isDeclared(ASTnode* leaf){
	SymbolTable *tmp;
	tmp=topSymbolStack(symbolStack);
	 while(tmp!=NULL){
		if(SearchHashTable(tmp, leaf->t.lexeme)!=-1)
			return 1;
		else tmp=tmp->parentTable;
		}
	if(tmp==NULL){
		return 0;
		}
	return 1;
	}
int findTypeBE(ASTnode* BE){
	ASTnode *lhs,*rhs;
	int z;
	switch(BE->label){
		case 75:// AND
		case 76:// OR
			lhs=BE->array[0];
			rhs=BE->array[1];
			if(findTypeBE(lhs)!=findTypeBE(rhs)){
				return -1;
			}
			return findTypeBE(lhs);
			break;
		case 77:// LT
		case 78:// LE
		case 79:// EQ
		case 80:// GT
		case 81:// GE
		case 82:// NE
			lhs=BE->array[0];
			rhs=BE->array[1];
			if(lhs->label!=54&&rhs->label!=54){//none of them is id
				if(lhs->label==rhs->label)
					return lhs->label;
				else return -1;
			}
			if(lhs->label==54){
				if(!isDeclared(lhs)){
					semanticError(1,lhs->t);
					return -1;
					}
				if(rhs->label==54){
					if(!isDeclared(rhs)){
						semanticError(1,lhs->t);
						return -1;
					}
					if((z=findType(lhs,0))==findType(rhs,0))
						return z;
					else 
						return -1;
				}
				else{
					if(findType(lhs,0)==rhs->label)
						return rhs->label;
					else 
						return -1;
						}
			}
			if(rhs->label==54){
				if(!isDeclared(rhs)){
					semanticError(1,lhs->t);
					return -1;
					}
				if(findType(rhs,0)==lhs->label)
						return lhs->label;
				else 
					return -1;
			}
			break;
			
		case 83:// NOT
			findType(BE->array[0],0);
			break;
	}
	}

SymbolTable* getSymbolTable(ASTnode* ID){
	if(ID==NULL)
		return NULL;
	SymbolTable *tmp;	
	int z;
	tmp=topSymbolStack(symbolStack);
	while(tmp!=NULL){
	 	z=SearchHashTable(tmp,ID->t.lexeme);
		if(z!=-1)
			break;
		else tmp=tmp->parentTable;
		}
	if(tmp==NULL){
		semanticError(1,ID->t);
		return NULL;
	}
	return tmp;
}
int stringToInt(char *lexeme){
	int len=strlen(lexeme);
	int i;
	int num=0;
	int digit;
	int mul=1;
	for(i=len-1; i>=0; i--){
		digit=(int)(lexeme[i]-'0');
		num+=digit*mul;
		mul=mul*10;
	}
	return num;
}
void populateMatrix(SymbolTableEntryNode* t, ASTnode* rows){
	int colSize,curColSize;
	int n=-1;
	int col;
	token bufToken;
	while(rows!=NULL){
		n++;//show present row
		col=-1;
		ASTnode* row=rows->array[0];
		do{
			col++;
			char computeLexeme[20];
			strcpy(computeLexeme,row->array[0]->t.lexeme);
			int num=stringToInt(computeLexeme);
			t->type.id.val.matrixValue[n][col]=num;
			row=row->array[1];
			
			
		}while(row);
		rows=rows->array[1];	
	}
	/*int i,j;
	for(i=0; i<=n;i++){
		for(j=0; j<=col; j++){
			printf("<%d>",t->type.id.val.matrixValue[i][j]);
		}
		printf("\n");
	}*/
	
	}
void MatrixInit(ASTnode* ID,ASTnode* rows){
	ASTnode* rowsMain=rows;
	int colSize,curColSize;
	int n=0;
	token bufToken;
	colSize=computeColSize(rows->array[0]);
	bufToken.lineNumber=rows->array[0]->array[0]->t.lineNumber;
	while(rows!=NULL){
		n++;
		curColSize=computeColSize(rows->array[0]);
		rows=rows->array[1];	
		if(curColSize!=colSize){
			semanticError(4,bufToken);
			return;
			}
	}
	SymbolTableEntryNode* t=getSymbolTableNode(ID);
	SymbolTable* h=getSymbolTable(ID);
	t->type.id.initialized=1;
	t->type.id.length[0]=n;
	t->type.id.length[1]=colSize;
	t->type.id.offset=h->offset;
	populateMatrix(t, rowsMain);
	h->offset+=n*colSize;	
	//printf("Matrix t->lexeme %s, size initialized: %d %d",t->lexeme,t->type.id.length[0],t->type.id.length[1]);
	}
void StringInit(ASTnode* ID,char* lexeme){
	int len=strlen(lexeme);
	SymbolTableEntryNode* t=getSymbolTableNode(ID);
	SymbolTable* h=getSymbolTable(ID);
	t->type.id.initialized=1;
	int i;
	for(i=0; i<len-2;i++){
		t->type.id.val.stringValue[i]=lexeme[i+1];
	}
	//printf("<String:%s>",t->type.id.val.stringValue);
	t->type.id.length[0]=len-2;
	t->type.id.offset=h->offset;
	h->offset+=len;
	//printf("String t->lexeme %s %s, size initialized: %d",t->lexeme,lexeme,t->type.id.length[0]);
}
SymbolTableEntryNode* getSymbolTableNode(ASTnode* ID){
	if(ID==NULL)
		return -1;
	SymbolTable *tmp;	
	int z;
	tmp=topSymbolStack(symbolStack);
	while(tmp!=NULL){
	 	z=SearchHashTable(tmp,ID->t.lexeme);
		if(z!=-1)
			break;
		else tmp=tmp->parentTable;
		}
	if(tmp==NULL){
		semanticError(1,ID->t);
		return -1;
	}
	SymbolTableEntryNode *t=findSymbolTableNode(tmp->table[z].next,ID->t.lexeme);
	return t;
}
int booleanExpressionSemantics(ASTnode* BE){
	ASTnode *lhs,*rhs;
	lhs=BE->array[0];
	rhs=BE->array[1];
	if(findTypeBE(lhs)==findTypeBE(rhs)){
		if(findTypeBE(lhs)!=-1)
		return 1;
		else return 0;
		}
	else return 0;
}
void semantics(ASTnode* ASTroot){
	firstMatrix=1;
	if(ASTroot==NULL){
		return;
	}
	int z,noTraverse=0;
	ASTnode *rows,*l;
	token bufToken;
	SymbolTable *tmp;
	SymbolTableEntryNode *t;
	int p=0;
	if(sflag==0){
		//first time, main function so create a symbol table for main function
		sflag=1;
		S[0]=createSymbolTable(size, NULL, "MAIN");//parentTable of Main is NULL
		symbolStack=createSymbolStack();
		pushSymbolStack(S[0],symbolStack);
		p=1;
		counter++;
		}
		
	switch(ASTroot->label){
	//Symbol Table creates only in 1, 61, 64
	//Symbol table populates in  1:functionDef,31:declarationStmt
		case 1://make a new symbol table, this would be the scope unless an END is encountered, functionDef
			InsertSymbolTable(topSymbolStack(symbolStack), ASTroot);
			S[counter]=createSymbolTable(size, topSymbolStack(symbolStack),ASTroot->array[1]->t.lexeme);
			pushSymbolStack(S[counter],symbolStack);
			InsertSymbolTableFun(topSymbolStack(symbolStack), ASTroot);//for input and output arguments of function
			p=1;
			counter++;
			break;
		case 2://ifstmt
			S[counter]=createSymbolTable(size, topSymbolStack(symbolStack),"IF");
			pushSymbolStack(S[counter],symbolStack);
			p=1;
			counter++;
			break;
		case 3: noTraverse=1;
			if(strcmp(topSymbolStack(symbolStack)->symbolTableName,ASTroot->array[0]->t.lexeme)==0){//checking for Recursion
				
				semanticError(3,ASTroot->array[0]->t);
				return;
				}
			//check for input parameter list and function signature- input and output
			tmp=topSymbolStack(symbolStack);
			 while(tmp!=NULL){
			 	z=SearchHashTable(tmp, ASTroot->array[0]->t.lexeme);
				if(z!=-1)
					break;
				else tmp=tmp->parentTable;
				}
				if(tmp==NULL){
					semanticError(1,ASTroot->t);
					break;
				}//declaration of FunId is checked here itself
				t=findSymbolTableNode(tmp->table[z].next,ASTroot->array[0]->t.lexeme);
				if(t->type.fid.outputSize!=typeCounter){
					semanticError(5,ASTroot->array[0]->t);
					break;
				}
				else{
					for(z=0; z<=t->type.fid.outputSize; z++){
						if(t->type.fid.output[z]!=type[z]){
							semanticError(5,ASTroot->array[0]->t);
							noTraverse=1;
							break;//from for
						}					
				}
					typeCounter=-1;//successfully implemented.
				}
				l=ASTroot->array[1];
				for(z=0; z<=t->type.fid.inputSize; z++){
					if(l==NULL){
						semanticError(5,ASTroot->array[0]->t);//number of output parameters
						noTraverse=1;
						break;
						}
					if(t->type.fid.input[z]!=findTypeVar(l->array[0])){
						semanticError(14,ASTroot->array[0]->t);//type Mismatch
						noTraverse=1;
						break;
					}
					l=l->array[1];					
				}
			break;
		
		case 11://else stmt
			S[counter]=createSymbolTable(size, topSymbolStack(symbolStack),"ELSE");
			pushSymbolStack(S[counter],symbolStack);
			p=1;
			counter++;
			break;	
		case 26:if(ASTroot->array[0]->label==67){
				t=getSymbolTableNode(ASTroot->array[1]);
				t->type.id.initialized=1;
			}
		case 27: break;
		case 28: break; //it should not come
		case 29: break;
		case 30: break;
		case 31://declaration stmt
			InsertSymbolTable(topSymbolStack(symbolStack), ASTroot);
			return;
			break;
		case 51://Assignment
			noTraverse=1;
			typeCounter=-1;
			if(ASTroot->array[1]->label==3){//function call statement
			
				if(ASTroot->array[0]->label==54){//single list
					if(outputCheck1(ASTroot->array[0])==0)//send leaf directly
					return;
				//1- it should already have been declared, 2-if so, then it's type should be recorded
				}
				else{
				//send l
					if(outputCheck(ASTroot->array[0])==0)
						return;
				}
				semantics(ASTroot->array[1]);
			}
			if(ASTroot->array[1]->label==60){//size stmt
				//1- check if ID is declared, 2- What is the type of ID, 3- Compare with the return type
				if(!isDeclared(ASTroot->array[1]->array[0])){
					semanticError(1,ASTroot->array[1]->array[0]->t);
					return;
				}
				z=findType(ASTroot->array[1]->array[0],0);
				if(z==57){
					if(outputCheck(ASTroot->array[0])==0){//it will populate type of LHS if declared, else returns 0
						return;
						}
					else{//declared
						if(!(typeCounter==0&&type[0]==57))
							semanticError(6,ASTroot->array[0]->t);
							return;
						}
					}
				else if(z==58){
					if(outputCheck(ASTroot->array[0])==0){//it will populate type of LHS if declared, else returns 0
						return;
						}
					else{//declared
						if(!(typeCounter==1&&type[0]==55&&type[1]==55))
							semanticError(6,ASTroot->array[0]->t);
							return;
						}
						
					}
				else {
					semanticError(8,ASTroot->array[1]->array[0]->t);//Size contains other that String and Matrix
					}
				}
			if(ASTroot->array[1]->label==37){//Arithmetic Expression
				l=ASTroot->array[0];
				z=findType(l,1);
				if(l->label==54){
					if(z==57){
						if(ASTroot->array[1]->array[1]==NULL){
							if(ASTroot->array[1]->array[0]->array[1]==NULL){
								if(findTypeVar(ASTroot->array[1]->array[0]->array[0])==57){//initialization
									StringInit(ASTroot->array[0],ASTroot->array[1]->array[0]->array[0]->t.lexeme);
									return;				
							}
							}
						}
					}
					else if(z==58){//lhs is matrix
						firstMatrix=1;
						if(ASTroot->array[1]->array[1]==NULL){
							if(ASTroot->array[1]->array[0]->array[1]==NULL){
								if((ASTroot->array[1]->array[0]->array[0]->label)==44){//initialization
									MatrixInit(ASTroot->array[0],ASTroot->array[1]->array[0]->array[0]);			
									return;
								}
							}
						}
					}
										
				}
				if(z==-1)
					break;
				typeCounter++;
				type[typeCounter]=z;
				if((z=findTypeAE(ASTroot->array[1]))!=type[typeCounter]){
					bufToken.lineNumber=l->t.lineNumber;
					semanticError(10,bufToken);
					break;
				}
				//valid Arithmetic expression
				//debug();
				t= getSymbolTableNode(ASTroot->array[0]);
				t->type.id.initialized=1;
				typeCounter=-1;
			}
			break;
		case 52://go to case 54
		case 54: if(!isDeclared(ASTroot))
					semanticError(1,ASTroot->t);
			break;	
		case 75:// AND
		case 76:// OR
		case 77:// LT
		case 78:// LE
		case 79:// EQ
		case 80:// GT
		case 81:// GE
		case 82:// NE
		case 83:// NOTbooleanExpressionSemantics(ASTnode* BE)	
			noTraverse=1;
			if(booleanExpressionSemantics(ASTroot)==0){
				semanticError(10,bufToken);
			}	
		default: break;
			
	}//end of switch
	int i;
	if(noTraverse==0){
		for( i=0; i<ASTroot->arraySize; i++){
			if(ASTroot->array[i]!=NULL){
				semantics(ASTroot->array[i]);
			}
		}
	}
	
	if(p){
		//if popping SymbolTable is a function, then check if it's output parameter are accurately initialised or not
		tmp=popSymbolStack(symbolStack);
		if(strcmp(tmp->symbolTableName,"MAIN")!=0&&strcmp(tmp->symbolTableName,"IF")!=0&&strcmp(tmp->symbolTableName,"ELSE")!=0){//it is a function
			int i;
			for(i=0; i<tmp->outputParameter; i++){
				t=outputParameterInitCheck(tmp,tmp->outputParameterLexeme[i]);
				if(t->type.id.initialized!=1)
					{
						semanticError(13,ASTroot->array[1]->t);
						break;
					}
					}
		}
		}
	
	}//end of function
void displaySemanticsSymboltable(){
	int i;
	printf("\n\n\nIdname\tscope\ttype\toffset\n"); 
	for(i=0; i<counter; i++){
		displayST(S[i]);
		printf("\n");
	}
	//deleteStackSymbolStack(symbolStack);
}
