all: stage1exe
stage1exe: Driver.o lexer.o parser.o linkedlistStack.o AST.o Semantics.o SymbolStack.o SymbolTable.o codeGen.o
	gcc Driver.o lexer.o parser.o linkedlistStack.o AST.o Semantics.o SymbolStack.o SymbolTable.o codeGen.o -o stage1exe
Driver.o: Driver.c
	gcc -c -w Driver.c
lexer.o: lexer.c
	gcc -c -w lexer.c
parser.o: parser.c
	gcc -c -w parser.c
linkedlistStack.o: linkedlistStack.c
	gcc -c -w linkedlistStack.c
AST.o: AST.c
	gcc -c -w AST.c
Semantics.o: Semantics.c
	gcc -c -w Semantics.c
SymbolTable.o: SymbolTable.c
	gcc -c -w SymbolTable.c
SymbolStack.o: SymbolStack.c
	gcc -c -w SymbolStack.c
codeGen.o: codeGen.c
	gcc -c -w codeGen.c
clean:
	rm -rf *o stage1exe
