#ifndef LEXERDEF_H
#define LEXERDEF_H
	#include"lexerDef.h"
#endif
typedef struct ASTnode{
	int label;
	token t;	
	struct ASTnode** array;
	int arraySize;
	}ASTnode;
