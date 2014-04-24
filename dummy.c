#include<stdio.h>
#include<string.h>
char* variableGenerator(char lastVar[]){
	int length=strlen(lastVar);
	
	int i=0;
	for(i=0; i<length; i++){
		if(lastVar[i]<'z'){
			lastVar[i]+=1;
			return lastVar;
			}
		/*else{
			printf("come to me");
		}*/
	}
	char newVar[256]={"a"};
	if(i==length){
		return strcat(newVar,lastVar);;
	}	
}
int main(){
	char ch='a';
	while(ch!='n'){
		char sample[20];
		scanf("%s",sample);
		printf("<%s>",variableGenerator(sample));
	}
	
}
