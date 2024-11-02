#pragma once

#include "framework.h"

class CDebugLog
{
public:

	FILE* m_file;

	char m_text[MAX_STRING];

	CDebugLog();
	~CDebugLog();

	void Write(const char* format, ...);
};