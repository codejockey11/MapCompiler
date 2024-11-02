#pragma once

#include "framework.h"

#include "CLine3D.h"
#include "../GameCommon/CVec3f.h"

class CPlane
{
public:

	CVec3f	m_normal;
	CVec3f	m_origin;
	
	float	m_dist;

	CPlane();
	~CPlane();

	void Copy(CPlane* p);

	CLine3D PlanePlaneIntersection(CPlane plane);
	CLine3D PlanePlaneIntersection2(CPlane plane);
};

