#ifndef ASTDEF_H
#define ASTDEF_H
	#include"ASTDef.h"
#endif
#ifndef LEXER_H
#define LEXER_H
	#include"lexer.h"
#endif
#ifndef PARSER_H
#define PARSER_H
	#include"parser.h"
#endif
ASTnode* FindNPTR(parseTreeNode* p);
ASTnode* makeNode1(int label,ASTnode* p);//1 pointer
ASTnode* makeLeaf(token label);
ASTnode* FindNPTR(parseTreeNode* PT);
ASTnode* makeNode3(int label,ASTnode *p1,ASTnode *p2,ASTnode *p3);
ASTnode* makeNode4(int label,ASTnode *p1,ASTnode *p2,ASTnode *p3,ASTnode *p4);
void displayAST(ASTnode* root);
