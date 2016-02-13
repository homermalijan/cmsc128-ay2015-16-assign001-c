#include<stdio.h>
#include<string.h>

void numberDelimited(int,char,int);
void toStringThisNumber(int,char[]);

//convert number to words
char* numToWords(int);
char* convertToWords(int, int);

//convert words to number
int convertToNumber(char[][10],int,int);
int requestPrint(char[]);
int wordsToNum(char*);

//misc functions
int checkInput(int);
void printMenu(int *);

main(){
	int choice=0,numberOutput=0;
	int input=0;
	char delimiter='\0';
	char wordOutput[256];
	int position=0;
	char words1[256],words2[256];
	do{
		printMenu(&choice);
		wordOutput[0] = '\0';					//to make sure string is empty everytime is is used

		switch(choice){
			case 1: printf("\n\nEnter Number (<= 100000): ");
					scanf("%d", &input);
					getchar();
					if(checkInput(input) == 1){
						printf("Input to big!");
						break;
					}else{
						strcat(wordOutput,numToWords(input));
						printf("Output: %s\n\n", wordOutput);
					}
					break;
			case 2: printf("\n\nEnter Number in Words (lower case; prints zero if number > 1000000) : ");
					fgets(words1,256,stdin);
					numberOutput = wordsToNum(words1);
					printf("\nOutput: %d\n", numberOutput);
					break;
			case 3: break;
			case 4: printf("\n\nEnter Number (<= 100000): ");
					scanf("%d", &input);
					getchar();
					if(checkInput(input) == 1){
						printf("Input to big!");
						break;
					}else{
						printf("Enter Delimiter (single character): ");
						scanf("%c", &delimiter);
						getchar();
						printf("Enter Position: ");
						scanf("%d", &position);
						getchar();
						strcat(wordOutput,numberDelimited(input,delimiter,position));
						printf("\nOutput: %s\n",wordOutput);
					}
					break;
			case 5: //exit
					break;
			default: printf("\nInvalid input\n");
		}

	}while(choice!=5);
}

//========================================================================================================================//

int checkInput(int x){
	if (x>1000000) return 1;
	else return 0;
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

char* numToWords(int input){
	int i = 0;
	char *pointer;
	char output[256] = "\0";
	if(input>1000000){									//number is too big
		printf("\nNumber too big!\n");
		return;
	}
	if(input == 0) strcpy(output,"zero");				//for zero input
	for(i = 1000000 ; i > 0 ; i = i/1000){				//divides the numbers into 3s
		switch(i){
			case 1000000: 	if(((input - input % i)/i) > 0) strcat(output, convertToWords((input - input % i)/i,1));		//million
							break;	
			case 1000:		if(((input - input % i)/i) > 0) strcat(output, convertToWords((input - input % i)/i,2));		//thousands
							break;
			case 1:			if(((input - input % i)/i) > 0) strcat(output, convertToWords((input - input % i)/i,3));		//hundreds
							break;
		}
		input = input%i;								//update current number
	}
	pointer = output;
	return pointer;
}

//========================================================================================================================//

char* convertToWords(int x,int y){
	char primary[9][10] = {" one"," two","three"," four"," five"," six"," seven"," eight"," nine"};
	char secondary[9][10] = {" ten"," twenty"," thirty"," forty"," fifty"," sixty"," seventy"," eighty"," ninety"};
	char tens[10][10] = {" ten"," eleven"," twelve"," thirteen"," fourteen"," fifteen"," sixteen"," seventeen"," eighteen"," nineteen"};
	char *pointer;
	char output[256]="";
	if(x/100 != 0) {
		strcat(output,primary[(x/100)-1]);
		strcat(output," hundred");	
	}
	
	x = x % 100;														//print only if not zero
	if(x/10 != 0){														//tens place print only if not zero
		if(x/10 != 1){													//checks for 11-19 (#pabebe case)
			strcat(output, secondary[(x/10)-1]);						//prints tens digit
			x = x % 10;
			if(x!=0) strcat(output, primary[x-1]);						//prints one digit
		}else strcat(output, tens[(x%10)]);
	}else strcat(output, primary[(x%10)-1]);	
	
	switch(y){															//print extension
		case 1: strcat(output," million");	
				break;
		case 2: strcat(output," thousand");	
				break;
	}
	
	pointer = output;
	return pointer;
}

//========================================================================================================================//

int wordsToNum(char input[]){
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
			accumulator += convertToNumber(forConverting, iterator,3);
			}
		}
	}
	
	if(accumulator > 1000000){
		printf("\nNumber too big!\n");
		return 0;
	}
	return accumulator;
}

//========================================================================================================================//

int convertToNumber(char toConvert[][10],int wordCount,int amount){
	int i;
	int accumulator = 0;
	
	if(wordCount == 1) accumulator = requestPrint(toConvert[0]);
	else{
		for(i = 0 ; i < wordCount ; i++){
			if(i == 0) accumulator += requestPrint(toConvert[0]);
			else if(strcmp(toConvert[i],"hundred")==0) accumulator *= 100;
			else accumulator += requestPrint(toConvert[i]); 
		}
	}

	if(amount == 1) return accumulator*1000000;
	else if(amount == 2) return accumulator * 1000; 
	else return accumulator;
}

//========================================================================================================================//

int requestPrint(char find[]){
	char primary[9][6] = {"one","two","three","four","five","six","seven","eight","nine"};
	char secondary[9][8] = {"ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char tens[10][9] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	int i;
		for(i=0;i<9;i++) if(strcmp(find,primary[i]) == 0) return i+1;
		for(i=0;i<9;i++) if(strcmp(find,secondary[i]) == 0)	return ((i+1)*10);
		for(i=0;i<9;i++) if(strcmp(find,secondary[i]) == 0) return i+10;
	return 0;
}

//========================================================================================================================//

char* numberDelimited(int input,char delimiter, int position){
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
	return toPrint;
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

