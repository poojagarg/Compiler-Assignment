#include<stdio.h>
char *words[]=  {"mainFunction","functionDef","ifStmt","funCallStmt","type","remainingList","var_list","more_ids","leftHandSide_singleVar","leftHandSide_listVar","sizeExpression","B","C","var","listVar","operator_lowPrecedence","operator_highPrecdence","logicalOp","constrainedVars","relationalOp","matrixElement","matrix","row" ,"F","remainingColElements","booleanExpression","ioStmt","stmtsAndFunctionDefs","stmtOrFunctionDef","A","stmt","declarationStmt","assignmentStmt_type1","assignmentStmt_type2","parameter_list","rightHandSide_type1","rightHandSide_type2" ,"arithmeticExpression" ,"otherStmts","inputParameterList","arithmeticTerm","D","factor","E","rows","G","MAIN","SQO","SQC","SEMICOLON","FUNCTION","ASSIGNOP","FUNID","END","ID","INT","REAL","STRING","MATRIX","COMMA","SIZE","IF","OP","CL","ELSE","ENDIF","PRINT","READ","PLUS","MINUS","MUL","DIV","NUM","RNUM","STR","AND","OR","LT","LE","EQ","GT","GE","NE","NOT","EPSILON"};

int main(){
	FILE* fp=fopen("grammar.txt","r");
	FILE* fp2=fopen("Reversegrammar.txt","w");
	int t; char ch;
	while(!feof(fp)){
		fscanf(fp,"%d%c",&t,&ch);
		fprintf(fp2,"%d:%s%c",t,words[t],ch);
}

}
