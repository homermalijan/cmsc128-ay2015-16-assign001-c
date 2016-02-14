//Author: Homer C. Malijan
#include<stdio.h>
#include<string.h>
#include "assign001.h"
#include "other-functions.h"

main(){
	int choice=0,numberOutput=0,input=0,position=0;;
	char words1[256],words2[256],wordOutput[256];
	char delimiter='\0';
	
	do{
		printMenu(&choice);
		wordOutput[0] = '\0';															//to make sure string is empty everytime is is used
		switch(choice){
			case 1: printf("\n\nEnter Number (<= 100000): ");							//convert number to words
					scanf("%d", &input);
					getchar();
					numToWords(input);
					break;
			case 2: printf("\n\nEnter Number in Words (lower case) : ");				//convert words to number
					fgets(words1,256,stdin);
					numberOutput = wordsToNum(words1);
					if(numberOutput != -1) printf("\nOutput: %d\n", numberOutput);		//number is too big if return is -1
					break;
			case 3: printf("\n\nEnter Number in Words (lower case) : ");				//convert to currency
					fgets(words1,256,stdin);
					printf("JPY/PHP/USD: ");
					fgets(words2,256,stdin);
					convertToCurrency(words1,words2);
					break;
			case 4: printf("\n\nEnter Number (<= 100000): ");							//add delimiter to input
					scanf("%d", &input);
					getchar();
					printf("Enter Delimiter (single character): ");
					scanf("%c", &delimiter);
					getchar();
					printf("Enter Position: ");
					scanf("%d", &position);
					getchar();
					numberDelimited(input,delimiter,position);					
					break;
			case 5: break;																//exit
			default: printf("\nInvalid input\n");										//invalid input
		}
	}while(choice!=5);																	//continuous until user exits
	
	printf("\nBye! :)\n");
}

