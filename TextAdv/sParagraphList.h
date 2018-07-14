#pragma once

class sString;
class sParagraph;	// 전방선언

class sParagraphList
{
private:
	int _count;
	sParagraph* _list;

public:
	void Create(int count);
	void Destroy();

	void AddStringToList(int pNo, sString* newString);
	int Process(int select);
};
