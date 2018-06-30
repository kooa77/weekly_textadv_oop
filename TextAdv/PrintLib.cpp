#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintLib.h"

void InitString(sString* string, const char* text, eStringType type)
{
	string->type = type;
	strcpy_s(string->text, text);
}
void InitString(sString* string, const char* text, eStringType type, int selectY, int selectN)
{
	InitString(string, text, type);
	string->selectY = selectY;
	string->selectN = selectN;
}

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	/*
	paragraph->stringList[paragraph->count] = *text;
	paragraph->count++;	// 1씩 증가
	*/
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다르다.
	if (NULL == paragraph->current)
	{
		// 첫 문장 (paragraph->current : 첫 문장)
		paragraph->current = string;	// 현재 문장 세팅
		string->prev = NULL;
		string->next = NULL;
		paragraph->start = string;
	}
	else
	{
		// 첫 문장 아님
		// current 에는 "첫 문장" 이라는 내용 세팅
		// string 에는 "두번 째 문장" 이라는 내용 세팅
		paragraph->current->next = string;
		string->prev = paragraph->current;
		string->next = NULL;
		paragraph->current = string;
	}
}

int PrintParagraph(sParagraph* paragraph)
{
	/*
	for (int i = 0; i < paragraph->count; i++)
	{
		switch (paragraph->stringList[i].type)
		{
		case TEXT:	// case 0:
			PrintText(paragraph->stringList[i].text);
			break;
		case BRANCH:	// case 1:
			PrintText(paragraph->stringList[i].text);
			// 요구사항
			// 유저가 선택하기 전까지는 머물러 있이어 한다.
			// 유저가 y or n 을 선택하면 진행.
			// 유저의 선택에 따라 다음 진행할 내용의 인덱스가 결정
			while (true)
			{
				// || : or, 또는
				// && : and, 그리고
				// == : equal, 같으면
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return paragraph->stringList[i].selectY;
				}
				else if ('n' == ch || 'N' == ch)
				{
					return paragraph->stringList[i].selectN;
				}
				else if ('q' ==ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// 종료
				}
			}
			break;
		case QUIT:	// case 2:
			PrintText(paragraph->stringList[i].text);
			return -1;	// 종료
		}
	}
	*/

	// 현재 출력할 문장을 첫 문장으로 세팅
	// (첫 문장 부터 출력)
	paragraph->current = paragraph->start;
	// 현재 문장이 존재하는 한 반복 (NULL 이면 없음)
	// != : 아니면
	// 문장의 갯수는 모르는 상태에서 반복을 진행한다.
	while(NULL != paragraph->current)
	{
		// stringList[i] : i 번째 있는 문장
		// current : 현재 문장
		// stringList[i].  ==>  current->
		switch (paragraph->current->type)
		{
		case TEXT:
			PrintText(paragraph->current->text);
			break;
		case BRANCH:
			PrintText(paragraph->current->text);
			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return paragraph->current->selectY;
				}
				else if ('n' == ch || 'N' == ch)
				{
					return paragraph->current->selectN;
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// 종료
				}
			}
			break;
		case QUIT:
			PrintText(paragraph->current->text);
			return -1;	// 종료
		}

		paragraph->current = paragraph->current->next;
	}

	return 0;
}

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph)
{
	paragraphList->list[paragraphList->count] = *paragraph;
	paragraphList->count++;
}

void PrintText(const char* text)
{
	printf(text);
	printf("\n");
}
