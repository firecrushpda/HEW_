#pragma once
#include "main.h"

D3DXVECTOR3* GetThreePowerBeizerList(D3DXVECTOR3 startPoint, D3DXVECTOR3 controlPoint1, D3DXVECTOR3 controlPoint2, D3DXVECTOR3 endPoint, int segmentNum);
D3DXVECTOR3 CalculateThreePowerBezierPoint(float t, D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3);