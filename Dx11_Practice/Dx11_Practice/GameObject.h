#pragma once

class GameObject
{
public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	void Update();
	void Render(shared_ptr<Pipeline> pipeline);


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

	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;
	
private:
	shared_ptr<Transform> _transform = make_shared<Transform>();

	shared_ptr<Transform> _parent = make_shared<Transform>();

};
