#pragma once
#include "Component.h"

class Mesh;
#include "Shader.h"
class Material;
class Pipeline;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();

	virtual void Update() override;



private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;

	friend class RenderManager;
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;


	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<PixelShader> _pixelShader;
	

	shared_ptr<Texture> _texture;



private:
	

};

