#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H 
	#include"SymbolTableDef.h"
#endif
SymbolTable* CreateSymbolTable(int size);
int InsertSymbolTable(SymbolTable* h, char* lexeme);
int InsertSymbolTableFun(SymbolTable* h, ASTnode* ASTroot);
int SearchHashTable(SymbolTable* h, char* lexeme);
int HashKey(char* lexeme, int size);
void displayST(SymbolTable* h);
SymbolTableEntryNode* SearchHashTableNode(SymbolTable* h, char* lexeme);
SymbolTableEntryNode* addEntry(SymbolTable* h,char* lexeme, int type);
