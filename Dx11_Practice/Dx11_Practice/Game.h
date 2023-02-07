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

private:
	HWND _hwnd = {};
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// DX
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

};

