#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sParagraphList.h"
#include "sString.h"
#include "sStringText.h"
#include "sStringBranch.h"
#include "sStringQuit.h"
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

		char* token = strtok(record, ",");	// 문단 번호
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
	// 스크립트 사용
	// 1. 파일은 연다. - 파일에 있는 내용을 읽을 준비를 한다.
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

	// 2. 파싱 - 파일에 있는 내용을 읽는다
	// 첫줄 읽었고. - 필요 없으므로 스킵
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

		// 3. 게임 데이터를 구성한다

		char* token = strtok(record, ",");	// 문단 번호
		int pNo = atoi(token);

		token = strtok(NULL, ",");	// 타입
		eStringType type = (eStringType)atoi(token);

		token = strtok(NULL, ",");	// 내용
		char* text = token;

		token = strtok(NULL, ",");	// Y
		int selectY = atoi(token);

		token = strtok(NULL, ",");	// N
		int selectN = atoi(token);

		if (pNo != prevNo)
		{
			// 문단이 바꼈다.
			prevNo = pNo;
		}
		
		sString* newString = NULL;
		switch (type)
		{
		case eStringType::TEXT:
			newString = new sStringText();
			break;
		case eStringType::BRANCH:
			newString = new sStringBranch();
			break;
		case eStringType::QUIT:
			newString = new sStringQuit();
			break;
		}
		newString->Init(text, type, selectY, selectN);
		paragraphList->AddStringToList(pNo, newString);
	}

	// 4. 파일을 닫는다. - 파일을 다시 읽을 수 없는 상태로 만든다
	fclose(fp);
}
