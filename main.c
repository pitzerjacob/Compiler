/*FILE HANDLER AND SCANNER UTILITY FOR USE WITH CUSTOM COMPILER
	CSC 460
	GROUP 4 MEMBERS:
		BARRY HUEY hue6208@calu.edu                 
		JACOB PITZER pit7706@calu.edu 
		JAQUA STARR sta7689@calu.edu
		
		
*/

#include "file_util.h"


char inFile[MAX_CHAR], outFile[MAX_CHAR],tmpName[MAX_CHAR],c='\0',choice='\0';
			// typedef to token for easier reference
int tokNum=0,lexErrors=0,synErrors=0,counter=0;
int main (int argc, char *argv[])
{
	int i=0;
         if(getInFile(argc, argv,&input));
		{
		 				
			if(getOutFile(argc, argv, &output, &listing, &tmp)) //call function for output file opening
			{
			
				 scanner(input,output,listing);
				 closeFiles( input,  output,  listing,  tmp); //call function to close any open files
				 printf("\n There were %d tokens total",tokNum);
				 printf("\n There were %d Lexical errors\n",lexErrors);
				
			};
			
		}
	
  printf("\n\tHAVE A NICE DAY \n");
  system ("Pause");
  return 0;
}
