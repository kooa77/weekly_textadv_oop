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
