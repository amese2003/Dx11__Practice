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
	


	_gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_gameObject->SetPosition(Vec3(0.4, 1, 0));
	
}

void Game::Update()
{
	//_transformData.offset.x += 0.0001f;
	//_transformData.offset.y += 0.0001f
	_gameObject->Update();
	
}

void Game::Render()
{
	_graphics->RenderBegin();

	_gameObject->Render(_pipeline);

	_graphics->RenderEnd();
}



