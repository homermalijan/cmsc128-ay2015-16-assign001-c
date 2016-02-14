//number delimiter
void numberDelimited(int,char,int);
void toStringThisNumber(int,char[]);

//convert number to words
void numToWords(int);
char* convertToWords(int, int);

//convert words to number
int convertToNumber(char[][10],int,int);
int requestPrint(char[]);
int wordsToNum(char*);

//convert to currency
void convertToCurrency(char[],char[]);

//misc functions
void printMenu(int *);



//========================================================================================================================//

void convertToCurrency(char wordA[256], char wordB[256]){
	int x = wordsToNum(wordA);											//reuse wordsToNum function to convert
	wordB[3] = '\0';
	if (x == -1) return;
	
	if (x <= 1000000){
		if(strcasecmp(wordB,"PHP")==0) printf("Output: PHP");			//check currency
		else if(strcasecmp(wordB,"JPY")==0) printf("Output: JPY");
		else if(strcasecmp(wordB,"USD")==0)	printf("Output: USD");
		else{
			printf("\nInvalid Currency! ");
			return;
		}
		printf("%d\n", x);												//print number
	}
	else printf("\nNumber is too big!\n");
	return;
}

//========================================================================================================================//

void numToWords(int input){
	int i = 0;
	char output[256] = "\0";
	if(input > 1000000){								//number is too big
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
	printf("Output: %s\n\n", output);
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

	for(i = 0 ; i < wordCount; i++){									//accumulates every three numbers
		if(strcmp(choppedInput[i],"million")==0){						//to accumulator
			accumulator += convertToNumber(forConverting, iterator,1);	//includes
			iterator = 0;												//multiplying my 1million for million standing
		}else if(strcmp(choppedInput[i],"thousand")==0){				//and 1 thousand for thousand standing
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
		return -1;
	}
	return accumulator;
}

//========================================================================================================================//

void numberDelimited(int input,char delimiter, int position){
	char toPrint[8],n[8];
	int delimitFlag = 0,i;
	
	if(input >1000000){
		printf("\nNumber is too big!\n");
		return;
	}
	
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
	printf("\nNumber Delimited is %s",toPrint);
	return;
}

