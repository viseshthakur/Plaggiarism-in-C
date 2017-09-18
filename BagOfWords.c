#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include "files.h"

struct func								//Defining a structure for storing words and counts
{
	char * words;
	int count;
};
														//Above 5 functions are declared
int characterSplitting(char* s,struct func f1[]);
int calDotProduct(int length1,int length2,struct func f[],struct func f2[]);
float eucldieanNormFormula(int length1,struct func f[]);
int rem_dup(int k,struct func fi1[]);
void freq_count(int i,char * a[],struct func fi1[]);

											
int main(int argc, char const *argv[])					//main execution starts here
{
	printf("----------------Bag Of Words-----------------\n");
	struct dirent *dic; 
	char folder_path[1000];
	DIR *dir ;	
	chdir(argv[1]);				//condition for openning directory using path through cmd 
	if (argc==2)
	{
		dir=opendir(argv[1]);
		strcpy(folder_path,argv[1]);
		strcat(folder_path,"\\");
	}
	else
	{
		dir= opendir(".");		//if no arg passed it will execute from same directory
		strcpy(folder_path,".");
		strcat(folder_path,"\\");
	}
	
	char *file[100];			
	if (dir == NULL) 			//if no path found prints Path is Wrong
	{
		perror("Path is Wrong!");
	}


	int check;
	int inc=0;				//to check files from directory and store each file in array
	while ((dic = readdir(dir)) != NULL)
	{
		if (strlen(dic->d_name)>2) 
		{
			check = fileCompare(dic->d_name);		//goes to user defined function in file.h header file
	   		if(check==0)
	   		{
				file[inc]=malloc(strlen(dic->d_name));
				strcpy(file[inc],dic->d_name);
				inc=inc+1;
	   		}	
	    }
	}

	for (int inc1 = 0; inc1 < inc; ++inc1)
	{
		printf("\t\t%s",file[inc1]);	//for printing matrix first line
	}
	printf("\n");
	char *string1 = (char*)malloc(sizeof(char)*100);
	char *string2 = (char*)malloc(sizeof(char)*100);
	int length1,length2;
	float result;
	float plagiarism[10];
	int temp=0;
	struct func fi1[100];
 	struct func fi2[100];
	for (int j = 0; j < inc; j++)		//for every file it is checked with every other file
	{
		printf("%s",file[j]);
		for (int k = 0; k < inc; k++)	//for first file it executes or compares with every file
	 	{
			if(j!=k)					//if both files not equal,it procedes with execution of bag of words	
			{
	 			char filepath1[1000];
	 			char filepath2[1000];
	 			strcpy(filepath1,folder_path); //copy folder path to variable filepath
	 			strcpy(filepath2,folder_path);
	 			strcat(filepath1,file[j]);		// concats file to the path and starts execution
	 			strcat(filepath2,file[k]);
	 			string1=openFile(filepath1); 		// open a file using user defined function in file.h header
	 			string2=openFile(filepath2);
	 			length1=characterSplitting(string1,fi1); 	//passing file string and struct function
				length2=characterSplitting(string2,fi2);
				int num_dot=0;
				float den_fi1,den_fi2=0.0;
				num_dot=calDotProduct(length1,length2,fi1,fi2);	//calculating dot product by comparing struct of file1 and file2 which has words and frequencies
				den_fi1=eucldieanNormFormula(length1,fi1);	//calculates freq vector
				den_fi2=eucldieanNormFormula(length2,fi2);
				float den=(den_fi1*den_fi2); 				 
				result=(num_dot/den)*100;			// result=dot/(fv1*fv2)
			}
			else
			{
				result=0.0;
			}
			printf("\t\t%0.2f",result);        		//printing result with spaces and rounding off 
	 	}
	 	printf("\n");
	}
	return 0;
}


/*
	Inputs : It accepts String of File and a struct variable.

	Functioning : It splits at spaces  and stores every word in struct fi. 
					It has function in function to removes dups and calculate
					count.

	Output : Returns length of the words in file string and appends to struct fi 
*/
int characterSplitting(char* string,struct func fi[])
{
	char * arr[50];
	int inc=0;
	int c[100];
	char * token=strtok(string," ");
	while(token!=NULL)
	{
		arr[inc]=token;
		fi[inc].words=token;
		inc++;
		token=strtok(NULL," ");
	}
	int num_of_words=inc,length;
	freq_count(inc,arr,fi);
	length=rem_dup(num_of_words,fi);
	return length;
}


/*
	Inputs : 	Accepts Number of words = inc , arr = Array of Words, struct fi1

	Functioning : For every word it will check for every other words
				  if they are equal count is incremented and assigned 
				  to the words count in struct fi1

	Ouputs : 	it returns void
*/
void freq_count(int inc,char * arr[],struct func fi[])
{
	int j1=0;
	for(int j=0;j<inc;j++)
	{
		int count=1;
		for(int l=j+1;l<inc;l++)
		{
			int r=strcmp(arr[j],arr[l]);
			if(r==0)
			{
				count=count+1;
			}
		}
		fi[j1].count=count;
		j1=j1+1;
	}
}

/*
	Inputs : It accepts number of words and also struct fi1 

	Function : It removes duplicates if any inside the struct fi1 and 
	returns length of the words count

	Ouputs : Returns length of the words in fi1 
*/
int rem_dup(int num_of_words,struct func fi[])
{
	int length=0;
	for(int j=0;j<num_of_words;j++)
	{
		for(int y=j+1;y<num_of_words;)
		{
			if(strcmp(fi[j].words,fi[y].words)==0)
			{
				for (int z = y; z < num_of_words; z++)
					{
						fi[z].words=fi[y+1].words;		
					} 
					num_of_words=num_of_words-1;
			}
			else
			{
				y++;		
			}
		}
		length=length+1;
	}
	return length;		
}

/*
	Inputs : Length1 of words from file 1 , Length of words from file 2,
				passing struct fi1 and struct fi2 (two file structs).
	Function: Checks for common words in both structs and multiplies it 
				count values and sum up till all done.

	Output : Calculates Dot Product and returns it.
 */
int calDotProduct(int length1,int length2,struct func fi1[],struct func fi2[])
{
	int num_dot=0;
	for (int inc = 0; inc < length1; inc++)
	{
		for (int j = 0; j < length2;j++)
		{
			if(strcmp(fi1[inc].words,fi2[j].words)==0)
			{
				num_dot=num_dot+(fi1[inc].count*fi2[j].count);
			}
		}
	}
	return num_dot;
}

/*

	Input : Accepts length of words of fi1, and also struct fi1 is passed

	Functioning: it calculates power of 2 of every freq count and sum it to a var
					and squaring this var gives us eucldieanNormalFormula.

	Ouput : Returns float value .i.e, vector from

*/
float eucldieanNormFormula(int length,struct func fi[])
{
	float den_fi=0.0;
	for (int inc = 0; inc < length; inc++)
	{
		den_fi=den_fi+pow(fi[inc].count,2);
	}
	den_fi=sqrt(den_fi);
	return den_fi;
}