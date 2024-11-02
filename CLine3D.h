#pragma once

#include "framework.h"

#include "../GameCommon/CVec3f.h"

class CLine3D
{
public:

    CVec3f m_P0;
    CVec3f m_D;

    int m_plane;

    CLine3D();
    CLine3D(CVec3f P0, CVec3f D);

    float DistToPoint(CVec3f V);
    float Dist(CLine3D L1, CLine3D L2);
    float DistSq(CLine3D L1, CLine3D L2);
};