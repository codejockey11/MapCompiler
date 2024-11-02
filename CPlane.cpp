#include "CPlane.h"

CPlane::CPlane()
{
	memset(this, 0x00, sizeof(CPlane));
}

CPlane::~CPlane()
{

}

void CPlane::Copy(CPlane* p)
{
	memcpy((void*)this, (void*)p, sizeof(CPlane));
}

CLine3D CPlane::PlanePlaneIntersection(CPlane plane)
{
	CLine3D line;

    //float Denominator = P1.a * P2.b - P1.b * P2.a;
    float denominator = m_normal.p.x * plane.m_normal.p.y - m_normal.p.y * plane.m_normal.p.x;
    if (denominator == 0.0f)
    {
        // this case should be handled by switching axes...
        return line;
    }
    //L.P0 = Vec3f((P2.d * P1.b - P1.d * P2.b) / Denominator, (P1.d * P2.a - P2.d * P1.a) / Denominator, 0.0f);
    CVec3f P0 = CVec3f((plane.m_dist * m_normal.p.y - m_dist * plane.m_normal.p.y) / denominator, (m_dist * plane.m_normal.p.x - plane.m_dist * m_normal.p.x) / denominator, 0.0f);

    //L.D = Vec3f::Cross(P1.Normal(), P2.Normal());
	CVec3f D = m_normal.Cross(plane.m_normal);
    //if (L.D.Length() == 0.0f)
    //{
		//return false;
    //}
    //L.D = Vec3f::Normalize(L.D);
	D.Normalize();

	line = CLine3D(P0, D);

    return line;
}

CLine3D CPlane::PlanePlaneIntersection2(CPlane plane)
{
	CLine3D line;

	// logically the 3rd plane, but we only use the normal component.
	CVec3f normal = m_normal.Cross(plane.m_normal);
	
	float det = normal.LengthSq();

	// If the determinant is 0, that means parallel planes, no intersection.
	// note: you may want to check against an epsilon value here.
	if (det != 0.0)
	{
		// calculate the final (point, normal)
		line.m_P0 =
			((normal.Cross(plane.m_normal) * m_dist) +
			(m_normal.Cross(normal) * plane.m_dist)) / det;
		
		line.m_D = normal;

		line.m_D.Normalize();
	}

	return line;
}