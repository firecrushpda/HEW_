#include "MathUtil.h"

// <summary>
// 
// </summary>
// <param name="startPoint"></param>
// <param name="controlPoint1"></param>
// <param name="controlPoint2"></param>
// <param name="endPoint"></param>
// <param name="segmentNum"></param>
// <returns></returns>
D3DXVECTOR3* GetThreePowerBeizerList(D3DXVECTOR3 startPoint, D3DXVECTOR3 controlPoint1, D3DXVECTOR3 controlPoint2, D3DXVECTOR3 endPoint, int segmentNum)
{
	D3DXVECTOR3* path = new D3DXVECTOR3[segmentNum];
	
	for (int i = 1; i <= segmentNum; i++)
	{
		float t = i / (float)segmentNum;
		D3DXVECTOR3 pixel = CalculateThreePowerBezierPoint(t, startPoint,
			controlPoint1, controlPoint2, endPoint);
		path[i - 1] = pixel;
	}

	return path;
}

// <summary>
// 
// </summary>
// <param name="t"></param>
// <param name="p0"></param>
// <param name="p1"></param>
// <param name="p2"></param>
// <param name="p3"></param>
// <returns></returns>
D3DXVECTOR3 CalculateThreePowerBezierPoint(float t, D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3)
{
	float u = 1 - t;
	float tt = t * t;
	float uu = u * u;
	float ttt = tt * t;
	float uuu = uu * u;

	D3DXVECTOR3 p = uuu * p0;
	p += 3 * t * uu * p1;
	p += 3 * tt * u * p2;
	p += ttt * p3;

	return p;
}

// <summary>
//
// </summary>
// <param name="t"></param>
// <param name="p0"></param>
// <param name="p1"></param>
// <returns></returns>
D3DXVECTOR3 CalculateLineBezierPoint(float t, D3DXVECTOR3 p0, D3DXVECTOR3 p1)
{
	float u = 1 - t;

	D3DXVECTOR3 p = u * p0;
	p += t * p1;


	return p;
}

// <summary>
//
// </summary>
// <param name="t"></param>
// <param name="p0"></param>
// <param name="p1"></param>
// <param name="p2"></param>
// <returns></returns>
D3DXVECTOR3 CalculateCubicBezierPoint(float t, D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	float u = 1 - t;
	float tt = t * t;
	float uu = u * u;

	D3DXVECTOR3 p = uu * p0;
	p += 2 * u * t * p1;
	p += tt * p2;

	return p;
}

// <summary>
//
// </summary>
// <param name="startPoint"></param>
// <param name="controlPoint"></param>
// <param name="endPoint"></param>
// <param name="segmentNum"></param>
// <returns></returns>
D3DXVECTOR3* GetCubicBeizerList(D3DXVECTOR3 startPoint, D3DXVECTOR3 controlPoint, D3DXVECTOR3 endPoint, int segmentNum)
{
	D3DXVECTOR3* path = new D3DXVECTOR3[segmentNum];
	for (int i = 1; i <= segmentNum; i++)
	{
		float t = i / (float)segmentNum;
		D3DXVECTOR3 pixel = CalculateCubicBezierPoint(t, startPoint,
			controlPoint, endPoint);
		path[i - 1] = pixel;
	}
	return path;

}


