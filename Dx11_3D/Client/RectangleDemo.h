#pragma once
#include "IExecute.h"
#include "VertexData.h"
#include "Engine/IndexBuffer.h"
#include "Engine/Geometry.h"
#include "Engine/GeometryHelper.h"

class RectangleDemo : public IExecute
{

public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
};

