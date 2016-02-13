
//========================================================================================================================//
void printMenu(int *choice){
	printf("\n\n\tI===============================I\n");
	printf("\tI [1] Numbers to Words          I\n");
	printf("\tI [2] Words to Numbers          I\n");
	printf("\tI [3] Convert to Currency       I\n");
	printf("\tI [4] Delimit                   I\n");
	printf("\tI [5] Exit                      I\n");
	printf("\tI===============================I\n");
	printf("   Choice: ");
	scanf("%d", choice);	
	getchar();
}


//========================================================================================================================//

char* convertToWords(int x,int y){
	char primary[9][10] = {" one"," two"," three"," four"," five"," six"," seven"," eight"," nine"};
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

int convertToNumber(char toConvert[][10],int wordCount,int amount){
	int i;
	int accumulator = 0;
	
	if(wordCount == 1) accumulator = requestPrint(toConvert[0]);				//request for integer counterpart
	else{
		for(i = 0 ; i < wordCount ; i++){
			if(i == 0) accumulator += requestPrint(toConvert[0]);
			else if(strcmp(toConvert[i],"hundred")==0) accumulator *= 100;		//if "hundred" is encountered, multiplies current number by 100
			else accumulator += requestPrint(toConvert[i]); 
		}
	}

	if(amount == 1) return accumulator*1000000;						//if it end with million, multiplies it with 1 million
	else if(amount == 2) return accumulator * 1000; 				//else if thousand, multiplies it with 1 thousand
	else return accumulator;										//else does nothing :)
}


//========================================================================================================================//

int requestPrint(char find[]){										//search for a match
	char primary[9][6] = {"one","two","three","four","five","six","seven","eight","nine"};
	char secondary[9][8] = {"ten","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
	char tens[10][9] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
	int i;
		for(i=0;i<9;i++) if(strcmp(find,primary[i]) == 0) return i+1;			//returns number
		for(i=0;i<9;i++) if(strcmp(find,secondary[i]) == 0)	return ((i+1)*10);	//depending on position
		for(i=0;i<9;i++) if(strcmp(find,secondary[i]) == 0) return i+10;		//and which array it is found
	return 0;
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
