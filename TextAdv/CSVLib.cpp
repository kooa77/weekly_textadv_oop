#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PrintLib.h"
#include "sString.h"
#include "CSVLib.h"

int CalcParagraphCount(FILE* fp)
{
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);

	int prevNo = -1;
	int count = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);
		if (pNo != prevNo)
		{
			prevNo = pNo;
			count++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	return count;
}
void ParsingCSV(const char* fileName, sParagraphList* paragraphList)
{
	// ��ũ��Ʈ ���
	// 1. ������ ����. - ���Ͽ� �ִ� ������ ���� �غ� �Ѵ�.
	FILE* fp = fopen(fileName, "r");	// r-read, w-write
	if (NULL == fp)
	{
		printf("\nError : File can't open");
		return;
	}

	int count = CalcParagraphCount(fp);
	paragraphList->Create(count);
	//paragraphList->_count = CalcParagraphCount(fp);
	//paragraphList->_list = new sParagraph[paragraphList->_count];

	// 2. �Ľ� - ���Ͽ� �ִ� ������ �д´�
	// ù�� �о���. - �ʿ� �����Ƿ� ��ŵ
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	printf("%s\n", record);

	int prevNo = -1;
	//paragraphList->count = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		printf("%s\n", record);

		// 3. ���� �����͸� �����Ѵ�

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);

		token = strtok(NULL, ",");	// Ÿ��
		eStringType type = (eStringType)atoi(token);

		token = strtok(NULL, ",");	// ����
		char* text = token;

		token = strtok(NULL, ",");	// Y
		int selectY = atoi(token);

		token = strtok(NULL, ",");	// N
		int selectN = atoi(token);

		if (pNo != prevNo)
		{
			// ������ �ٲ���.
			prevNo = pNo;
		}
		
		sString* newString = new sString(text, type, selectY, selectN);
		//paragraphList->_list[pNo].AddString(newString);
		paragraphList->AddStringToList(pNo, newString);
	}

	// 4. ������ �ݴ´�. - ������ �ٽ� ���� �� ���� ���·� �����
	fclose(fp);
}