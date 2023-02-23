#include "pch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device) : _device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create(D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID, D3D11_CULL_MODE cullMode = D3D11_CULL_BACK)
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

	desc.FillMode = fillMode;
	desc.CullMode = cullMode;
	desc.FrontCounterClockwise = false;

	HRESULT hr = _device->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);
}
