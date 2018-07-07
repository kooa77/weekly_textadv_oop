#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "sString.h"
#include "PrintLib.h"

sParagraph::sParagraph()
{
	_current = NULL;
}

sParagraph::~sParagraph()
{
	_current = _start;
	while (NULL != _current)
	{
		sString* nextStirng = _current->GetNext();
		delete _current;
		_current = nextStirng;
	}
}

void sParagraph::AddString(sString* string)
{
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다르다.
	if (NULL == _current)
	{
		// 첫 문장 (paragraph->current : 첫 문장)
		_current = string;	// 현재 문장 세팅
		string->InitNode(NULL, NULL);
		_start = string;
	}
	else
	{
		// 첫 문장 아님
		_current->SetNext(string);
		
		string->InitNode(_current, NULL);
		_current = string;
	}
}

int sParagraph::Print()
{
	// 현재 출력할 문장을 첫 문장으로 세팅
	// (첫 문장 부터 출력)
	_current = _start;
	while(NULL != _current)
	{
		switch (_current->GetType())
		{
		case TEXT:
			_current->Print();
			break;
		case BRANCH:
			_current->Print();
			while (true)
			{
				char ch = _getche();
				if ('y' == ch || 'Y' == ch)
				{
					return _current->GetSelectY();
				}
				else if ('n' == ch || 'N' == ch)
				{
					return _current->GetSelectN();
				}
				else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
				{
					return -1;	// 종료
				}
			}
			break;
		case QUIT:
			_current->Print();
			return -1;	// 종료
		}
		_current = _current->GetNext();
	}

	return 0;
}

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph)
{
	paragraphList->list[paragraphList->count] = *paragraph;
	paragraphList->count++;
}
