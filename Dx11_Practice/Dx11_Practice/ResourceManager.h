#pragma once
#include "ResourceBase.h"

class Mesh;
class Shader;
class Texture;
class Material;
class Animation;


class ResourceManager
{
public:
	ResourceManager(ComPtr<ID3D11Device> device);

	void Init();

	template<typename Ty>
	shared_ptr<Ty> Load(const wstring& key, const wstring& path);

	template<typename Ty>
	bool Add(const wstring& key, shared_ptr<Ty> obj);

	template<typename Ty>
	shared_ptr<Ty> Get(const wstring& key);

	template<typename Ty>
	ResourceType GetResourceType();

private:
	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();

private:
	ComPtr<ID3D11Device> _device;

	using KeyObjMap =  map<wstring, shared_ptr<ResourceBase>>;
	array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;
};

template<typename Ty>
inline shared_ptr<Ty> ResourceManager::Load(const wstring& key, const wstring& path)
{
	ResourceType type = GetResourceType<Ty>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(type)];

	auto findit = keyObjMap.find(key);
	if (findit != keyObjMap.end())
		return static_pointer_cast<Ty>(findit->second);

	shared_ptr<Ty> object = make_shared<Ty>();
	object->Load(path);
	keyObjMap[key] = object;
	return object;
}

template<typename Ty>
inline bool ResourceManager::Add(const wstring& key, shared_ptr<Ty> object)
{
	ResourceType type = GetResourceType<Ty>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(type)];

	auto findit = keyObjMap.find(key);
	if (findit != keyObjMap.end())
		return false;

	keyObjMap[key] = object;
	return true;
}

template<typename Ty>
inline shared_ptr<Ty> ResourceManager::Get(const wstring& key)
{
	ResourceType type = GetResourceType<Ty>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(type)];

	auto findit = keyObjMap.find(key);
	if (findit != keyObjMap.end())
		return static_pointer_cast<Ty>(findit->second);

	return nullptr;
}

template<typename Ty>
inline ResourceType ResourceManager::GetResourceType()
{
	if (::is_same_v<Ty, Mesh>)
		return ResourceType::Mesh;

	if (::is_same_v<Ty, Shader>)
		return ResourceType::Shader;

	if (::is_same_v<Ty, Texture>)
		return ResourceType::Texture;

	if (::is_same_v<Ty, Material>)
		return ResourceType::Material;

	if (::is_same_v<Ty, Animation>)
		return ResourceType::Animation;

	CHECK(false);
	return ResourceType::None;
}
