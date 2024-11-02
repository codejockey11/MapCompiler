#pragma once

#include "framework.h"

class CShaderMaterial
{
public:

	int m_number;

	char m_name[MAX_STRING];

	int m_x;
	int m_y;
	
	char m_map_Ka[MAX_STRING];
	char m_map_Kb[MAX_STRING];
	char m_map_Kd[MAX_STRING];
	char m_map_Ks[MAX_STRING];
	char m_map_Ns[MAX_STRING];
	char m_map_d[MAX_STRING];
	
	char m_refl[MAX_STRING];
	
	UINT m_illum;
	
	XMFLOAT3 m_ambient;
	XMFLOAT3 m_diffuse;
	XMFLOAT3 m_emissive;
	XMFLOAT3 m_specular;
	
	float m_opacity;
	float m_opticalDensity;
	float m_specularExponent;

	CShaderMaterial();
	~CShaderMaterial();

	void SetNumber(int i) { m_number = i; }
	void SetName(char* s) { strcpy_s(m_name, MAX_STRING, s); }
	void SetKa(char* s) { strcpy_s(m_map_Ka, MAX_STRING, s); }
	void SetKb(char* s) { strcpy_s(m_map_Kb, MAX_STRING, s); }
	void SetKd(char* s) { strcpy_s(m_map_Kd, MAX_STRING, s); }
	void SetKs(char* s) { strcpy_s(m_map_Ks, MAX_STRING, s); }
	void SetNs(char* s) { strcpy_s(m_map_Ns, MAX_STRING, s); }
	void Setd(char* s) { strcpy_s(m_map_d, MAX_STRING, s); }
	void SetRefl(char* s) { strcpy_s(m_refl, MAX_STRING, s); }
	void SetIllum(int i) { m_illum = i; }
	void SetAmbient(float r, float g, float b) { m_ambient.x = r; m_ambient.y = g; m_ambient.z = b; }
	void SetDiffuse(float r, float g, float b) { m_ambient.x = r; m_ambient.y = g; m_ambient.z = b; }
	void SetEmissive(float r, float g, float b) { m_ambient.x = r; m_ambient.y = g; m_ambient.z = b; }
	void SetSpecular(float r, float g, float b) { m_ambient.x = r; m_ambient.y = g; m_ambient.z = b; }
	void SetOpacity(float i) { m_opacity = i; }
	void SetOpticalDensity(float i) { m_opticalDensity = i; }
	void SetSpecularExponent(float i) { m_specularExponent = i; }
	void SetXRepeat(int i) { m_x = i; }
	void SetYRepeat(int i) { m_y = i; }
};