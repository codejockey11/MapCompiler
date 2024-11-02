#pragma once

#include "framework.h"

class CToken
{
public:

	enum
	{
		MAX_TOKEN = 256
	};

	FILE* m_file;

	char* m_buffer;

	char* m_startOfBuffer;
	char* m_endOfBuffer;

	int m_bufferLength;
	int m_tokenCount;

	bool m_tokenFound;

	char m_token[CToken::MAX_TOKEN];

	CToken();
	~CToken();

	bool CheckEndOfBuffer();
	bool CurrentToken(const char* token);
	char* GetToken();
	void InitBuffer(char* filename);
	void Move(int i);
	void MoveToToken(const char* token);
	void SkipEndOfLine();
	void SkipTabs();
};