#include "file_util.h"


int getInFile(int arg_count,  char * argv[], FILE ** input) 
{
//////////     INPUT FILE NAME LOOP ACCEPTS AN EXISTING NAME OR LOOPS UNTIL ONE IS FOUND OR USER ENTERS NULL    ////////////////////////////
    int i=0, cont = 0, ext, inExist = 0;
    char *d;
    char inFile [MAX_CHAR];

    while(inExist==0)
    {
		cont=0;
        fflush(stdin);
   		printf("\t%d parameters entered from command line", (arg_count-1));
		printf("\n\tEnter an Input File Name, or Press Enter to Exit: ");  //prompts user for input file name


//READ AND PARSE THE STRING

	gets(inFile);
		if (inFile[0] != '\0')
		{
			d = strchr(inFile, '.');

				 if(d == NULL)
					strcat(inFile,".IN");


                 if(fopen(inFile,"r") != NULL)
	               inExist= 1;       //try opening the input file, if successful inExist !=0


			     if (inExist!=0)
				{
					*input=fopen(inFile,"r");                                        //if file exists open it for reading
					printf("\n\t*SUCCESS* Opened Input File: [%s] \n", inFile);       //inform user input file successfully opened
				}
				else 
					printf("\n\t*ERROR* Input File: [%s] Could Not be Located\n", inFile);    //if file doesn't exist loop again until user exits
		}
		else
		{
			inExist=1;
		}
	}
    return inExist;	
};

int getOutFile(int arg_count,  char * argv[], FILE **output, FILE **listing, FILE **tmp)
{

	int again, i, p, cont, ext, outExist;
    char c, choice;
    char outFile[MAX_CHAR],listFile[MAX_CHAR], outBak[MAX_CHAR],tmpName[MAX_CHAR];
    char *d;


	outExist = 0;
	while(outExist==0)   //output file control loop, loops until an output file is
    {                               //successfully opened or user terminates
		cont=0;
		outExist=1;
		choice='\0';
        printf("\n\tEnter an Output file Name: ");
		gets(outFile);
		
		if (outFile != NULL)
		{
			d = strchr(outFile, '.');

				if(d == NULL)
                   strcat(outFile, ".OUT") ;

				 if((fopen(outFile,"r")))
				 {
					
					 printf("\tThis File Name is Already in Use.\n");
					 printf("\tWould You Like To OverWrite It?");
					 choice=getchar();
						if(choice=='Y' || choice == 'y')
						{
							 copy_backup(outFile);
						}; 
				 };
			
                *output=fopen(outFile,"w");                                      //opens output file searches for the '.' keeps only 
                printf("\n\t*SUCCESS* Opened  Output  File: [%s]", outFile);		// that which comes before the '.' and adds .lst extern		
				memset(listFile, '\0', MAX_CHAR);								//after that open listing file with .lst extension
				d = strchr(outFile, '.');
				p = (int)(d - outFile);
				strncpy(listFile, outFile, p);
                strcat(listFile,".LST");
                *listing=fopen(listFile,"w");
                printf("\n\t*SUCCESS* Opened  Listing File: [%s]\n", listFile);
                outExist=1;
                            
		};
		return outExist;
	}
                        
};


void copy_backup(char *outFile)   // copies current contents of output to backup file
{
	int p;
	char *d;
	char outBak[MAX_CHAR];
	FILE *back_up, *output;
	

	output=fopen(outFile,"r");      						// open local file output and set it to outFile
	memset(outBak,'\0',MAX_CHAR);  							// clears outBak array
	d = strchr(outFile, '.');     							 // locate first instance of '.'
	p = (int)(d - outFile);									// subtract remaining string from outFile to get integer value of lettters before the .
	strncpy(outBak, outFile, p);  							// copy to the dot
	strcat(outBak,".BAK");   							 //concatenate .BAK extension
	back_up=fopen(outBak,"w");  							//open backup for writing
	printf("\n\t*SUCCESS* Created Backup  File: [%s]",outBak);
	
	char c;
   
    while((c=getc(output))!=EOF)      //while output is not at the end of file copy to backup
    {
        putc(c,back_up);
  	};
									//since backup file will be used outside this function close both local output and backup
		fclose(back_up);
}

void printToken(FILE *input, FILE *output, FILE *listing,token tok[], int count)
{
	int i; 
	
    static int j;
	char c;
	char begin[]="BEGIN";
	char end[]="END";
	char read[]="READ";
	char write[]="WRITE";
	char IF[]="IF";
	char ENDIF[]="ENDIF";
	char GOTO[]="GOTO";
	char integer[]="INTEGER";
	char var[]="VARIABLE";
	char err[]="ERROR";
	char lpar[]="LEFT PARANTHESIS";
	char rpar[]="RIGHT PARANTHESIS";
	char semi[]="SEMI COLON";
	char comma[]="COMMA";
	char assign[]="ASSIGNMENT OPERATOR";
	char add[]="ADDITION OPERATOR";
	char sub[]="SUBTRACTION OPERATOR";
	char less[]="LESS THAN OPERATOR";
	char great[]="GREATER THAN OPERATOR";
	char eq[]="EQUALS OPERATION";
	char scaneof[]="SCAN EOF";
    
		


			if(tok->str =='\0' ||  tok->num!=10)   // if its a blank line or not an error print it
			{
				j++;
				fprintf(listing,"%d) ",j);
				fprintf(listing,"%s",tok->str);
			}
				else 										//else it is an error
				{
			
					fprintf(listing,"ERROR Not Recognized [%s]\n ",tok->str);
				}
			
				
			for(i=0; i<count;i++)
			{
			 if(tok->num==1){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n",tok->num, begin,tok->len,tok->str );
			 tok++;}
			 else if(tok->num== 2){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok->num, end,tok->len,tok->str );
			 tok++;}
			 else if(tok->num== 3){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n",tok->num, read,tok->len,tok->str );
			 tok++;}
			 else if(tok->num== 4){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n",tok->num, write,tok->len,tok->str );
			tok++;}
			 else if(tok->num== 5){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n",tok->num, IF,tok->len,tok->str );
			 tok++;}
			 else if(tok->num== 6){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n",tok->num, ENDIF,tok->len,tok->str );
			 tok++;}
			 else if(tok->num== 7){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n",tok->num, GOTO,tok->len,tok->str );
			 tok++;} 
			 else if(tok->num==8){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n", tok->num, var, tok->len,tok->str);
			 tok++;}
			 else if(tok->num==9){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n", tok->num, integer, tok->len,tok->str);
			 tok++;}
			 else if(tok->num==10){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %.*s\n", tok->num, err,tok->len ,tok->str);
			 tok++;}
			 else if(tok->num==11){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %.*s\n", tok->num, lpar,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==12){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %.*s\n", tok->num, rpar,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==13){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %.*s\n", tok->num, semi,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==14){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE:%s\t\t\t ACTUAL TOKEN: %.*s\n", tok->num, comma,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==15){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %.*s\n", tok->num, assign,tok->len,tok->str);
			 tok++;}
			 else if(tok->num==16){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %.*s\n", tok->num, add,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==17){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %.*s\n", tok->num, sub,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==18){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %.*s\n", tok->num, less,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==19){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %.*s\n", tok->num, great,tok->len, tok->str);
			 tok++;}
			 else if(tok->num==20){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %.*s\n", tok->num, eq,tok->len, tok->str);
			 tok++;}
			 
		
			
			};
	
}

void closeFiles(FILE *input, FILE *output, FILE *listing, FILE *tmp)
{
	if(input)
		fclose(input);
	if(output)
		fclose(output);
	if(listing)
		fclose(listing);
	if(tmp)
		fclose(tmp);
	if(back_up)
		fclose(back_up);
};

void scanner (FILE *input, FILE *output, FILE *listing)
{
	token tok[MAXBUFF];
	char c;
	char lineBuff[MAXBUFF];
	 int count=0,i=0;
	clear_lineBuff(lineBuff);								//make sure line buff is empty
	while(fgets(lineBuff,MAXBUFF,input) !=NULL)				//gets a line from input
	{
		i++;
		count=Tokenize(lineBuff,tok);					//calls func tokenize and returns number of tokens on that line
		printf("\nLine %d has %d tokens:",i,count);
		ident_token(count,tok);
		clear_lineBuff(lineBuff);						//clears the line buffer for next line
	}
	

}

void clear_lineBuff(char * lineBuff)				
{
	memset(lineBuff,'\0',MAXBUFF);				//sets value of line buff to null
}

int Tokenize( char *lineBuff,  token tok[])
{
	
	
	char *begin,*c;
	int count=0;
	while(*lineBuff)       //dereference linebuff and loop while not null
	{
		
		while(isspace(*lineBuff))		//consume leading whitespace
			lineBuff++;
		
		begin=lineBuff;					//set char ptr begin to start of first detected character
		
		while(*lineBuff && !isspace(*lineBuff))			//if not null and not space go to next character
			lineBuff++;
		
			
			if(count<MAXBUFF)				    //if token is within parameters 
			{									//assign tok str to the value pointed to by begin
				tok[count].str=begin;			//length of token is the difference of current pos ptr and linebuff ptr
				tok[count].len= (lineBuff-begin);
				lineBuff++;
			}
			count++;					//inc token count
	}
	return count;
}	

void ident_token(int count, token tok[])
{
	int i; 
	int resWord=0,isInt=0,isSym=0;
	token tmp;
	for(i=0; i<count;i++)
	{
		tmp.str=0;
		tmp.len=0;
		tok[i].num=0;
		resWord=0;
		//printf("\n%s\n",tok[i].str);
		
		if (isalpha(*tok[i].str))  //if the string begins with an alpha
		{
			
			tmp.str=tok[i].str;			//assign a tmp token the values
			tmp.len=tok[i].len;
			resWord=checkReserved(tmp);  //pass tmp token into function to check if it is reserved
			tok[i].num=resWord;
			if(tok[i].num<8)			// reserved words are enum status 1-7
				printf("\n\t[%.*s]IS A RESERVED WORD ENUM %d",tmp.len,tmp.str,tok[i].num);
				
			else                  		//variable are enum 8
				printf("\n\t[%.*s] IS A VARIABLE ENUM %d",tmp.len,tmp.str,tok[i].num);
				
		
			
			//printToken(input,output,listing,tok);				//print the token
		}
		
		else if(isdigit(*tok[i].str))		//see if token begins with int
		{
			tmp.str=tok[i].str;
			tmp.len=tok[i].len;
			printf("\n\t[ %.*s ]",tmp.len,tmp.str);
			isInt=checkInt(tmp);				//checks if all of the str is digits, returns 1 if not int
			tok[i].num=isInt;					// assigns either 1 or 0 to struct value. 1= is not an int 0= is an int
				if(tok[i].num==9)				// ints are enum 9
					printf(" IS AN INT ENUM %d",tok[i].num);
					
				else							//if string contains any char other than int
					printf(" IS A LEX ERROR %d", tok[i].num);
					
				
			//printToken(input,output,listing,tok);				//print the token
		}
		else 
		{
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!here make loop to go one char ata atime allow no spaces in expressions
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!but require spaces before and after keywords, variables ,and expressions
			//for (int k=0; k<tok[i].len;k++)
		//	{
			tmp.str=tok[i].str;
			tmp.len=tok[i].len;
			printf("\n\t[ %.*s ]",tmp.len,tmp.str);
			isSym=checkSymbol(tmp);				//checks to see if token is any of the reserved characters
			tok[i].num=isSym;
				if(tok[i].num>10 && tok[i].num<21)		//reserve char are enum 10-21
					printf(" IS A SYMBOL ENUM %d", tok[i].num);
					
				else									//if not a aplha digit or symbol, its an error
					printf(" IS A LEX ERROR ENUM %d",tok[i].num);
					
			//}
			//printToken(input,output,listing,tok);				//print the token
		}
		
		
	}
		//printToken(input,output,listing,tok,count);
}	


int checkReserved(token tmp)
{
	
	char string[MAX_CHAR];
	int resWord=0;
	memset(string,'\0',MAX_CHAR);
	strncpy(string, tmp.str,tmp.len);

	 if(strcasecmp(string,"begin")==0)
		 resWord=1;
	 else if (strcasecmp(string,"END") ==0 ) 
		resWord=2;
	 else if (strcasecmp(string, "READ")==0)
		resWord=3;
	 else if (strcasecmp(string,"WRITE")==0 )
		resWord=4;
	 else if (strcasecmp(string,"IF") ==0) 
		resWord=5;
	 else if (strcasecmp(string,"ENDIF")== 0)
		resWord=6;
	 else if (strcasecmp(string,"GOTO") ==0)
		resWord=7;
	 	 	
	else		
		resWord=8;
	//printf("\n%d\n",resWord);	 
	
	return resWord;

	
}

int checkInt(token tmp)
{
	int i; 
	int digit=9;
	char *ptr;
	ptr=tmp.str;
	
	
	for(i=0; i<tmp.len;i++)				//loop size of token
	{
		
		if(!isdigit(*ptr))				//dereferencing ptr and check if its a digit, if not give it enum 10 for lex error
			digit=10;
		
		ptr++;							//inc the pointer to next char
	}
	return digit;
	
}
int checkSymbol(token tmp)
{
	char string[MAX_CHAR];
	int sym=0;
	memset(string,'\0',MAX_CHAR);
	strncpy(string, tmp.str,tmp.len);		//copy into char array for strcmp, see if it matches any reserved tokens

	 if(strcmp(string,"(")==0)
		 sym=11;
	 else if (strcmp(string,")") ==0 ) 
		sym=12;
	 else if (strcmp(string, ";")==0)
		sym=13;
	 else if (strcmp(string,",")==0 )
		sym=14;
	 else if (strcmp(string,":=") ==0) 
		sym=15;
	 else if (strcmp(string,"+")== 0)
		sym=16;
	 else if (strcmp(string,"-") ==0)
		sym=17;
	 else if(strcmp(string,"<") ==0)
		 sym=18;
	 else if(strcmp(string,">")==0)
		 sym=19;
	 else if(strcmp(string,"=")==0)
		 sym=20;
		 	
	else						//if it does not its a lex error enumerated by 10
		sym=10;
		 
	
	return sym;
}
