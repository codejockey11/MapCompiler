#include "CShaderMaterial.h"

/*
*/
CShaderMaterial::CShaderMaterial()
{
	memset(this, 0x00, sizeof(CShaderMaterial));

	m_x = 1;
	m_y = 1;
}

/*
*/
CShaderMaterial::~CShaderMaterial()
{
}