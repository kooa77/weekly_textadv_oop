#pragma once

class sString;

// sParagraph 캡슐화
struct sParagraph
{
	sString* _start;		// 시작 문장
	sString* _current;	// 현재 출력해야 할 문장

	void AddString(sString* string);
	int Print();
};

struct sParagraphList
{
	int count;
	struct sParagraph* list;
};

//void AddStringToParagraph(sParagraph* paragraph, sString* text);

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph);

//int PrintParagraph(sParagraph* paragraph);