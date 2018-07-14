#include <conio.h>
#include "sStringBranch.h"

sStringBranch::sStringBranch()
{
}

sStringBranch::~sStringBranch()
{
}

int sStringBranch::Process()
{
	Print();

	int select = -1;
	while (true)
	{
		char ch = _getche();
		if ('y' == ch || 'Y' == ch)
		{
			select = GetSelectY();
			break;
		}
		else if ('n' == ch || 'N' == ch)
		{
			select = GetSelectN();
			break;
		}
		else if ('q' == ch || 'Q' == ch || 27 == ch)	// 27 : ESC
		{
			select = -1;
			break;
		}
	}
	return select;
}