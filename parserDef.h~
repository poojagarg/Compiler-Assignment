//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
#ifndef LEXERDEF_H
	#define LEXERDEF_H
	#include"lexerDef.h"
#endif
#define RuleSize 30
#define FollowSize 10 //max # of elements in follow of a Non-Terminal
#define FirstSize 10
#define NumberOfTerminal 40
#define NumberOfNonTerminal 46
#define EPSILON 84
#define NullableNTSize 20
#define baseTerminal 46 //46th no. is a terminal
#define ParseTreeSize 200
typedef int table[NumberOfNonTerminal][NumberOfTerminal]; //number of non terminals * (terminals+1)
typedef struct Rule{
	int parts[RuleSize];
	struct Rule* next;
	}Rule;
typedef int follow[NumberOfTerminal];
typedef int first[NumberOfTerminal];
typedef struct NTrule{ int count; Rule* head;//make a stack
		       first FirstSet; follow FollowSet; int firstIndex; int followIndex;}NTrule;
typedef struct grammar{
	int count; //no. of NT
	NTrule* ntRuleNext;	//malloc for no. of non-terminals
	int nullable[NumberOfNonTerminal]; 
	//int nullableIndex;//base index	to start adding in nullable[]	
		}grammar;
typedef union parseNodeUnion{token name; int NonTerminalSymbol;}parseNodeUnion;
typedef struct parseNodeValue{
	parseNodeUnion p; 
	int isLeafNode; 
	//is a non-terminal for every node, extract actual name from words array 
	int parentNodeSymbol;}parseNodeValue;
typedef struct parseTreeNode{parseNodeValue value; struct parseTreeNode* nextSibling; struct parseTreeNode* children;}parseTreeNode;
typedef parseTreeNode* parseTree;
