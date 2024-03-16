#include "Math.h"
#include "Direct3D.h"
#include <cmath>
#include <numbers>

float Math::Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
	return (a.x * b.y * c.z +
		    a.z * b.x * c.y +
		    a.y * b.z * c.x -
		    a.z * b.y * c.x -
		    a.y * b.x * c.z -
		    a.x * b.z * c.y);
}

bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float& dist, XMVECTOR& hitPos)
{
	XMFLOAT3 e1 = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
	XMFLOAT3 e2 = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
	XMFLOAT3 d = XMFLOAT3(-dir.x, -dir.y, -dir.z);
	XMFLOAT3 s = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
	float e1e2d = Math::Det(e1, e2, d);
	float u = Math::Det(s, e2, d) / e1e2d;
	float v = Math::Det(e1, s, d) / e1e2d;
	float l = Math::Det(e1, e2, s) / e1e2d;

	if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && (u + v) <= 1 && l >= 0)
	{
		XMVECTOR vU = XMLoadFloat3(&e1) * u;
		XMVECTOR vV = XMLoadFloat3(&e2) * v;
		XMVECTOR vV0 = XMLoadFloat3(&v0);
		hitPos = vV0 + vU + vV;
		dist = l;
		return true;
	}
	return false;
}

//bool Math::Intersect(RayCastData& rayCast, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
//{
//	XMFLOAT3 e1 = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
//	XMFLOAT3 e2 = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
//	XMFLOAT3 d = XMFLOAT3(-rayCast.dir.x, -rayCast.dir.y, -rayCast.dir.z);
//	XMFLOAT3 s = XMFLOAT3(rayCast.start.x - v0.x, rayCast.start.y - v0.y, rayCast.start.z - v0.z);
//	float e1e2d = Math::Det(e1, e2, d);
//	float u = Math::Det(s, e2, d) / e1e2d;
//	float v = Math::Det(e1, s, d) / e1e2d;
//	float l = Math::Det(e1, e2, s) / e1e2d;
//
//	if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && (u + v) <= 1 && l >= 0)
//	{
//		XMVECTOR vU = XMLoadFloat3(&e1)*u;
//		XMVECTOR vV = XMLoadFloat3(&e2)*v;
//		XMVECTOR vV0 = XMLoadFloat3(&v0);
//		rayCast.hitPos=vV0 + vU + vV;
//		rayCast.dist = l;
//		return true;
//	}
//	return false;
//}

bool Math::IsFrontSurface(XMVECTOR vNormal, XMVECTOR vDir)
{
	XMFLOAT3 normal;
	XMFLOAT3 dir;

	XMStoreFloat3(&normal, vNormal);
	XMStoreFloat3(&dir, -vDir);
	float denominator = sqrtf(powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2)) * sqrtf(powf(dir.x, 2) + powf(dir.y, 2) + powf(dir.z, 2));
	float dot = ((normal.x * dir.x) + (normal.y * dir.y) + (normal.z * dir.z))/denominator;
	if (dot <= 1.0f && dot >= 0.0f)
	{
		return true;
	}
	return false;
}

XMFLOAT3 Math::TransformToPixel(const XMFLOAT3& transform)
{
	//position_Ç0~1Ç…ïœçX
	XMFLOAT3 pos = { (transform.x + 1) / 2, (-transform.y + 1) / 2, transform.z };

	pos = { pos.x * Direct3D::GetScreenWidth(), pos.y * Direct3D::GetScreenHeight(), pos.z};

	return pos;
}

XMFLOAT3 Math::PixelToTransform(const XMFLOAT3& pixel)
{
	XMFLOAT3 pos = { pixel.x / Direct3D::GetScreenWidth(), pixel.y / Direct3D::GetScreenHeight(), pixel.z};
	pos = { pos.x * 2 - 1, -pos.y * 2 + 1, pos.z };
	return pos;
}
XMFLOAT3 Math::PixelToTransform(const XMINT3& pixel)
{
	return PixelToTransform(XMFLOAT3{ (float)pixel.x, (float)pixel.y, (float)pixel.z });
}

float Math::Wavelet(float Incli, float Coord)
{
	//-1Ç©ÇÁ1Ç…é˚ÇﬂÇÈ
	Coord = std::clamp(Coord, -1.0f, 1.0f);

	//àÍéüä÷êîy = ax
	float y = Incli * Coord;
	//å‹éüä÷êîC(t) = 1 - (6(|t|^5) -15(t^4) + 10(|t|^3))
	float C = 1 - (6 * fabsf(powf(Coord, 5))) - 15 * (powf(Coord, 4)) + (10 * fabsf(powf(Coord, 3)));

	//ìÒÇ¬ÇÃä÷êîÇä|ÇØÇΩílÇ™ìöÇ¶
	return y * C;
}

float Math::Sincurve(float val)
{
	return std::sinf(val / std::numbers::pi_v<float>);
}
