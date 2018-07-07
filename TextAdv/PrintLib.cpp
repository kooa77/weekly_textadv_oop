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
	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ���.
	if (NULL == _current)
	{
		// ù ���� (paragraph->current : ù ����)
		_current = string;	// ���� ���� ����
		string->InitNode(NULL, NULL);
		_start = string;
	}
	else
	{
		// ù ���� �ƴ�
		_current->SetNext(string);
		
		string->InitNode(_current, NULL);
		_current = string;
	}
}

int sParagraph::Print()
{
	// ���� ����� ������ ù �������� ����
	// (ù ���� ���� ���)
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
					return -1;	// ����
				}
			}
			break;
		case QUIT:
			_current->Print();
			return -1;	// ����
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
