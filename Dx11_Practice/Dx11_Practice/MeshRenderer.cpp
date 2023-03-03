#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Pipeline.h"
#include "Game.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : Super(ComponentType::MeshRanderer), _device(device), _deviceContext(deviceContext)
{
}

MeshRenderer::~MeshRenderer()
{
}
