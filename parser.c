//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
/*Requires grammar.txt, first.txt, follow.txt file in relevant format*/
#ifndef PARSERDEF_H
#define PARSERDEF_H
	#include"parserDef.h"
#endif
#ifndef AST_H
#define AST_H
	#include"AST.h"
#endif
#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H
	#include"linkedlistStack.h"
#endif
#ifndef STDIO_H
#define STDIO_H
	#include<stdio.h>
#endif

extern char *words[];
//= {"mainFunction","functionDef","ifStmt","funCallStmt","type","remainingList","var_list","more_ids","leftHandSide_singleVar","leftHandSide_listVar","sizeExpression","B","C","var","listVar","operator_lowPrecedence","var","operator_highPrecdence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","row" ,"F","remainingColElements","logicalOp","relationalOp","booleanExpression","ioStmt","stmtsAndFunctionDefs","stmtOrFunctionDef","A","stmt","declarationStmt","assignmentStmt_type1","assignmentStmt_type2","parameter_list","rightHandSide_type1","rightHandSide_type2" ,"arithmeticExpression" ,"otherStmts","inputParameterList","arithmeticExpression","arithmeticTerm","D","factor","E","rows","G","MAIN","SQO","SQC","SEMICOLON","FUNCTION","ASSIGNOP","FUNID","END","ID","INT","REAL","STRING","MATRIX","COMMA","SIZE","IF","OP","CL","ELSE","ENDIF","PRINT","READ","PLUS","MINUS","MUL","DIV","NUM","RNUM","STR","AND","OR","LT","LE","EQ","GT","GE","NE","NOT","EPSILON","$"};
void debug(){
	int i;
	scanf("%d",&i);
}
void createFirst(grammar* g){
	FILE* fp=fopen("first.txt","r");
	int b=0,i=0;
	for(i=0; i<g->count; i++){
	for(b=0; b<NumberOfTerminal; b++)
		g->ntRuleNext[i].FirstSet[b]=-1;}
	while(!feof(fp)){		
		int index,ruleNumber,value=0; 
		fscanf(fp,"%d",&index);
		fscanf(fp,"%d %d",&value,&ruleNumber); 
		if(value<baseTerminal) return; 		
		g->ntRuleNext[index].FirstSet[value-baseTerminal]=ruleNumber;
		if(value==84) g->nullable[index]=1;
	}//end of while
}
void createFollow(grammar* g){
	FILE* fp=fopen("follow.txt","r");
	int b=0,i=0;
	for(i=0; i<g->count; i++){
	for(b=0; b<NumberOfTerminal; b++)
		g->ntRuleNext[i].FollowSet[b]=-1;}	
	while(!feof(fp)){
		int index,ruleNumber,value=0; 
		fscanf(fp,"%d",&index);
		fscanf(fp,"%d %d",&value,&ruleNumber); 
		if(value<baseTerminal) return; 	
		g->ntRuleNext[index].FollowSet[value-baseTerminal]=ruleNumber;
	}//end of while
}
grammar* createGrammar(){
	//FILE* fp2=fopen("ntRules.txt","w");
	grammar* g=NULL;
	int no_of_NT=NumberOfNonTerminal;
	g=(grammar*)malloc(sizeof(grammar));
	g->count=no_of_NT;
	g->ntRuleNext=(NTrule*)malloc((no_of_NT)*sizeof(NTrule));
	int i=0;	
	for(i=0; i<no_of_NT; i++){
		g->ntRuleNext[i].count=0;
		g->ntRuleNext[i].head=NULL;
	}
	FILE* fp=fopen("grammar.txt","r");
	if(!fp) return NULL;
	int index; char ctemp; int itemp;
	while(!feof(fp))
	{ 
		fscanf(fp,"%d",&index);
		Rule* r=(Rule*)malloc(sizeof(Rule));
		int ruleIndex=0;
		
		do{		 
			fscanf(fp,"%d%c",&itemp,&ctemp);			
			r->parts[ruleIndex]=itemp;
			//printf("<%d> ",r->parts[ruleIndex]); 
			ruleIndex++; 
			//fprintf(fp2,"<%d>",itemp); 
			} while(ctemp!='\n'); //end of do
		//printf("\n");
		r->parts[ruleIndex]=-1; //denotes end of the rule
		ruleIndex++;
		r->next=g->ntRuleNext[index].head;
		g->ntRuleNext[index].head=r;	
		//fprintf(fp2,":%d\n",index);			
	}
		g->ntRuleNext[25].head=g->ntRuleNext[index].head->next;//for last line reading error, reading last line twice
		//g->ntRuleNext[1].head->parts[10]=53;
		//g->ntRuleNext[1].head->parts[11]=49;
		//g->ntRuleNext[1].head->parts[12]=-1;
	for(i=0; i<g->count; i++)	g->nullable[i]=0;
	createFirst(g); createFollow(g); 
	//computeNullable(g);
	return g;	
}
void computeNullable(grammar* g){
	FILE* fp=fopen("grammar.txt","r"); int tmp;
	while(!feof(fp)){
		fscanf("%d",&tmp); g->nullable[tmp]=1;
		}//end of while
}
void createParseTable(grammar* g, table T){
	int i,j; 	
	for(i=0; i<g->count; i++){
		for(j=0;j<NumberOfTerminal;j++){
			T[i][j]=g->ntRuleNext[i].FirstSet[j]; //gives rule no. for terminal digit representation baseTerminal+j
			if(g->nullable[i]){
				if(g->ntRuleNext[i].FollowSet[j]!=-1)
				T[i][j]=g->ntRuleNext[i].FollowSet[j]; 
	}
		}//end of for
	}//end of 2nd for
}//end of function
void printParseTable(grammar* g, table T){
	FILE* fp;
	fp=fopen("predictiveParserTable.txt","w");
	int i,j; 	
	for(i=0; i<g->count; i++){
		for(j=0;j<NumberOfTerminal;j++){
			fprintf(fp,"%d\t",T[i][j]); //gives rule no. for terminal digit representation baseTerminal+j
		}//end of for
	fprintf(fp,"END\n");
	}//end of 2nd for
}//end of function
extern int SyntaxError;
void printSyntaxError(int i){
	switch(i){
		case 0: printf("top of stack is epsilon and still tokens are left\n"); break;
		case 1: printf("top of stack is there but no tokens are left\n"); break;
		case 2: printf("terminal of top of stack is different from token\n"); break;	
		case 3: printf("No entry for existing combination in parseTable\n"); break;
		case 4: printf("Stack is improperly populated\n");
}//end of switch
 SyntaxError=1;
}
parseTree createRootParseTree(parseNodeValue value){
	parseTree p;
	p->value=value; p->nextSibling=NULL; p->children=NULL;
	return p;
}

void createChildParseTreeNode(parseTreeNode* parent,parseTreeNode* child){
	child->nextSibling=parent->children;
	parent->children=child;
	child->children=NULL;
}
void printNTRule(grammar* g){
	int i,j;
	FILE* fp3=fopen("ntrules2.txt","w");
	//fprintf(fp3,"writing");
	if(!fp3) {printf("can't open"); return;}
	if(!g)	{printf("grammar does not exist"); return;}
	for(i=0; i<g->count; i++){
		Rule* r=g->ntRuleNext[i].head;
		//printf("index:%d->",i);
		fprintf(fp3,"\nindex:%d->",i);
		while(r){
			int ruleIndex=0;
			fprintf(fp3,"\n");
			while(r->parts[ruleIndex]>=0){				
				//printf("%d",r->parts[ruleIndex]);			
				fprintf(fp3,"<%d>",r->parts[ruleIndex]);
				ruleIndex++;}// end of while
			r=r->next;}//end of outer while
		}//end of for
close(fp3);
}
parseTree parseInputSourceCode(char *testcaseFile, table T, grammar* g){
	
	parseTree p;
	FILE* f=fopen(testcaseFile,"r");
	tokenInfo t= getNextToken(f); //populates Symbol table also
	linkedlistStack* parseStack=create();
	parseTree tmp=(parseTreeNode*)malloc(sizeof(parseTreeNode));
	tmp->value.isLeafNode=1; 
	tmp->value.p.name.tokenIndex=85; 
	tmp->value.p.NonTerminalSymbol=0;
	push(tmp,parseStack); //change this to its integer value
	tmp=(parseTreeNode*)malloc(sizeof(parseTreeNode));	
	tmp->value.isLeafNode=0; 
	tmp->value.p.NonTerminalSymbol=0; 
	tmp->value.parentNodeSymbol=0;
	push(tmp,parseStack); //change Start Symbol to its integer value
	p=tmp; 
	p->nextSibling=NULL; 
	p->children=NULL;
	parseTreeNode* topPT;
	 // no. of nodes in parsetree p
	while(top(parseStack)!=NULL)
	{       
		int topIntValue;
		if(top(parseStack)->value.isLeafNode==1){
			topIntValue=top(parseStack)->value.p.name.tokenIndex;
			//printf("<Leaf: %d>",topIntValue);
			}
		else {
			topIntValue=top(parseStack)->value.p.NonTerminalSymbol;
			//printf("<Non: terminal: %d>",topIntValue);
			}
			
			
		if(topIntValue==84) {//top of stack is Epsilon
			pop(parseStack); 
			continue;
			}
		if(topIntValue==85 && t==NULL){ //top of stack is Dollar and no more tokens=>Success
			//printf("check 0");
			return p;}
		if(topIntValue==85 && t!=NULL){//top of stack is epsilon and still tokens are left
			//printf("check 1");			
			printSyntaxError(0); 
			return p; 
			}// end of if
		if(t==NULL){
			int tmp;
			//printf("check 2");
			while(topIntValue!=85){
				if(top(parseStack)->value.isLeafNode==1)
					topIntValue=top(parseStack)->value.p.name.tokenIndex;
				else 
					topIntValue=top(parseStack)->value.p.NonTerminalSymbol;
				if(topIntValue==85) {
					return p;
					}
				if(topIntValue>=baseTerminal) {
					printSyntaxError(1); 
					return p;
					}
				if(!g->nullable[topIntValue]){
					printSyntaxError(1); 
					return p;
					}//end of if
				pop(parseStack);			
				}//end of while
			return p; //success
			}
		if(topIntValue>=baseTerminal){
				
			token* tmp;
			if(t->tokenIndex==topIntValue) {
			top(parseStack)->value.p.name.lineNumber=t->lineNumber;
			top(parseStack)->value.p.name.next=t->next;
			strcpy(top(parseStack)->value.p.name.lexeme,t->lexeme);
			pop(parseStack); 
			tmp=t; 
			t=t->next; 
			free(tmp); 
			continue;
			}
			else {
				printSyntaxError(2); 
				return p;
				}
		}//end of if
		
		else { 	//it is a non-terminal
			//printf("non-terminal else"); 
			/*if(t->tokenIndex==64)	
				debug();
			if(t->tokenIndex==38){	
				printf("<token:%d>",t->tokenIndex);
				debug();
				}*/
			topPT=pop(parseStack);
			if(topIntValue<0) {// No need
				printSyntaxError(4); 
				return p;
				}
			if(topIntValue>=baseTerminal) {// No need
				printSyntaxError(4); 
				return p;
				}
			//printf("<t->tokenIndex-baseTerminal:%d>",t->tokenIndex-baseTerminal);
			int count=T[topIntValue][(t->tokenIndex)-baseTerminal];//determine rule no.
			/*if(topIntValue==11){
			printf("<t->tokenIndex-baseTerminal:%d %s, count: %d>",t->tokenIndex-baseTerminal,t->lexeme,count);
			debug();
			}*/
			if(count<0) {printSyntaxError(3); return p;}						
			Rule* r=g->ntRuleNext[topIntValue].head;
			while(count>0) {r=r->next; count--;}
			int ruleIndex=0; 
			while(r->parts[ruleIndex]!=-1) {
				ruleIndex++;
			}
			int z;
			token* tmpToken=t;			
			for(z=ruleIndex-1; z>=0; z--){
				tmp=(parseTreeNode*)malloc(sizeof(parseTreeNode));
				tmp->value.parentNodeSymbol=topIntValue;
				if(r->parts[z]>=baseTerminal){
					tmp->value.isLeafNode=1; 
					strcpy(tmp->value.p.name.lexeme,tmpToken->lexeme);
					tmpToken=tmpToken->next;
					tmp->value.p.name.tokenIndex=r->parts[z];
					if(topIntValue==2) {
						//printf("%s %d",tmp->value.p.name.lexeme,r->parts[z]); 
						//debug();
						}
					}
				else{
					tmp->value.isLeafNode=0; 
					tmp->value.p.NonTerminalSymbol=r->parts[z];
					if(topIntValue==2) {
						//printf("%s",words[tmp->value.p.NonTerminalSymbol]);	
						//debug();
						}				
					}
				 push(tmp,parseStack); 
				 createChildParseTreeNode(topPT,tmp);//maintaining a stack
				 
			//printf("<pooja>");
			}
			//displayStack(parseStack);
			//debug();
		}//end of else  if		
	}//end of while
return p;	
}//end of function
void printParseTree(parseTree  PT, char *outfile){
	
	if(PT==NULL) {
		//printf("NULL"); 
		return;}
	FILE* fp;
	fp=fopen(outfile,"w");
	if(PT->value.isLeafNode==0){//non-Terminal		
		printf("---%d\t NO \t%d\n",PT->value.parentNodeSymbol,PT->value.p.NonTerminalSymbol);
		}
	else{
		token t=PT->value.p.name; int value;
		if(t.tokenIndex==72||t.tokenIndex==73){
			printf("t.lexeme:%s\tt.lineNumber:%d\tt.tokenIndex:%d\tt.lexeme:%s\tPT->value.parentNodeSymbol:%dYES\n",t.lexeme,t.lineNumber,t.tokenIndex,t.lexeme,PT->value.parentNodeSymbol);
}
		else{
			printf("t.lexeme:%s\tt.lineNumber:%d\tt.tokenIndex:%d\t-\tPT->value.parentNodeSymbol:%dYES\n",t.lexeme,t.lineNumber,t.tokenIndex,PT->value.parentNodeSymbol);
}
		}//end of outer else*/
	printParseTree(PT->children,outfile);
	printParseTree(PT->nextSibling,outfile);
	fclose(fp);		
}
