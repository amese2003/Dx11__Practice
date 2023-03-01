#include "pch.h"
#include "GameObject.h"
#include "MonoBehavior.h"
#include "Transform.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : _device(device)
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());
	
	_vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	
	_pixelShader = make_shared<PixelShader>(_device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(_device, deviceContext);
	_transformBuffer->Create();
	
	_inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	_texture = make_shared<Texture>(_device);
	_texture->Create(L"Skeleton.png");
	
	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();

	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();
}

GameObject::~GameObject()
{
	
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Awake();
	}

	for (shared_ptr<Component>& script : _scripts)
		script->Awake();

	GetOrAddTransform();
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<Component>& script : _scripts)
		script->Start();
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}
		

	for (shared_ptr<Component>& script : _scripts)
		script->Update();

	_transformData.matWorld = GetOrAddTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<Component>& script : _scripts)
		script->LateUpdate();
}

void GameObject::FixedUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->FixedUpdate();
	}

	for (shared_ptr<Component>& script : _scripts)
		script->FixedUpdate();
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	CHECK(index < FIXED_COMPONENT_COUNT);
	return _components[index];

}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		shared_ptr<Transform> transform = make_shared<Transform>(); 
		AddComponent(transform);
	}

	return GetTransform();
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());

	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
	{
		PipelineInfo info;
		info.inputLayout = _inputLayout;
		info.vertexShader = _vertexShader;
		info.rasterizerState = _rasterizerState;
		info.pixelShader = _pixelShader;
		info.blendState = _blendState;
		pipeline->UpdatePipeline(info);


		// IA
		pipeline->SetVertexBuffer(_vertexBuffer);
		pipeline->SetIndexBuffer(_indexBuffer);
		pipeline->SetConstantBuffer(0, SS_VertexShader, _transformBuffer);
		pipeline->SetTexture(0, SS_PixelShader, _texture);
		pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);

	}
}
