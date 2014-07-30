#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct word {
	size_t length;
	char * text;
};

struct wordlist {
	size_t count;
	struct word * list[90000];
} words;

void load() {
	srand(time(NULL));

	char temp[30];
	size_t index = 0;	

	FILE * pFileWords;
	pFileWords = fopen("wordlist", "r");
	while (fscanf(pFileWords, "%s", temp) != EOF) {

		size_t length = strlen(temp);
		words.list[index] = malloc(sizeof(struct word));
		words.list[index]->text = (char *)malloc(length*sizeof(char)+1);
		strcpy(words.list[index]->text, temp);
		words.list[index]->length = length;
		index++;
	}
	words.count = index;
}

int main(int argc, char * argv) {
	load();
	do {
		struct word * word = words.list[rand()%words.count];
		int guess;
		int left = 5;
		char wrong[30] = "";
		char found[word->length+1];
		memset(found, '\0', word->length+1);
		memset(found, '_', word->length);

		printf("solved %s | left %i | wrong '%s'  ", found, left, wrong);
		do {
			guess = getchar();
			if (guess == '\n') {
				printf("solved %s | left %i | wrong '%s'  ", found, left, wrong);
				continue;
			}
			else if (guess == EOF) {
				printf("\n");
				return 0;
			}
			else if (guess < 97 || guess > 122) {
				continue;
			}
			else {
				int i;
				for (i = 0; i < strlen(found); i++) {
					if (word->text[i] == guess) {
						found[i] = guess;
					}
				}
				if (strchr(found, guess) == NULL && strchr(wrong, guess) == NULL) {
					strncat(wrong, (char *)&guess, 30);
					left--;
				}
			}
		} while (strchr(found, '_') != NULL && left > 0);
		printf("solved %s | left %i | wrong '%s'\n", word->text, left, wrong);
		if (left > 0) {
			printf("VICTORY!\n\n");
		} else {
			printf("DEFEAT!\n\n");
		}
		while (getchar() != '\n') { /* do nothing */ };
	} while(1);
	return 0;
}
