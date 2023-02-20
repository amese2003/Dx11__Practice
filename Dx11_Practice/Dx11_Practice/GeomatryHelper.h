#pragma once
#include "Geomatry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateRectangle(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateRectangle(shared_ptr<Geometry<VertexTextureData>> geometry);
};

