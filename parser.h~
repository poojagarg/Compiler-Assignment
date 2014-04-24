//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
#ifndef PARSERDEF_H
#define PARSERDEF_H
	#include"parserDef.h"
#endif
void computeNullable(grammar* g);
int isNullable(NTrule ntR, int A[]);
grammar* createGrammar();
void createFollow(grammar* g);
void createFirst(grammar* g);
void createParseTable(grammar* g, table T);
void printSyntaxError(int i);
parseTree parseInputSourceCode(char *testcaseFile, table T, grammar* g);
void printParseTree(parseTree  PT, char *outfile);
void createChildParseTreeNode(parseTreeNode* parent,parseTreeNode* child);
void printParseTable(grammar* g, table T);



