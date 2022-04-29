#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZ 100
#define STACK_SIZ 32

int stack[STACK_SIZ];
int top = 0;

void push(int n) {
	stack[top] = n;
	top++;
}

int pop(void) {
    top--;
	int value = stack[top];
	return value;
}

int8_t isNumber(char* str) {
	size_t size = strlen(str);
	int i = 0;
	if (str[0] == '-' && size != 1) i = 1;
	for (; i != size; i++) if (str[i] < '0' || str[i] > '9') return 0;
	return 1;
}

void main(void) {
	char* input = malloc(BUF_SIZ * sizeof(char));
	fgets(input, BUF_SIZ, stdin);
	for (int i = 0; i != strlen(input); i++) if (*(input + i) == '\n') input[i] = ' ';

	char* operation = malloc(BUF_SIZ * sizeof(char));

	char* token = strtok(input, " ");
	while (token != NULL) {
		if(isNumber(token)) {
    		push(atoi(token));
		}
		else {
    		if (top < 2) {
				printf("Cannot execute operation [%s], as there is not enough elements on the stack\n", token);
				exit(1);
    		}
			int second = pop();
			int first = pop();
			if      (!strcmp(token, "+")) push(first + second);
			else if (!strcmp(token, "-")) {
    			int value = first - second;
    			printf("%d substraction result\n");
    			push(value);
			}
			else if (!strcmp(token, "*")) push(first * second);
			else if (!strcmp(token, "/")) push(first / second);
			else if (!strcmp(token, "%")) push(first % second);
			else printf("[ERROR]: Unrecognized token: %s\n", token);
		}
		token = strtok(NULL, " ");
	}
	printf("Stack has %d elements in it\n", top);
	printf("Stack state ::\n");
	while (top) {
		printf("%d ", pop());
	}
	printf("\n");
}
