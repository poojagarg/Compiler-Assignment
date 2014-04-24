typedef struct SymbolStackNode{SymbolTable* value; struct SymbolStackNode* next;}SymbolStackNode;
typedef struct SymbolStack{int count; SymbolStackNode* top;}SymbolStack;

