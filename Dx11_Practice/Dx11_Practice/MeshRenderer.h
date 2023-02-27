#pragma once
#include "Component.h"

class Mesh;
#include "Shader.h"
class Material;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~MeshRenderer();

	void SetMaterial(shared_ptr<Material> material);
	void SetShader(shared_ptr<Shader> shader);
	void SetMesh(shared_ptr<Mesh> mesh);
	void SetTexture(shared_ptr<Texture> texture);

	auto GetMaterial();
	auto GetVertexShader();
	auto GetInputLayout();
	auto GetPixelShader();

	shared_ptr<Mesh> GetMesh();
	shared_ptr<Texture> GetTexture();

private:
	friend class RenderManager;

	ComPtr<ID3D11Device> _device;

	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
};

