#pragma once

#include "framework.h"

#include "../GameCommon/CVec3f.h"

class CCollision
{
public:

	float m_distance;
	
	float m_u;
	float m_v;

	CCollision();
	~CCollision();

	bool IntersectPlane(CVec3f* planeNormal, CVec3f* planeOrigin, CVec3f* rayOrigin, CVec3f* rayDirection);
	bool RayTriangleIntersect(CVec3f* P, CVec3f* A, CVec3f* B, CVec3f* C);
};