#pragma once

class sString;

class sParagraph
{
public:
	sParagraph();
	~sParagraph();

private:
	sString* _start;		// 시작 문장
	sString* _current;	// 현재 출력해야 할 문장

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