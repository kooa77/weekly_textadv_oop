#include <stdio.h>
#include <string.h>

#include "sString.h"

sString::sString()
{
	_prev = NULL;
	_next = NULL;
}

sString::sString(const char* text, eStringType type, int selectY, int selectN)
{
	_prev = NULL;
	_next = NULL;
	Init(text, type, selectY, selectN);
}

sString::~sString()
{
}

void sString::Init(const char* text, eStringType type)
{
	_type = type;
	strcpy_s(_text, text);
}

void sString::Init(const char* text, eStringType type, int selectY, int selectN)
{
	Init(text, type);
	_selectY = selectY;
	_selectN = selectN;
}

int sString::Process()
{
	return -1;
}

void sString::Print()
{
	printf(_text);
	printf("\n");
}
