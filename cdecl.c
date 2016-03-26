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
#define pop stack[top--];
#define push(s) stack[++top]=s

enum type_tag classify_string(){
	enum type_tag ret = IDENTIFIER;
	printf("About to figure out the tag for: %s\n", this.string);
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
	printf("found a type of  (%d)",ret);
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

	printf("The token is: (%s)\n", this.string);
	printf("The type is: (%d)\n", this.type);

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


int main(int argc, char *argv[])
{
	read_to_first_identifier();
	return 0;
}
