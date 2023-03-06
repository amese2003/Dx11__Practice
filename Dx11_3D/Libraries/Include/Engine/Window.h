#pragma once

struct WindowDesc
{
	shared_ptr<class IExecute> app = nullptr;
	wstring appName = L"GameCoding";
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
	float width = 800;
	float height = 600;
	bool vsync = false;
	bool windowed = true;
	Color backColor = Color(0.5, 0.5, 0.5, 0.5f);
};

class Window
{
public:
	WPARAM Run(WindowDesc& desc);

private:
	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);

	void Update();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	static shared_ptr<class IExecute> GExecute;

	WindowDesc _desc;
};

