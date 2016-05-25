/**********************************************************************     
* *   Copyright (c)2015,WK Studios   
* *   Filename:  A.h 
* *   Compiler: GCC  vc 6.0    
* *   Author:WK     
* *   Time: 2015 20 6  
* **********************************************************************/ 

#include"Translate.h"
#include<iostream>
using namespace std;

extern int CommentConvert(FILE *inputfile, FILE *outputfile);

int main()
{
	FILE *fpIn = NULL;  //inputfile
	FILE *fpOut = NULL; //outputfile
	
	fpIn = fopen("input.txt","r");
	if(NULL == fpIn)
	{
		cout<<"Open input file fail!"<<endl;
		return -1;
	}
	

	fpOut = fopen("output.txt","w");
	if(NULL == fpOut)
	{
		cout<<"Open output file fail!"<<endl;
		return -1;
	}
		CommentConvert(fpIn,fpOut); 
	
	fclose(fpIn);
	fclose(fpOut);
	return 0;
}