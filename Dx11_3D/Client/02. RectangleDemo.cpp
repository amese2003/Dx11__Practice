#include "pch.h"
#include "02. RectangleDemo.h"


void RectangleDemo::Init()
{
	_shader = make_shared<Shader>(L"02. Rectangle.fx");

	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateRectangle(_geometry, Color(1.f, 0.f, 0.f, 1.f));

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}

void RectangleDemo::Update()
{

}

void RectangleDemo::Render()
{
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 1, 6, 0, 0);
}
