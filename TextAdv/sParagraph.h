#pragma once

class sString;

class sParagraph
{
public:
	sParagraph();
	~sParagraph();

private:
	sString * _start;		// ���� ����
	sString* _current;	// ���� ����ؾ� �� ����

public:
	void AddString(sString* string);
	int Process();
};