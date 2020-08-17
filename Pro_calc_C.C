#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 512

double memory;

double stack_operend[128];

char stack_op[128];

int operend_top=-1;

int op_top=-1;

void help()
{
 printf("EXIT        Exits the program.\n\n");
 printf("HELP        Displays information about this program.\n\n");
 printf("RESET       Erases stored memory and return calculator to its initial 'Start-up'mode.\n\n");
 printf("OPERATORS   DESCRIPTION      SYNTAX\n");
 printf("+           addition         [a+b|+a]\n");
 printf("-           subtraction      [a_b|-a]\n");
 printf("*           multiplication   [a*b|*a]\n");
 printf("/           division         [a/b|/a]\n");
 printf("^           sqr(a)           a^\n");
 printf("#           sqrt(a)          a#\n\n");
 printf("Example:   a^ +b#/c <spacing optional>\n");
}
int op_priority(char op){

	switch(op){

		case '+':

			return 1;

		case '-':

			return 1;

		case '*':

			return 2;

		case '/':

			return 2;

		case '^':

			return 3;

		case '#':

			return 3;

	}

}

double read_operend(char *Input, int *i, int n)

{

		int j=*i;

		char buf[128];

		while(j<n){

				if((Input[j] == '+') || (Input[j] == '-') || (Input[j] == '*') ||(Input[j] == '/') || (Input[j] == '^') || (Input[j] == '#') || (Input[j] == ' '))

						break;

				buf[j-*i] = Input[j];

				j++;

		}

		buf[j-*i]= '0';

		*i=j;

		if(!strcmp(buf, "MEMORY") || !(strcmp(buf, "memory")))

				return memory;

		return atof(buf);

}

int is_operend(char c){

		if(((c >= 48) && (c <= 57)) || (c == 'm') || (c == 'M') || (c == '.'))

				return 1;

		return 0;

}

int is_op(char c){

		if((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '#'))

				return 1;

		return 0;

}

double calop(char op){

		double a,b;

		a = stack_operend[operend_top--];

		if(operend_top == -1)

				b=0;

		else

				b = stack_operend[operend_top--];

		switch(op){

		case '+':

						return (b+a);

		case '-':

						return (b-a);

		case '*':

			return (b*a)/10;

		case '/':

			return (b/a)*10;

		case '^':

						if(b != 0)

								stack_operend[++operend_top] = b;

			return pow(a/10, 2)*10;

		case '#':

						if(b != 0)

				stack_operend[++operend_top] = b;

			return sqrt(a/10)*10;

	}

}

void calc(char done){

		double val=0;

		if(op_top == -1)

				return;

		if(done == 'y'){

				while(op_top != -1){

						val = calop(stack_op[op_top--]);

						stack_operend[++operend_top] = val;

				}

		}else{

				if(op_top < 1)

						return;

				if(op_priority(stack_op[op_top]) > op_priority(stack_op[op_top-1])){

						val = calop(stack_op[op_top--]);

						stack_operend[++operend_top] = val;

				}

		}

}

int main(int argc, char *argv[]){

		char Input[512], buf[512];

		char is_answer_exist='n';

		double answer=0;

		char is_memory_exist='n';

		int i, j, n;

		char last_token;
		 
		printf("\nType \"HELP\" or enter a mathematical expression\n\n");

		while(1){

				printf("Calc:\\> ");

				fgets(Input, MAX, stdin);

				Input[strlen(Input)-1] = '\0';

				if(!strcmp(Input, "")){

						answer = 0;

						printf("\nType \"HELP\" or enter a mathematical expression\n\n");

						continue;

				}

				if(!strcmp(Input, "help") || !strcmp(Input, "HELP")){

						help();

						continue;

				}

				if(!strcmp(Input, "store") || !strcmp(Input, "STORE")){

						if(is_answer_exist == 'y'){

								memory = answer;

								is_memory_exist='y';

								printf("ANSWER STORED IN MEMORY\n");

						} else{

								printf("NO ANSWER TO STORE IN MEMORY\n");

						}

						continue;

				}

				if(!strcmp(Input, "reset") || !strcmp(Input, "RESET")){

						system("clear");

						printf("\nType \"HELP\" or enter a mathematical expression\n\n");

						is_memory_exist='n';

						continue;

				}

				if(!strcmp(Input, "exit") || !strcmp(Input, "EXIT")){

						printf("\n\n");

						return 0;

				}

				i=0;

				n = strlen(Input);

				while(1){

						if(is_operend(Input[i])){

								stack_operend[++operend_top] = read_operend(Input, &i, n);

								last_token = 'e';

						}else if(is_op(Input[i])){

								if(operend_top == -1)

										stack_operend[++operend_top] = answer;

								stack_op[++op_top] = Input[i];

								i++;

								last_token = 'o';

						}

						if(Input[i] == ' '){

								if(last_token == 'o'){

										char op = stack_op[op_top--];

										calc('y');

										stack_op[++op_top] = op;

								}else{

										calc('y');

								}

								i++;

								continue;

						}

						if(i == n){

								calc('y');

								answer = stack_operend[operend_top--];

								is_answer_exist = 'y';

								break;

						}

						calc('n');

				}

				printf("Answer:\\> %.6f\n\n", answer/10);

		}

}
