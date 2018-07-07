#pragma once

class sString;

class sParagraph
{
public:
	sParagraph();
	~sParagraph();

private:
	sString* _start;		// ���� ����
	sString* _current;	// ���� ����ؾ� �� ����

public:
	void AddString(sString* string);
	int Print();
};

struct sParagraphList
{
	int count;
	sParagraph* list;
};

//void AddStringToParagraph(sParagraph* paragraph, sString* text);

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph);

//int PrintParagraph(sParagraph* paragraph);