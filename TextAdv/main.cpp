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

	// select ���� ���Ͽ� ��� �ϴ� �κ�
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

	// ����� select ���� �о�´�.
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

	int select = 0;	// ���� select�� 0�� ����

	// [�䱸����]
	// �ε带 �Ͻðڽ��ϱ�? Y or N
	// Y - �ε�
	// N - ó������
	
	// ���� ���
	printf("�ε带 �Ͻðڽ��ϱ�? Y or N\n");
	char ch = _getche();	// ������ �Է��� �޴´�.
	if ('y' == ch || 'Y' == ch)
	{
		select = Load();
	}	

	// || : or, �Ǵ�, �̰ų�~�̸�
	// && : and, �׸���, ~��~�̸�
	// == : equal, ������
	// <, >, <=, >=

	while(true)
	{
		int nextSelect = 0;
		if(select < paragraphList.count)
		{
			printf("\n");
			//nextSelect = PrintParagraph(&paragraphList.list[select]);
			nextSelect = paragraphList.list[select].Print();
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

	/*
	for (int i = 0; i < paragraphList.count; i++)
	{
		paragraphList.list[i]._current = paragraphList.list[i]._start;
		while (NULL != paragraphList.list[i]._current)
		{
			sString* nextStirng = paragraphList.list[i]._current->GetNext();
			delete paragraphList.list[i]._current;
			paragraphList.list[i]._current = nextStirng;
		}
	}
	free(paragraphList.list);
	*/
	delete[] paragraphList.list;
	
	return 0;
}
