#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define N 30

int main()
{
  char input[N];  
  char *hexarr;
  int i,digit,len,validNum;
  double num;
  printf("Metatropeas apo dekaexadiko se dekadiko systima!\n\n");
  do {
    printf("Dwste enan dekaexadikos arithmo (mexri %d psifia):",N);
	/* �������������� ��� fgets() ����� �� ��������� ��� � ������� ����� ������������� ���������� ��� �� ������� ��� ������ input ��� �� ������� �������� ��� ���������  */
    fgets(input, sizeof input, stdin);

	/* � fgets() ���� ��� ������ �������� �� \n ��� ����� ��� string ��� �������� */
    input[strlen(input)-1]='\0';
    fflush(stdin);  // ������� ���� ���������� ����������

    len = strlen(input);
    validNum = 1;
    if (len == 0) {
       printf("Den dwsate kapoia psifia.\n\n");
       int validNum = 0;
    }
    else 
      for (i=0;i<len;i++)
         if (input[i]<'0' || input[i]>'F' || (input[i]>'9' && input[i]<'A'))
            {
                printf("To %d psifio den einai egkyro!\n\n",i);
                validNum = 0;
                break;
            }   
  } while (!validNum);

  hexarr = (char *) malloc(len * sizeof(char));

  for (i=0;i<len;i++)
    hexarr[i] = input[len-i];
    
  num = 0.0;

  for (i=0;i<len;i++) {
    if (hexarr[i]<'9')
       digit =  hexarr[i] - '0';
    else   
       digit =  10 + hexarr[i] - 'A';
    num += digit*pow(16,i);   
  }    
  printf("O Dekaexadikos '%s' antistoixei ston dekadiko '%.0f'.\n\n",input,num);
}
