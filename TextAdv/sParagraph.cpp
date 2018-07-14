#include <stdio.h>
#include <conio.h>
#include "sString.h"
#include "sParagraph.h"

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

int sParagraph::Process()
{
	int nextSelect = 0;

	// ���� ����� ������ ù �������� ����
	// (ù ���� ���� ���)
	_current = _start;
	while (NULL != _current)
	{
		nextSelect = _current->Process();
		_current = _current->GetNext();
	}

	return nextSelect;
}
