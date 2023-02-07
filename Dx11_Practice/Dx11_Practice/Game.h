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
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewPort();

private:
	HWND _hwnd = {};
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// DX
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = { 0 };
	float _clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
};

