#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "sParagraphList.h"
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
	sParagraphList paragraphList;
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
		int nextSelect = paragraphList.Process(select);

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

	paragraphList.Destroy();
	
	return 0;
}
