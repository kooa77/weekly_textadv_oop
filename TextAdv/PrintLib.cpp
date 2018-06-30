#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintLib.h"

void sString::InitString(sString* string, const char* text, eStringType type)
{
	string->_type = type;
	strcpy_s(string->_text, text);
}
void sString::InitString(sString* string, const char* text, eStringType type, int selectY, int selectN)
{
	InitString(string, text, type);
	string->_selectY = selectY;
	string->_selectN = selectN;
}

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다르다.
	if (NULL == paragraph->current)
	{
		// 첫 문장 (paragraph->current : 첫 문장)
		paragraph->current = string;	// 현재 문장 세팅
		string->_prev = NULL;
		string->_next = NULL;
		paragraph->start = string;
	}
	else
	{
		// 첫 문장 아님
		paragraph->current->_next = string;
		string->_prev = paragraph->current;
		string->_next = NULL;
		paragraph->current = string;
	}
}

int PrintParagraph(sParagraph* paragraph)
{
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
		switch (paragraph->current->_type)
		{
		case TEXT:
			PrintText(paragraph->current->_text);
			break;
		case BRANCH:
			PrintText(paragraph->current->_text);
			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return paragraph->current->_selectY;
				}
				else if ('n' == ch || 'N' == ch)
				{
					return paragraph->current->_selectN;
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// 종료
				}
			}
			break;
		case QUIT:
			PrintText(paragraph->current->_text);
			return -1;	// 종료
		}

		paragraph->current = paragraph->current->_next;
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
