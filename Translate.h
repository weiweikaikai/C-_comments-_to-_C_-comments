/**********************************************************************     
* *   Copyright (c)2015,WK Studios   
* *   Filename:  A.h 
* *   Compiler: GCC  vc 6.0    
* *   Author:WK     
* *   Time: 2015 20 6  
* **********************************************************************/

#include<iostream>
using namespace std;
#define STACKSIZE 1024
#define UL unsigned long

extern int CommentConvert(FILE *inputfile, FILE *outputfile);

typedef enum
{
	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	STR_STATE,
	END_STATE
}STATE_ENUM;//״̬�б�

typedef struct
{
	FILE *inputfile;
	FILE *outputfile;
	STATE_ENUM ulstate;
}STATE_MACHINE;  //״̬��

//
STATE_MACHINE g_state = { 0 };

///////////////////////////////////////////////////
void EventPro(char ch);//�¼�����
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
void EventProAtStr(char ch);
////////////////////////////////////////////////////

int CommentConvert(FILE *inputfile, FILE *outputfile)
{
	if (inputfile == NULL || outputfile == NULL)
	{
		cout << "input argument Invalid!" << endl;
		return -1;
	}

	g_state.inputfile = inputfile;
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;  //��ʼ״̬Ϊ��ע��״̬

	char ch;
	while (g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile); //
		EventPro(ch);
	}
	return 0;
}

void EventPro(char ch)  //�¼�����ģ��
{
	switch (g_state.ulstate)   //��ͬ���¼�״̬ʹ�ò�ͬ��״̬����
	{
	case NO_COMMENT_STATE:
		EventProAtNo(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp(ch);
		break;
	case STR_STATE:
		EventProAtStr(ch);
		break;
	case END_STATE:
		break;
	}
}

void EventProAtNo(char ch)
{
	char nextch;
	switch (ch)
	{
	case '/':   // // /* 
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/') // C++
		{
			fputc('/', g_state.outputfile);
			fputc('*', g_state.outputfile);		//��CPP��//ת��Ϊ/*
			g_state.ulstate = CPP_COMMENT_STATE;//ת��ΪCPP״̬
		}
		else if (nextch == '*') //C
		{
			fputc(ch, g_state.outputfile);
			fputc(nextch, g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;//ת��ΪC״̬
		}
		else
		{
		}
		break;
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	case '"':
		fputc('"', g_state.outputfile);
		g_state.ulstate = STR_STATE;
		
		break;
	default:
		fputc(ch, g_state.outputfile);
		break;
	}
}
void EventProAtC(char ch)
{
	char nextch;
	switch (ch)
	{
	case '*':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(ch, g_state.outputfile);
			fputc(nextch, g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ', g_state.outputfile);
			fputc(' ', g_state.outputfile);//Ƕ��ע���������ո����
		}
		break;
	default:
		fputc(ch, g_state.outputfile);
		break;
	}
}

/// Events the pro at CPP.

void EventProAtCpp(char ch)
{
	//123  /*123
	char nextch;
	switch (ch)
	{
	case '\n': //�������
		fputc('*', g_state.outputfile);
		fputc('/', g_state.outputfile);
		fputc('\n', g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case EOF:
		fputc('*', g_state.outputfile);
		fputc('/', g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/') //  (Ƕ��//)
		{
			fputc(' ', g_state.outputfile);
			fputc(' ', g_state.outputfile);
		}
		else if (nextch == '*') //  (Ƕ�� /*)
		{
			fputc(' ', g_state.outputfile);
			fputc(' ', g_state.outputfile);
		}
		else
		{
			fputc(ch, g_state.outputfile);
		}
		break;

	case '*':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/') //  Ƕ��//
		{
			fputc(' ', g_state.outputfile);
			fputc(' ', g_state.outputfile);
		}
		else
		{
			fputc(ch, g_state.outputfile);
		}
		break;
	case'"':
		g_state.ulstate = STR_STATE;
	default:
		fputc(ch, g_state.outputfile);
		break;
	}
}


void EventProAtStr(char ch)
{
	char nextch;
	switch (ch)
	{
	case '\0':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '"')		//��ȡ�� \0 �� " ˵���ַ������� 
			g_state.ulstate = NO_COMMENT_STATE; //״̬�л�
		break;
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	default:
		fputc(ch, g_state.outputfile);
		break;
	}
}