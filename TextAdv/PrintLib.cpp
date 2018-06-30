#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "sString.h"
#include "PrintLib.h"

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다르다.
	if (NULL == paragraph->current)
	{
		// 첫 문장 (paragraph->current : 첫 문장)
		paragraph->current = string;	// 현재 문장 세팅
		//string->_prev = NULL;
		//string->_next = NULL;
		string->InitNode(NULL, NULL);
		paragraph->start = string;
	}
	else
	{
		// 첫 문장 아님
		//paragraph->current->_next = string;
		paragraph->current->SetNext(string);
		
		//string->_prev = paragraph->current;
		//string->_next = NULL;
		string->InitNode(paragraph->current, NULL);
		paragraph->current = string;
	}
}

int PrintParagraph(sParagraph* paragraph)
{
	// 현재 출력할 문장을 첫 문장으로 세팅
	// (첫 문장 부터 출력)
	paragraph->current = paragraph->start;
	while(NULL != paragraph->current)
	{
		switch (paragraph->current->GetType())
		{
		case TEXT:
			paragraph->current->Print();
			break;
		case BRANCH:
			paragraph->current->Print();
			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return paragraph->current->GetSelectY();
				}
				else if ('n' == ch || 'N' == ch)
				{
					return paragraph->current->GetSelectN();
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// 종료
				}
			}
			break;
		case QUIT:
			paragraph->current->Print();
			return -1;	// 종료
		}

		//paragraph->current = paragraph->current->_next;
		paragraph->current = paragraph->current->GetNext();
	}

	return 0;
}

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph)
{
	paragraphList->list[paragraphList->count] = *paragraph;
	paragraphList->count++;
}
