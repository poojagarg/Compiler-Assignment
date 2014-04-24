#ifndef _POSTFIXSTACKDEF_H
	#include"postfixStackDef.h"
#endif
postfixStack* createpostfixStack();
void pushpostfixStack(int value,postfixStack* s);
int poppostfixStack(postfixStack* s);
int isEmptypostfixStack(postfixStack* s);
void deletepostfixStack(postfixStack* s);
