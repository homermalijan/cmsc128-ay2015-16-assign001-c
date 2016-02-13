#include<stdio.h>
#include<string.h>

void printMenu(int *);
void numToWords(int);
void convertToWords(int, int);
void wordsToNum(char*);
int convertToNumber(char[][10],int,int);
void numberDelimited(int,char,int);
void toStringThisNumber(int,char[]);
int requestPrint(char[],int);

main(){
	int choice=0;
	int input=0;
	char delimiter='\0';
	int position=0;
	char words1[256],words2[256];
	do{
		printMenu(&choice);
		switch(choice){
			case 1: printf("\n\nEnter Number (<= 100000): ");
					scanf("%d", &input);
					getchar();
					numToWords(input);
					break;
			case 2: printf("\n\nEnter Number in Words (lower case) : ");
					fgets(words1,256,stdin);
					wordsToNum(words1);
					break;
			case 3: break;
			case 4: printf("\n\nEnter Number (<= 100000): ");
					scanf("%d", &input);
					getchar();
					if(input >1000000){
						printf("Input to big!");
						break;
					}
					printf("Enter Delimiter (single character): ");
					scanf("%c", &delimiter);
					getchar();
					printf("Enter Position: ");
					scanf("%d", &position);
					getchar();
					numberDelimited(input,delimiter,position);					
					break;
			case 5: //exit
					break;
			default: printf("\nInvalid input\n");
		}

	}while(choice!=5);
}

//========================================================================================================================//
void printMenu(int *choice){
	printf("\n\n\tI===============================I\n");
	printf("\tI [1] Numbers to Words          I\n");
	printf("\tI [2] Words to Numbers          I\n");
	printf("\tI [3] Number to Words           I\n");
	printf("\tI [4] Delimit                   I\n");
	printf("\tI [5] Exit                      I\n");
	printf("\tI===============================I\n");
	printf("   Choice: ");
	scanf("%d", choice);	
	getchar();
}

//========================================================================================================================//

void numToWords(int input){
	int i = 0;
	if(input>1000000){									//number is too big
		printf("\nNumber too big!\n");
		return;
	}
	if(input == 0) printf("\n Zero");					//for zero input
	for(i = 1000000 ; i > 0 ; i = i/1000){				//divides the numbers into 3s
		switch(i){
			case 1000000: 	if(((input - input % i)/i) > 0) convertToWords((input - input % i)/i,1);	//million
							break;	
			case 1000:		if(((input - input % i)/i) > 0) convertToWords((input - input % i)/i,2);	//thousands
							break;
			case 1:			if(((input - input % i)/i) > 0) convertToWords((input - input % i)/i,3);	//hundreds
							break;
		}
		input = input%i;								//update current number
	}
}

//========================================================================================================================//

void convertToWords(int x,int y){
	char primary[9][6] = {"One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
	char secondary[9][8] = {"Ten","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
	char tens[10][9] = {"Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};

	if(x/100 != 0) printf(" %s hundred", primary[(x/100)-1]);			//hundreds place
	x = x % 100;														//print only if not zero

	if(x/10 != 0){														//tens place print only if not zero
		if(x/10 != 1){													//checks for 11-19 (#pabebe case)
			printf(" %s", secondary[(x/10)-1]);							//prints tens digit
			x = x % 10;
			if(x!=0) printf(" %s", primary[x-1]);						//prints one digit
		}else printf(" %s", tens[(x%10)]);								//if tens is zero print only ones digit
	}else printf(" %s", primary[(x%10)-1]);								//print 11-19
	
	switch(y){															//print extension
		case 1: printf(" Million");
				break;
		case 2: printf(" Thousand");
				break;
	}
	return;
}

//========================================================================================================================//

void wordsToNum(char input[]){
	char choppedInput[10][10];
	char forConverting[10][10];
	char tempStorage[10];
	int iterator=0,i;
	int wordCount=0;
	int checker = 0;
	int accumulator=0;
	for(i = 0 ; i < strlen(input)+1 ; i++){								//chops the whole input into
		if(input[i] == ' ' || input[i] == '\0'){						//separate words and stored into a 2d array
			if(input[i] == ' ') tempStorage[iterator] = '\0';
			else tempStorage[iterator-1] = '\0';
			strcpy(choppedInput[wordCount],tempStorage);
			wordCount++;
			iterator=0;
			continue;
		}
		tempStorage[iterator] = input[i];
		iterator++;
	}
	iterator = 0;														//recycle variable

	for(i = 0 ; i < wordCount; i++){
		if(strcmp(choppedInput[i],"million")==0){
			accumulator += convertToNumber(forConverting, iterator,1);
			iterator = 0;
		}else if(strcmp(choppedInput[i],"thousand")==0){
			accumulator += convertToNumber(forConverting, iterator,2);
			iterator = 0;
		}else{
			strcpy(forConverting[iterator],choppedInput[i]);
			iterator++;
			if(i == (wordCount-1)){
			printf("pasok");
			accumulator += convertToNumber(forConverting, iterator,3);
			}
		}
	}
	
	printf("%d",accumulator);

	return;
}

//========================================================================================================================//

int convertToNumber(char toConvert[][10],int wordCount,int amount){
	char primary[9][6] = {"one","two","three","four","five","six","seven","eight","nine"};
	char secondary[9][8] = {"ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char tens[10][9] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	int i;
	int accumulator = 0;
	printf("\nword count is %d\n", wordCount);	
	
	if(wordCount == 1){
		accumulator = requestPrint(toConvert[0],1);
	}
	else{
		for(i = 0 ; i < wordCount ; i++){
			if(i == 0) accumulator += requestPrint(toConvert[0],1);
			else if(strcmp(toConvert[i],"hundred")==0) accumulator *= 100;
			else accumulator += requestPrint(toConvert[i],1); 
		}
	}
	printf("\nyey%d\n",accumulator);

	if(amount == 1) return accumulator*1000000;
	else if(amount == 2) return accumulator * 1000; 
	else return accumulator;
}

//========================================================================================================================//

int requestPrint(char find[], int type){
	char primary[9][6] = {"one","two","three","four","five","six","seven","eight","nine"};
	char secondary[9][8] = {"ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char tens[10][9] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	int i;
	if(type == 1){
		for(i=0;i<9;i++){
			if(strcmp(find,primary[i]) == 0){
				printf("\nA %d\n", i+1);
				return i+1;
			}

		}
		for(i=0;i<9;i++){
			if(strcmp(find,secondary[i]) == 0){
				printf("\nB %d\n", ((i+1)*10));
				return ((i+1)*10);
			}

		}
		for(i=0;i<9;i++){
			if(strcmp(find,secondary[i]) == 0){
				printf("\nB %d\n", i+10);
				return i+10;
			}
		}
	}
	
	return 1;
}

//========================================================================================================================//

void numberDelimited(int input,char delimiter, int position){
	char toPrint[8],n[8];
	int delimitFlag = 0,i;
	toStringThisNumber(input,n);			//convert integer input to string and store it to n
	
	for(i=0 ; i<strlen(n)+1 ; i++){
		if(delimitFlag == 0){				
			if(i == strlen(n)-position){	//delimit flag turns on when right position for delimiter is encountered
				toPrint[i] = delimiter;
				delimitFlag = 1;
				i--;
			}else toPrint[i] = n[i];
		}else toPrint[i+1] = n[i];			
	}
	toPrint[i] = '\0';						//end of string
	printf("\nNumber Delimited is /%s/",toPrint);
	return;
}

//========================================================================================================================//

void toStringThisNumber(int input,char stringInput[]){
	int len=0,temp,i,tempRemainder=0;
	temp = input;

	while(temp!=0){							//count length of number
		len++;
		temp=temp/10;
	}

	for (i = 0; i < len; i++){				//store every number
        tempRemainder = input % 10;			//to stringInput
        input = input / 10;
        stringInput[len - (i + 1)] = tempRemainder + '0';		//add '0' or 48 to convert to ascii equivalent
    }
    stringInput[len] = '\0';				//mark end of string :D
}

//========================================================================================================================//

