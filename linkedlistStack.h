//BATCH 12
//TEAM MEMBERS-NIKITA BHALLA-2011A7PS122P
//POOJA GARG-2011A7PS056P
#ifndef _LINKEDLISTSTACKDEF_H
	#define _LINKEDLISTSTACKDEF_H
	#include"linkedlistStackDef.h"
#endif
linkedlistStack* create();
void push(parseTreeNode* value,linkedlistStack* s);
parseTreeNode* pop(linkedlistStack* s);
parseTreeNode* top(linkedlistStack* s);
void deleteStack(linkedlistStack* s);
void displayStack(linkedlistStack* st);

