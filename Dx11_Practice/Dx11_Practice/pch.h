#pragma once

#include "Types.h"
#include "Values.h"
#include "Struct.h"

// STL
#include <memory>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;

// WIN
#include <windows.h>
#include <assert.h>

// UTILS
#include "tinyxml2.h"
using namespace tinyxml2;

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif

#define CHECK(p)	assert(SUCCEEDED(p))

#include "Game.h"
#define GAME		GGame
#define INPUT		GGame->GetInputManager()
#define TIME		GGame->GetTimeManager()
#define SCENE		GGame->GetSceneManager()
#define RESOURCES	GGame->GetResourceManager()
#define RENDER		GGame->GetRenderManager()

#include "Graphics.h"
#include "Geomatry.h"
#include "GeomatryHelper.h"
#include "VertexData.h"
#include "Transform.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderBase.h"
#include "ConstantBuffer.h"
#include "InputLayout.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "Texture.h"
#include "BlendState.h"
#include "Pipeline.h"
#include "GameObject.h"
#include "Component.h"
