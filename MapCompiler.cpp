#include "framework.h"

#include "CDebugLog.h"
#include "CShaderMaterial.h"
#include "../GameCommon/CString.h"
#include "CToken.h"
#include "../GameCommon/CVec3f.h"

CDebugLog m_debugLog;

char m_filename[MAX_STRING];
char* m_materialFilename;

CToken m_objectScript;
CToken m_materialScript;

CShaderMaterial m_material[MAX_SHADER];

int m_materialCount = 0;

CVec3f m_vertex[MAX_VERTEX];
CVec3f m_normal[MAX_NORMAL];

float m_u[MAX_UV];
float m_v[MAX_UV];

int m_vertexCount = 1;
int m_normalCount = 1;
int m_uvCount = 1;

void ProcessMaterialScript()
{
	while (true)
	{
		if (m_materialScript.CheckEndOfBuffer())
		{
			break;
		}

		m_materialScript.MoveToToken("newmtl");

		while (strncmp(m_materialScript.m_buffer, "newmtl ", 7) == 0)
		{
			m_materialScript.Move(7);

			char* material = m_materialScript.GetToken();

			if (strncmp(material, "caulk", 5) == 0)
			{
				break;
			}

			m_material[m_materialCount].SetNumber(m_materialCount);

			m_material[m_materialCount].SetName(material);

			m_materialScript.SkipEndOfLine();

			if (strncmp(m_materialScript.m_buffer, "Ns ", 3) == 0)
			{
				m_materialScript.Move(3);

				char* token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "Ka ", 3) == 0)
			{
				m_materialScript.Move(3);

				char* token = m_materialScript.GetToken();
				token = m_materialScript.GetToken();
				token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "Ks ", 3) == 0)
			{
				m_materialScript.Move(3);

				char* token = m_materialScript.GetToken();
				token = m_materialScript.GetToken();
				token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "Ke ", 3) == 0)
			{
				m_materialScript.Move(3);

				char* token = m_materialScript.GetToken();
				token = m_materialScript.GetToken();
				token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "Ni ", 3) == 0)
			{
				m_materialScript.Move(3);

				char* token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "d ", 2) == 0)
			{
				m_materialScript.Move(2);

				char* token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "illum ", 6) == 0)
			{
				m_materialScript.Move(6);

				char* token = m_materialScript.GetToken();

				m_materialScript.SkipEndOfLine();
			}

			if (strncmp(m_materialScript.m_buffer, "map_Kd ", 7) == 0)
			{
				m_materialScript.Move(7);

				if (strncmp(m_materialScript.m_buffer, "-s ", 3) == 0)
				{
					m_materialScript.Move(3);

					char* token = m_materialScript.GetToken();

					m_material[m_materialCount].SetXRepeat(atoi(token));

					token = m_materialScript.GetToken();

					m_material[m_materialCount].SetYRepeat(atoi(token));
				}

				m_materialScript.MoveToToken("C:/");

				char* token = m_materialScript.GetToken();

				m_material[m_materialCount].SetKd(token);

				m_materialScript.SkipEndOfLine();

				m_materialCount++;

				break;
			}
		}
	}
}

void ProcessObjectScript()
{
	while (true)
	{
		if (m_objectScript.CheckEndOfBuffer())
		{
			break;
		}

		m_objectScript.MoveToToken("v");

		while (strncmp(m_objectScript.m_buffer, "v ", 2) == 0)
		{
			m_objectScript.Move(2);

			m_vertex[m_vertexCount].p.x = (float)atof(m_objectScript.GetToken());
			m_vertex[m_vertexCount].p.y = (float)atof(m_objectScript.GetToken());
			m_vertex[m_vertexCount].p.z = (float)atof(m_objectScript.GetToken());

			m_vertexCount++;

			m_objectScript.SkipEndOfLine();
		}

		m_objectScript.MoveToToken("vn");

		while (strncmp(m_objectScript.m_buffer, "vn ", 3) == 0)
		{
			m_objectScript.Move(3);

			m_normal[m_normalCount].p.x = (float)atof(m_objectScript.GetToken());
			m_normal[m_normalCount].p.y = (float)atof(m_objectScript.GetToken());
			m_normal[m_normalCount].p.z = (float)atof(m_objectScript.GetToken());

			m_normalCount++;

			m_objectScript.SkipEndOfLine();
		}

		m_objectScript.MoveToToken("vt");

		while (strncmp(m_objectScript.m_buffer, "vt ", 3) == 0)
		{
			m_objectScript.Move(3);

			m_u[m_uvCount] = (float)atof(m_objectScript.GetToken());
			m_v[m_uvCount] = (float)atof(m_objectScript.GetToken());

			m_uvCount++;

			m_objectScript.SkipEndOfLine();
		}

		m_objectScript.MoveToToken("usemtl");

		while (strncmp(m_objectScript.m_buffer, "usemtl ", 7) == 0)
		{
			m_objectScript.Move(7);

			char* material = m_objectScript.GetToken();

			if (strncmp(material, "caulk", 5) == 0)
			{
				break;
			}

			CShaderMaterial* mat = &m_material[0];

			for (int m = 0; m < m_materialCount; m++)
			{
				if (strncmp(material, m_material[m].m_name, strlen(m_material[m].m_name)) == 0)
				{
					mat = &m_material[m];

					break;
				}
			}

			m_objectScript.MoveToToken("f");

			while (strncmp(m_objectScript.m_buffer, "f ", 2) == 0)
			{
				m_objectScript.Move(2);

				int vertex[3] = {};
				int normal[3] = {};
				int uv[3] = {};

				sscanf_s(m_objectScript.m_buffer, "%i/%i/%i %i/%i/%i %i/%i/%i\n", &vertex[0], &uv[0], &normal[0], &vertex[1], &uv[1], &normal[1], &vertex[2], &uv[2], &normal[2]);


				for (int p = 0; p < 3; p++)
				{
					m_debugLog.Write("%i %+012.7f %+012.7f %+012.7f %+012.7f %+012.7f %+012.7f %+012.7f %+012.7f\r\n",
						mat->m_number,
						m_vertex[vertex[p]].p.x, m_vertex[vertex[p]].p.y, m_vertex[vertex[p]].p.z,
						m_normal[normal[p]].p.x, m_normal[normal[p]].p.y, m_normal[normal[p]].p.z,
						m_u[uv[p]] * mat->m_x,
						m_v[uv[p]] * mat->m_y
					);
				}

				m_objectScript.SkipEndOfLine();
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		m_debugLog.Write("Specify an environment name\r\n");

		return 0;
	}

	memset(m_filename, 0x00, MAX_STRING);
	memcpy(m_filename, argv[1], strlen(argv[1]));

	m_objectScript.InitBuffer(m_filename);

	m_objectScript.MoveToToken("mtllib");
	m_objectScript.Move(6);

	m_materialFilename = m_objectScript.GetToken();

	m_materialScript.InitBuffer(m_materialFilename);

	ProcessMaterialScript();

	for (int m = 0; m < m_materialCount; m++)
	{
		m_debugLog.Write("%i %s %s\r\n",
			m_material[m].m_number,
			m_material[m].m_name,
			m_material[m].m_map_Kd
		);
	}

	ProcessObjectScript();

	return 1;
}