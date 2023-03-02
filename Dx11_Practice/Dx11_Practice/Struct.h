#pragma once
#include "Types.h"

struct Vertex
{
	Vec3 position;
	//Color color;
	Vec2 uv;
};

struct CameraData
{
	Matrix matView;
	Matrix matProjection;
};

struct TransformData
{
	Matrix matWorld;
};