char* dataFormat(char *ch)
{
	char* data = (char *) malloc(sizeof(char) * 1000);
	strlwr(ch);					// it lowers all characters in string
	int i=0,j=0;
	int a = strlen(ch);
	while(i!=a)
	{
		if (ch[i]==32||ch[i]>96&&ch[i]<123)	// checks wether string has any special characters , and they are removed
		{
			data[j]=ch[i];
			j++;
		}
		i+=1;
	}
	data[i]='\0';
	return data;
	
}
int fileCompare(char *file_name)
{
	char *cmpr = (char *) malloc(sizeof(char) * 3);
	cmpr = "txt";
	char *ret;
	int a;
	ret = strstr(file_name,cmpr); 			//used to compare files
	if(ret == NULL)
	{
		ret="EMPTY";
	}
	a=strcmp(ret,cmpr);
	return a;
}
char* openFile(char *file_name)
{
	
	FILE * fp;
	FILE * fp1;
	char *s = (char*)malloc(sizeof(char)*100);
	char *s2 = (char*)malloc(sizeof(char)*100);
	char *d = (char*)malloc(sizeof(char)*100);
	// s2[100];
	int i=0,j=0;
	fp = fopen(file_name, "r"); 			//opens file and reads it
  	if(!fp) 
  	{
  		return NULL;  						//prints NULL if no file
  	}
  	else
  	{ 
  		strcpy(s,"");						//this is used to replace \n with spaces
  		strcpy(s2,"");
  		while (fgets(s2,1000,fp)!=NULL) 
  		{
  			int temp2=strlen(s2);
  			if (s2[temp2-1]=='\n')			//if multiple lines exist it replaces \n with " "
  			{
  			s2[temp2-1]=' ';
  			}
  	  		strcat(s,s2);
		}
    }
    d=dataFormat(s);					//string is forwared to dataFormat function
    return d; 	
}