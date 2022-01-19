/*
 ============================================================================
 Name        : roman.c
 Author      : Ken
 Version     :
 Copyright   : Your copyright notice
 Description : CLI conversion tool to convert Roman Numerals to corresponding Integer value (vice-versa)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int peek(int* stack, int* top){
    return stack[*top];
}

void push(int* stack, int* top, int elem){
    *top += 1;
    stack[*top] = elem;
    return;
}

int pop(int* stack, int* top){
    int elem = stack[*top];
    *top -= 1;
    return elem;
}

int romanToInt(char * s){
    int final = 0;
    int numeral;
    int prevNumeral;
    int size = 15;
    int top = -1;
    int stack[size];

    for (int i=0; s[i] != '\0'; i++){
        char temp = s[i];
        switch (temp){
            case 'I':
                numeral = 1;
                break;
            case 'V':
                numeral = 5;
                break;
            case 'X':
                numeral = 10;
                break;
            case 'L':
                numeral = 50;
                break;
            case 'C':
                numeral = 100;
                break;
            case 'D':
                numeral = 500;
                break;
            case 'M':
                numeral = 1000;
                break;
            default:
                return -1;
        }
        if (top > -1){
          if (numeral > peek(&stack, &top)){
              prevNumeral = pop(&stack, &top);
              final += (numeral - prevNumeral);
          }else{
              push(&stack, &top, numeral);
              peek(&stack, &top);
          }
        }else{
            push(&stack, &top, numeral);
            peek(&stack, &top);
        }
    }
    while(top > -1){
        final += pop(&stack, &top);
    }
    return final;
}



char getChar(int num){

    switch (num){
            case 1:
                return 'I';
            case 5:
                return 'V';
            case 10:
                return 'X';
            case 50:
                return 'L';
            case 100:
                return 'C';
            case 500:
                return 'D';
            case 1000:
                return 'M';
            default:
                printf("%d\n", num);
                return 'z';
        }
}

int power(int base, int exp){
    int result = 1;
    while (exp > 0){
        result = result * base;
        exp--;
    }
    return result;
}

char * intToRoman(int num){
    char ten;
    char five;
    char one;
    char *result = malloc( sizeof(char) * 20);
    int index = 0;
    int magnitude = 0;
    int tmp = num;
    while (tmp > 1){
        tmp = tmp / 10;
        if (tmp > 0){
            magnitude += 1;
        }
    }
    tmp = num;
    int sigDigit;
    for (; magnitude >= 0; magnitude--){
        if (tmp > 0){
            while (tmp/power(10,magnitude) == 0){
                magnitude--;
            }
            sigDigit = tmp/power(10,magnitude);
            tmp = tmp - (sigDigit*power(10,magnitude));
            //0 -> 10
            if (sigDigit == 0){
                result[index] = getChar(sigDigit*power(10,magnitude));
                index++;
            }
            //9
            else if (sigDigit == 9){
                one = getChar(1*power(10,magnitude));
                result[index] = one;
                index++;
                ten = getChar(10*power(10,magnitude));
                result[index] = ten;
                index++;
            }
            //6-8
            else if (sigDigit > 5 && sigDigit < 9){
                five = getChar(5*power(10,magnitude));
                result[index] = five;
                index++;

                sigDigit = sigDigit - 5;
                for(; sigDigit > 0; sigDigit--){
                    one = getChar(1*power(10,magnitude));
                    result[index] = one;
                    index++;
                }
            }
            //5
            else if (sigDigit == 5){
                result[index] = getChar(sigDigit*power(10,magnitude));
                index++;
            }
            //4
            else if (sigDigit == 4){
                one = getChar(1*power(10,magnitude));
                result[index] = one;
                index++;
                five = getChar(5*power(10,magnitude));
                result[index] = five;
                index++;
            }
            //1-3
            else if (sigDigit > 0 && sigDigit < 4){
                for(; sigDigit > 0; sigDigit--){
                    one = getChar(1*power(10,magnitude));
                    result[index] = one;
                    index++;
                }
            }
        }else{
            break;
        }
    }
    result[index] = '\0';
 return result;
}

int main(int argc,char* argv[])
{
	int rtiResult;
	int romanToInteger = 0;

	int opt;

	// put ':' in the starting of the
	// string so that program can
	//distinguish between '?' and ':'
	char* value;
	int itor = 0;
	while((opt = getopt(argc, argv, "v:i")) != -1)
	{
		switch(opt)
		{
			case 'i':
				itor = 1;
				break;
			case 'v':
				value = optarg;
				break;
			case ':':
				printf("option needs a value\n");
				break;
			case '?':
				printf("unknown option: %c\n", optopt);
				break;
		}
	}
	if (!itor){
		printf("Roman Numeral To Integer: [%s] -> %d\n",value, romanToInt(value));
	}else{
		int valueInt = atoi( value );
		printf("Roman Numeral To Integer: [%d] -> %s\n",valueInt, intToRoman(valueInt));
	}
    return 0;
}
