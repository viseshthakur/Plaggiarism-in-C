#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include "files.h"

/*
  Inputs : This function has three inputs data of file in form string, 
          base index of the string char,index until where to produce 
          sequences
  Functioning : It accepts string and index position 
                Allocates size and removes spaces                              
  Output : It returns string which has a sequence 
*/
char * subString(char * s,int i,int n)
{
    char* substr=(char*)malloc(sizeof(char)*1000);
    int p=0;
    strcpy(substr,"");
    for (int j = i; j <= n;j++)
	  {
        substr[p] = s[j]; 
        p++;
    }
    substr[p] = '\0'; 
    return substr;
}

/*
  Inputs : This function has two inputs the whole file in 
            form of string and an char array to store sequences.
  Functioning : This is used to accept string and passes
            base index and last index to other function called substring where 
            each element is stored in array and count is incremented
  Output : It returns total len_of_seq_into_filesber of sequences/combinations produced
*/
int  split(char * s,char * seq_file1[])
{
  	char * s1;
  	int l=strlen(s);
   	int i=0,n=2,j=0,count=0;
	  for (int inc = 0; i<l;i++)
	  {
		    for (int j=inc;j<l; j++)
		    {
		        s1=subString(s,inc,j);
            seq_file1[count]=s1;
		        count++;
		    } 
	  }
	  return count;
}


int main(int argc, char const *argv[])
{
  printf("-------------Largest Common Substring-----------------\n");
	char *string1 = (char*)malloc(sizeof(char)*100);   //
  char *string2 = (char*)malloc(sizeof(char)*100);
	int len1,len2;
	int c[100];
	int n;
	char * seq_file1[1000];
	char * seq_file2[1000];
	char * final_seq[1000];
	char * stemp;
  struct dirent *dic; 
  float match_percent;
  DIR *dir;                      //declare a DIR variable
  char folder[1000];
  chdir(argv[1]);                //change directory in built
  if (argc==2)                  
  {
    dir=opendir(argv[1]);       //during execution if path is added it gets openned and stored in dir
    strcpy(folder,argv[1]);
    strcat(folder,"\\");        // it says that to accept \ if any 
  }
  else
  {
    dir= opendir(".");          // if no argument is passed it takes the directory where program is present
    strcpy(folder,".");
    strcat(folder,"\\");
  }
  char *Filen[100];
  if (dir == NULL)              // if path not valid it prints wrong path
  {
    perror(" wrong path : ");
  }
  int a;
  int inc=0;
  while ((dic = readdir(dir)) != NULL)
  {
    if (strlen(dic->d_name)>2)      //accepts all .txt files
    {
        a = file_cmp(dic->d_name);
        if(a==0)
        {
          Filen[inc]=malloc(strlen(dic->d_name));
          strcpy(Filen[inc],dic->d_name);
          inc=inc+1;
        } 
    }
  }
  for (int z = 0; z < inc; ++z)       //to print in matrix format 1st row
  {
      printf("  \t\t%s",Filen[z]);
  }
  printf("\n");
  for (int j = 0; j < inc; j++)       //for every file we will check LCS with other files and itself
    {
      printf("%s ",Filen[j]);
      for (int k = 0; k < inc; k++)
      {
          if(j!=k)                    //if both are diff files we perform following operations
          {
            char filepath1[1000];
            char filepath2[1000];
            strcpy(filepath1,folder);
            strcpy(filepath2,folder);
            strcat(filepath1,Filen[j]);
            strcat(filepath2,Filen[k]);
            string1=file_open(filepath1);     //opens the file and stored in string1
            string2=file_open(filepath2);
            int length1=strlen(string1);      //it calculates the length of string
            int length2=strlen(string2);
          	len1=split(string1,seq_file1);           // string1 and empty array to split Function
            len2=split(string2,seq_file2);
            int z=0,count=0;
            char temp[100];
            strcpy(temp," ");
            for (int inc = 0; inc < len1;inc++) //comapares every string sequence of file 1 with other file string array 
            {
       	      for (int j = 0; j < len2; j++)
       	      {
       		       if(strcmp(seq_file1[inc],seq_file2[j])==0)    //if two sequences are equal increment count
                 {
       			        count=count+1;
       			        final_seq[z]=seq_file1[inc];
       			        strcpy(temp,seq_file1[inc]);              //add it to temp and calculate length
       			        int x=strlen(temp);
       			        c[z]=x;                                   //store length in array
       			        z++;
       	          }
       	      }
            }
        int m=c[0];
        for (int inc = 0; inc < z; inc++)       //checks for highest count or sequence
        {
       	  if(m<c[inc])
          {
       		   m=c[inc];
       	  }
        }
        float len_of_seq_into_files=(m*2);            //LCS Formula  
        float total_length_of_files=(length1+length2);
        match_percent=(len_of_seq_into_files/total_length_of_files)*100;
      }
      else        //if two files are same
      {
        match_percent=100.00;  
      }
      printf("\t\t%0.2f",match_percent);    //prints % /t/t are used for spaces
    }
    printf("\n");
  }
  return 0;
}
