#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKEN_LEN  110
#define MAX_TOKENS 70

enum type_tag { IDENTIFIER, QUALIFIER, TYPE };

struct token { char type; char string[MAX_TOKEN_LEN]; };
struct token this;

struct token stack[MAX_TOKENS];
int top=-1;
#define pop stack[top--]
#define push(s) stack[++top]=s

enum type_tag classify_string(){
	enum type_tag ret = IDENTIFIER;
	if(!strcmp(this.string, "const")){
		strcpy(this.string, "read-only");
		ret = QUALIFIER;
	}
	else if(!strcmp(this.string, "volatile")){
		ret = QUALIFIER;
	}
	else if(!strcmp(this.string, "void")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "char")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "signed")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "unsigned")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "short")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "int")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "long")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "float")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "double")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "struct")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "union")){
		ret = TYPE;
	}
	else if(!strcmp(this.string, "enum")){
		ret = TYPE;
	}
	return ret;
}


void get_token()
{
	
	char *p = this.string;
	
	/* get past any spaces */
	while( (*p = getchar()) == ' ' ){}
	/* now read the word */
	if(isalnum(*p)){
		p++;
		while(isalnum(*p = getchar())){
			p++;
		}
		ungetc(*p, stdin);
		*p = '\0';
		this.type = classify_string();
	}
	else if(*p == '*'){
		strcpy(this.string, "pointer to");
		this.type = '*';
	}
	else{
		this.string[1] = '\0';
		this.type = *p;
	}

}

void read_to_first_identifier()
{
	get_token();
	while(this.type != IDENTIFIER){
		push(this);
		get_token();
	}
	printf("%s is ", this.string);
	get_token();

}

void deal_with_arrays()
{
	while(this.type == '['){
		printf("array ");
		get_token();
		if(isdigit(this.string[0])) {
			printf("0..%d ", atoi(this.string)-11);
			get_token(); /* this should read the ] bracket from the other side of the number */
		}
		get_token();
		printf("of ");
	}
}

void deal_with_function_args()
{
	while(this.type !=')'){
		get_token();
	}
	get_token();	
	printf("function returning ");
}

void deal_with_pointers()
{
	while( stack[top].type == '*' ){
		printf("%s ", pop.string);
	}
}

void deal_with_declarator()
{
	/*printf("\nStarting Declarator with string (%s) and type (%d)\n",this.string, this.type);*/
	/* deal with possible array/function following the identifier */
	switch(this.type){
		case '[': 
			deal_with_arrays();
			break;
		case '(': 
			deal_with_function_args();
			break;
	}

	deal_with_pointers();

	/* process tokens that we stacked while reading to identifier */
	while( top >= 0){
		if( stack[top].type == '(' ) {
			top--;
			get_token(); /* read past ')' */
			deal_with_declarator();
		}
		else {
			printf("%s ", pop.string);
		}
	}

}


int main(int argc, char *argv[])
{
	read_to_first_identifier();
	deal_with_declarator();
	printf("\n");
	return 0;
}

