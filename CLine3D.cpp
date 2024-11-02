#include "CLine3D.h"

CLine3D::CLine3D()
{
    memset(this, 0x00, sizeof(CLine3D));
}

CLine3D::CLine3D(CVec3f P0, CVec3f D)
{
    memset(this, 0x00, sizeof(CLine3D));

    m_P0 = P0;
    m_D = D;
}

float CLine3D::Dist(CLine3D L1, CLine3D L2)
{
    //CVec3f Cross = CVec3f::Cross(L1.D, L2.D);
    CVec3f Cross = L1.m_D.Cross(L2.m_D);

    //return Math::Abs(CVec3f::Dot(L2.P0 - L1.P0, Cross)) / Cross.Length();
    return (float)fabsf((L2.m_P0 - L1.m_P0).Dot(Cross) / Cross.Length());
}

float CLine3D::DistSq(CLine3D L1, CLine3D L2)
{
    //CVec3f Cross = CVec3f::Cross(L1.D, L2.D);
    CVec3f Cross = L1.m_D.Cross(L2.m_D);

    //float Dot = CVec3f::Dot(L2.P0 - L1.P0, Cross);
    CVec3f l = L2.m_P0 - L1.m_P0;

    float Dot = l.Dot(Cross);

    return (Dot * Dot) / Cross.LengthSq();
}

float CLine3D::DistToPoint(CVec3f P)
{
    //float t0 = Dot(D, P - P0) / Vec3f::Dot(D, D);
    float t0 = m_D.Dot(P - m_P0) / m_D.Dot(m_D);
    
    //float distanceLine = Vec3f::Dist(P, P0 + t0 * D);
    CVec3f d = m_P0 + (m_D * t0);
    float distanceLine = P.Dist(d);
    
    return distanceLine;
}