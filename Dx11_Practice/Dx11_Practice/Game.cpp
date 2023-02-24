#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice());
	_indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
	
	GeometryHelper::CreateRectangle(_geometry);
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer->Create(_geometry->GetIndices());
	
	_vertexShader = make_shared<VertexShader>(_graphics->GetDevice());
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	
	_pixelShader = make_shared<PixelShader>(_graphics->GetDevice());
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_constantBuffer->Create();
	
	_inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	_rasterizerState = make_shared<RasterizerState>(_graphics->GetDevice());
	_rasterizerState->Create();


	_texture = make_shared<Texture>(_graphics->GetDevice());
	_texture->Create(L"Skeleton.png");
	
	_samplerState = make_shared<SamplerState>(_graphics->GetDevice());
	_samplerState->Create();

	_blendState = make_shared<BlendState>(_graphics->GetDevice());
	_blendState->Create();
}

void Game::Update()
{
	//_transformData.offset.x += 0.0001f;
	//_transformData.offset.y += 0.0001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation;
	_transformData.matWorld = matWorld;

	_constantBuffer->CopyData(_transformData);
}

void Game::Render()
{
	_graphics->RenderBegin();

	{
		PipelineInfo info;
		info.inputLayout = _inputLayout;
		info.vertexShader = _vertexShader;
		info.rasterizerState = _rasterizerState;
		info.pixelShader = _pixelShader;
		info.blendState = _blendState;
		_pipeline->UpdatePipeline(info); 


		// IA
		_pipeline->SetVertexBuffer(_vertexBuffer);
		_pipeline->SetIndexBuffer(_indexBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, _texture);
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);

	}

	_graphics->RenderEnd();
}



