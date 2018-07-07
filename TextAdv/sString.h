#pragma once


enum eStringType
{
	TEXT,		// 0
	BRANCH,		// 1
	QUIT,		// 2
};

class sString
{
public:
	sString();	// 생성자
	~sString();	// 해제자

private:
	eStringType _type;
	char _text[256];
	int _selectY;
	int _selectN;

	sString* _prev;	// 이전 문장
	sString* _next;	// 다음 문장

public:
	void Init(const char* text, eStringType type);
	void Init(const char* text, eStringType type, int selectY, int selectN);
	void Print();

	// getter/setter
	eStringType GetType() { return _type; }

	int GetSelectY() { return _selectY; }
	int GetSelectN() { return _selectN; }

	void InitNode(sString* prev, sString* next)
	{
		_prev = prev;
		_next = next;
	}
	
	void SetNext(sString* next) { _next = next; }
	sString* GetNext() { return _next; }
};