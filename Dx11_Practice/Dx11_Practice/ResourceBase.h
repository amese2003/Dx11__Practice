#pragma once

enum class ResourceType : uint8
{
	None = -1,

	// ?
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	END
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<ResourceType>(ResourceType::END)
};

class ResourceBase : public enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();

	ResourceType GetResourceType() { return _type; }

	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() { return _name; }
	uint32 GetID() { return _id; }

protected:
	virtual void Load(const wstring& name) { }
	virtual void Save(const wstring& name) { }


protected:
	ResourceType _type = ResourceType::None;
	wstring _name;
	wstring _path;
	uint32 _id = 0;

};

