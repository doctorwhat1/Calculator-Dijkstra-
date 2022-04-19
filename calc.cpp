#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 150

// Input: a file with a string consisting of an equasion, for instance: "5 - (2 / 2)"
// Output: correct mathematical result with right order of operations, for instance " 4 "

struct Stack {
	int stk[SIZE];
	int cursize;
};
typedef struct Stack STACK;

struct StackCHAR {
	char stk[SIZE];
	int cursize;
};
typedef struct StackCHAR STACKCHAR;

STACK s1;

STACK numbers;

STACKCHAR operands;


int temp;

char str[SIZE] = { 0 };
char output[SIZE] = { 0 };




void DisplayStack(STACKCHAR stack)
{
	printf("\nStack elements are:\n");
	for (int i = 0; i < stack.cursize; ++i)
	{
		printf("%c ", stack.stk[i]);
	}
	printf("\nNumber of elements is %d \n", stack.cursize);
}

void Push(STACK* stack, int element, int cursize)
{
	stack->stk[cursize] = element;
	stack->cursize = stack->cursize + 1;

}

void PushCH(STACKCHAR* stack, char element, int cursize)
{
	stack->stk[cursize] = element;
	stack->cursize = stack->cursize + 1;
}

int ReturnPriority(char symbol)
{
	switch (symbol)
	{
	case'+':
		return(1);

	case '-':
		return(1);

	case '*':
		return(2);

	case '/':
		return(2);
	case '(':
		return(0);


	}
}

int Pop(STACK* stack, int cursize)
{
	int temp;
	if (stack->cursize == 0)
	{
		printf("Stack Underflow!!!");
		return(-10);
	}
	else
	{
		temp = stack->stk[cursize - 1];
		stack->stk[cursize] = NULL;
		stack->cursize = stack->cursize - 1;
		return(temp);
	}
}

int PopCH(STACKCHAR* stack, int cursize)
{
	char temp;
	if (stack->cursize == 0)
	{
		printf("Stack Underflow!!!");
		return('X');
	}
	else
	{
		temp = stack->stk[cursize - 1];
		stack->stk[cursize] = NULL;
		stack->cursize = stack->cursize - 1;
		return(temp);
	}
}


int main(int argc, char* argv[])
{
	// Открываем файлы
	FILE* fr = fopen("input.txt", "r");
	if (!fr)
	{
		printf("Error opening file for reading\n");
		return -2;
	}

	FILE* fw = fopen("output.txt", "w");
	if (!fw)
	{
		printf("Error opening file for reading\n");
		return -3;
	}
	int i, len;

	//	s1.stk[0] = 0;
	//	s1.stk[1] = 1;
	//	s1.stk[2] = 2;
	//	s1.cursize = 3;
	////	s1.top = s1.stk[0];
	//	DisplayStack(s1);
	//
	//	Push(&s1, 14,s1.cursize);
	//
	//	DisplayStack(s1);
	//
	//	Push(&s1, 11, s1.cursize);
	//	DisplayStack(s1);
	//
	//	printf("Popped element == %d  \n",Pop(&s1, s1.cursize));
	//
	//	DisplayStack(s1);
	//	//printf("%d", s1.top);

		// debug


//	fgets(str, SIZE, stdin);

	fgets(str, SIZE, fr);
	
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	str[i] = '\n';

	i = 0;


	printf("Expression:\n");
	printf(str);
	//(10+93)*(22-0)

	len = strlen(str);
	//	str[len] = '\0';
	str[len - 1] = ' ';




	int output_l = 0;
	//printf(str);
////	printf("%c",str[len-2]);
//	temp = atoi(str);
//	printf("%d   !!!", temp);

	operands.cursize = 0;
	i = 0;
	int temp1;
	char tempstr[SIZE] = { 0 };

	while (len != 0)
	{
		switch (str[0])
		{
		case' ':
			//output_l--;
			break;
		case'+':
		case'-':
		case'/':
		case'*':
			//printf("It was a symbol ");
			if ((operands.cursize != 0) && (ReturnPriority(operands.stk[operands.cursize - 1]) >= ReturnPriority(str[0])))
				//&& (ReturnPriority(operands.stk[operands.cursize]) >= ReturnPriority(str[0]))
			{
				//printf("polozhili v stek");
				output[output_l] = PopCH(&operands, operands.cursize);
				output_l++;
				PushCH(&operands, str[0], operands.cursize);
				output[output_l] = ' ';
				output_l++;

			}
			else
			{
				//	printf("lol");
				PushCH(&operands, str[0], operands.cursize);
			}
			break;
		case'(':
			//printf("It was (");
			PushCH(&operands, str[0], operands.cursize);
			break;
		case ')':
			//printf("It was )");
			while (operands.stk[operands.cursize - 1] != '(')
			{
				// POP элемента из операндов в оутпут
				output[output_l] = PopCH(&operands, operands.cursize);
				output_l++;


				output[output_l] = ' ';
				output_l++;

			}
			PopCH(&operands, operands.cursize);
			break;
		default:
			//	printf("It was a number ");
				//temp1 = atoi(str);
				////tempstr = itoa(temp1,,10);
				//_itoa(temp1, tempstr, 10);
				//strcat(output, tempstr);
				//output_l = strlen(output);

				//take3
				//while (output[1] >= '0' && output[1] <= '9')
				//{
				//	output[output_l] = str[0];
				//	output_l++;

				//	for (i = 0; i < len; i++)
				//	{
				//		str[i] = str[i + 1];
				//	}
				//	str[i] = 0;
				//	len--;
				//}

				//prev
			output[output_l] = str[0];
			output_l++;

			if (str[1] < '0' || str[1]>'9')
			{
				output[output_l] = ' ';
				output_l++;
			}
			break;

		}

		for (i = 0; i < len; i++)
		{
			str[i] = str[i + 1];
		}
		str[i] = 0;
		len--;
	}

	while (operands.cursize != 0)
	{
		output[output_l] = PopCH(&operands, operands.cursize);
		output_l++;
		output[output_l] = ' ';
		output_l++;
	}


//	printf("Reverse Polish Notation:\n");
//	printf(output);



	//case' ':
//	while (output_l>0 && output[0] == ' ')
//	{
//		for (i = 0; i < output_l; i++)
//		{
//			output[i] = output[i + 1];
//		}
//		output[i] = 0;
//		output_l--;
//	}
//	break;

	int tempI1;
	int tempI2;
	// PODSCHET
	int sum = 0;
	//	printf("=vv %d vv= ",output_l);

	while (output_l > 1)
	{
		sum = 0;
		if (output[0] == ' ')
		{
			for (i = 0; i < output_l; i++)
			{
				output[i] = output[i + 1];
			}
			output[i] = 0;
			output_l--;
		}

		switch (output[0])
		{

		case'/':

			tempI1 = Pop(&numbers, numbers.cursize);
			tempI2 = Pop(&numbers, numbers.cursize);

			sum = tempI2 / tempI1;
			Push(&numbers, sum, numbers.cursize);
			for (i = 0; i < output_l; i++)
			{
				output[i] = output[i + 1];
			}
			output[i] = 0;
			output_l--;
			break;


		case'*':
			sum = Pop(&numbers, numbers.cursize) * Pop(&numbers, numbers.cursize);
			Push(&numbers, sum, numbers.cursize);
			for (i = 0; i < output_l; i++)
			{
				output[i] = output[i + 1];
			}
			output[i] = 0;
			output_l--;
			break;


		case'+':
			sum = Pop(&numbers, numbers.cursize) + Pop(&numbers, numbers.cursize);
			Push(&numbers, sum, numbers.cursize);
			for (i = 0; i < output_l; i++)
			{
				output[i] = output[i + 1];
			}
			output[i] = 0;
			output_l--;
			break;
		case'-':
			sum = 0 - Pop(&numbers, numbers.cursize) + Pop(&numbers, numbers.cursize);
			Push(&numbers, sum, numbers.cursize);
			for (i = 0; i < output_l; i++)
			{
				output[i] = output[i + 1];
			}
			output[i] = 0;
			output_l--;
			break;
		default:
			numbers.stk[numbers.cursize] = atoi(output);
			numbers.cursize++;
			//printf("/n/n,%d", atoi(output));

			while (output[0] != ' ')
			{
				for (i = 0; i < output_l; i++)
				{
					output[i] = output[i + 1];
				}
				output[i] = 0;
				output_l--;
			}

			break;

		}

		//while (!(output[0] != ' ' || output[1] == ' ') )
		//{
		//	for (i = 0; i < output_l; i++)
		//	{
		//		output[i] = output[i + 1];
		//	}
		//	output[i] = 0;
		//	output_l--;
			//printf("AND THE CYCLE NEVER ENDS");
		//}
		//printf("AGAIN");
	}

	//printf("/n  ATOI =====%d",atoi(output));
	sum = Pop(&numbers, numbers.cursize);

	//	printf(" SUM IS EQUAL =%d", sum);
	printf("\n");
	printf("Result:\n%d", sum);


	fclose(fr);
	fclose(fw);
	return 0;


}