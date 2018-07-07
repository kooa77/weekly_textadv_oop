#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "sString.h"
#include "PrintLib.h"

void AddStringToParagraph(sParagraph* paragraph, sString* string)
{
	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ���.
	if (NULL == paragraph->current)
	{
		// ù ���� (paragraph->current : ù ����)
		paragraph->current = string;	// ���� ���� ����
		//string->_prev = NULL;
		//string->_next = NULL;
		string->InitNode(NULL, NULL);
		paragraph->start = string;
	}
	else
	{
		// ù ���� �ƴ�
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
	// ���� ����� ������ ù �������� ����
	// (ù ���� ���� ���)
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
					return -1;	// ����
				}
			}
			break;
		case QUIT:
			paragraph->current->Print();
			return -1;	// ����
		}
		paragraph->current = paragraph->current->GetNext();
	}

	return 0;
}

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph)
{
	paragraphList->list[paragraphList->count] = *paragraph;
	paragraphList->count++;
}
