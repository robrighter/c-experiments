#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PHRASE_LENGTH 7
#define MIN_PHRASE_LENGTH 2
#define MAX_WORD_LENGTH 20

typedef struct Word Word;

struct Word { 
	char *word;
	Word *next;
	Word *previous;
};

struct Word* train_head = 0;
struct Word* train_tail = 0;
int train_length = 0;

void add_word_to_train(char *new_word_string)
{
	struct Word* new_word;		
	if(train_length < MAX_PHRASE_LENGTH){
		/* Need to make a new word */
		new_word = malloc( sizeof (struct Word) );
		if(train_length == 0){
			train_tail = new_word;	
		}
		train_length++;
	}
	else {
		/* Need to recycle the last word in the train */
		new_word = train_tail;
		train_tail = train_tail->next;
		train_tail->previous = 0;
	}
	if(train_head != 0){
		train_head->next = new_word;
	}
	new_word->previous = train_head;
	new_word->next = 0;
	train_head = new_word;
	new_word->word = new_word_string;
}

void print_word_train()
{
	struct Word * next_word = train_head;
	printf("Head => ");
	while(next_word != 0){
		printf("%s => ", next_word->word);
		next_word = next_word->previous;
	}
	printf("tail\n");
	return;
}

int main(int argc, char *argv[])
{
	add_word_to_train("one");
	print_word_train();
	add_word_to_train("two");
	print_word_train();
	add_word_to_train("three");
	print_word_train();
	add_word_to_train("four");
	print_word_train();
	add_word_to_train("five");
	print_word_train();
	add_word_to_train("six");
	print_word_train();
	add_word_to_train("seven");
	print_word_train();
	add_word_to_train("eight");
	print_word_train();
	add_word_to_train("nine");
	print_word_train();
	add_word_to_train("ten");
	print_word_train();
	add_word_to_train("eleven");
	print_word_train();
	return 0;
}


