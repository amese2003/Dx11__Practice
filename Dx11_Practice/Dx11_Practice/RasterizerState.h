#pragma once
class RasterizerState
{
public:
	RasterizerState(ComPtr<ID3D11Device> device);
	~RasterizerState();

	ComPtr<ID3D11RasterizerState> GetComPtr() { return _rasterizerState; }
	void Create(D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID, D3D11_CULL_MODE cullMode = D3D11_CULL_BACK);


private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11RasterizerState> _rasterizerState;
};

