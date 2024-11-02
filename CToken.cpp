#include "CToken.h"

CToken::CToken()
{
	memset(this, 0x00, sizeof(CToken));
}

CToken::~CToken()
{

}

bool CToken::CheckEndOfBuffer()
{
	if (m_buffer >= m_endOfBuffer)
	{
		return true;
	}

	return false;
}

bool CToken::CurrentToken(const char* token)
{
	char* buffer = m_buffer;

	int i = 0;

	while (i < strlen(token))
	{
		if (buffer[i] != token[i])
		{
			return false;
		}

		i++;
	}

	return true;
}

char* CToken::GetToken()
{
	m_tokenFound = false;
	m_tokenCount = 0;

	memset(m_token, 0x00, CToken::MAX_TOKEN);

	while (true)
	{
		if (CToken::CheckEndOfBuffer())
		{
			break;
		}

		if ((m_buffer[0] > ' ') && (m_buffer[0] < 127))
		{
			if (m_tokenCount == CToken::MAX_TOKEN)
			{
				printf_s("Token %s exceeded max token size\r\n", m_token);

				m_token[CToken::MAX_TOKEN - 1] = 0x00;

				break;
			}

			m_token[m_tokenCount] = m_buffer[0];

			m_tokenCount++;

			m_tokenFound = true;
		}
		else
		{
			if (m_tokenFound)
			{
				break;
			}
		}

		m_buffer++;
	}

	return m_token;
}

void CToken::InitBuffer(char* filename)
{
	errno_t err = fopen_s(&m_file, filename, "rb");

	if (err != 0)
	{
		printf("Material Not found\r\n");

		return;
	}

	int pos = ftell(m_file);
	fseek(m_file, 0, SEEK_END);
	int filesize = ftell(m_file);
	fseek(m_file, pos, SEEK_SET);

	if (m_buffer)
	{
		free(m_buffer);
	}

	m_buffer = (char*)malloc(filesize);

	if (m_buffer)
	{
		size_t rl = fread_s(m_buffer, filesize, 1, filesize, m_file);

		fclose(m_file);
	}

	m_startOfBuffer = m_buffer;

	m_bufferLength = filesize;

	m_endOfBuffer = m_buffer + m_bufferLength;
}

void CToken::Move(int i)
{
	m_buffer += i;
}

void CToken::MoveToToken(const char* token)
{
	while (true)
	{
		if (CToken::CheckEndOfBuffer())
		{
			break;
		}

		int r = strncmp(&m_buffer[0], token, strlen(token));
		
		if (r == 0)
		{
			break;
		}

		m_buffer++;
	}
}

void CToken::SkipEndOfLine()
{
	if (CToken::CheckEndOfBuffer())
	{
		return;
	}

	while (m_buffer[0] != '\r' && m_buffer[0] != '\n')
	{
		m_buffer++;
	}

	m_buffer++;

	if (m_buffer[0] == '\r' || m_buffer[0] == '\n')
	{
		m_buffer++;
	}
}

void CToken::SkipTabs()
{
	while (m_buffer[0] == '\t')
	{
		m_buffer++;
	}
}