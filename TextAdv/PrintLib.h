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

class sParagraphList
{
private:
	int _count;
	sParagraph* _list;

public:
	void Create(int count);
	void AddStringToList(int pNo, sString* newString);
	int Print(int select);
};

//void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph);
