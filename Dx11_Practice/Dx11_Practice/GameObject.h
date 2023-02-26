#pragma once

class MonoBehaviour;

class GameObject
{
public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render(shared_ptr<Pipeline> pipeline);

	void SetPosition(const Vec3& pos);


private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	shared_ptr<Geometry<VertexTextureData>> _geometry;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<BlendState> _blendState;

	shared_ptr<Texture> _texture;
	shared_ptr<SamplerState> _samplerState;


	
private:
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	shared_ptr<Transform> _transform = make_shared<Transform>();

protected:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<Component>> _scripts;

};

