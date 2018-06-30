#pragma once

enum eStringType
{
	TEXT,		// 0
	BRANCH,		// 1
	QUIT,		// 2
};

struct sString
{
	eStringType _type;
	char _text[256];
	int _selectY;
	int _selectN;

	sString* _prev;	// 이전 문장
	sString* _next;	// 다음 문장

	void Init(sString* string, const char* text, eStringType type);
	void Init(sString* string, const char* text, eStringType type, int selectY, int selectN);
};

struct sParagraph
{
	sString* start;		// 시작 문장
	sString* current;	// 현재 출력해야 할 문장
};

struct sParagraphList
{
	int count;
	struct sParagraph* list;
};

void AddStringToParagraph(sParagraph* paragraph, sString* text);

void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph);

void PrintText(sString* string);
int PrintParagraph(sParagraph* paragraph);