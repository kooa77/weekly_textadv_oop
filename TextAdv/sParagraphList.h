#pragma once

class sString;
class sParagraph;	// ���漱��

class sParagraphList
{
private:
	int _count;
	sParagraph* _list;

public:
	void Create(int count);
	void Destroy();

	void AddStringToList(int pNo, sString* newString);
	int Print(int select);
};
