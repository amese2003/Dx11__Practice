#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();





private:
	void CreateGeometry();
	void CreateInputLayout();

	void CreateSRV();
	void CreateBlendState();



private:
	HWND _hwnd = {};
	shared_ptr<Graphics> _graphics;
	

private:
	// Geometry
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	
	
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;
	

	// VS
	shared_ptr<VertexShader> _vertexShader;
	//ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	//ComPtr<ID3DBlob> _vsBlob = nullptr;

	// RS
	shared_ptr<RasterizerState> _rasterizerState;

	// PS
	shared_ptr<PixelShader> _pixelShader;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView1 = nullptr;

	shared_ptr<SamplerState> _samplerState;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

private:
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	Vec3 _localRotation = {0.f, 0.f, 0.f};
	Vec3 _localScale = { 1.f, 1.f, 1.f };
};

