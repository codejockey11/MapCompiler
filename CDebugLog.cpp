#include "CDebugLog.h"

CDebugLog::CDebugLog()
{
	memset((void*)m_text, 0x00, MAX_STRING);

	errno_t err = fopen_s(&m_file, "debugLog.txt", "wb");
}

CDebugLog::~CDebugLog()
{
	fclose(m_file);
}

void CDebugLog::Write(const char* format, ...)
{
	if (strlen(format) == 0)
	{
		return;
	}

	memset((void*)m_text, 0x00, MAX_STRING);

	va_list argptr;

	va_start(argptr, format);

	vsprintf_s(m_text, MAX_STRING, format, argptr);

	va_end(argptr);

	fwrite(m_text, strlen(m_text), 1, m_file);
}