#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "PrintLib.h"
#include "sString.h"
#include "CSVLib.h"

void Save(int select)
{
	FILE* fp = fopen("save.dat", "w+b");
	if (NULL == fp)
	{
		printf("File Not Open!\n");
		return;
	}

	// select 값을 파일에 기록 하는 부분
	// | 1 * sizeof(int) |
	if (1 == fwrite(&select, sizeof(int), 1, fp))
	{
		printf("Success Save\n");
	}
	else
	{
		printf("Failed Save\n");
	}

	fclose(fp);
}

int Load()
{
	FILE* fp = fopen("save.dat", "rb");
	if (NULL == fp)
	{
		printf("File Not Open!\n");
		return 0;
	}

	// 저장된 select 값을 읽어온다.
	int loadSelect = 0;
	if (1 == fread(&loadSelect, sizeof(int), 1, fp))
	{
		printf("Success Load\n");
	}
	else
	{
		printf("Failed Load\n");
	}

	fclose(fp);

	return loadSelect;
}

int main(void)
{
	struct sParagraphList paragraphList;
	ParsingCSV("story.csv", &paragraphList);

	int select = 0;	// 정수 select에 0을 대입

	// [요구사항]
	// 로드를 하시겠습니까? Y or N
	// Y - 로드
	// N - 처음부터
	
	// 문구 출력
	printf("로드를 하시겠습니까? Y or N\n");
	char ch = _getche();	// 유저의 입력을 받는다.
	if ('y' == ch || 'Y' == ch)
	{
		select = Load();
	}	

	// || : or, 또는, 이거나~이면
	// && : and, 그리고, ~고~이면
	// == : equal, 같으면
	// <, >, <=, >=

	while(true)
	{
		int nextSelect = 0;
		if(select < paragraphList.count)
		{
			printf("\n");
			nextSelect = PrintParagraph(&paragraphList.list[select]);
		}
		else
		{
			break;
		}
		if (nextSelect < 0)
		{
			break;
		}			
		else
		{
			select = nextSelect;
		}
	}

	Save(select);

	for (int i = 0; i < paragraphList.count; i++)
	{
		paragraphList.list[i].current = paragraphList.list[i].start;
		while (NULL != paragraphList.list[i].current)
		{
			// 다음 문장을 기억해 놓고
			sString* nextStirng = paragraphList.list[i].current->_next;
			// 현재 문장을 지운 후
			free(paragraphList.list[i].current);
			// 현재 문장을 기억해 놓은 다음 문장으로 세팅
			paragraphList.list[i].current = nextStirng;
			// 다음 문장을 기억하지 않고 현재 문장을 지워버리면
			// 다음 문장을 알 방법이 없다.
		}
	}
	free(paragraphList.list);
	
	return 0;
}
