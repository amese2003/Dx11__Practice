#pragma once
#include "ResourceBase.h"

class Texture;
class Material;
class Shader;

class Material : public ResourceBase
{
	using Super = ResourceBase;
public:
	Material();
	virtual ~Material();

	auto GetTexture() { return _texture; }
	auto GetShader() { return _shader; }

	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }


private:
	shared_ptr<Texture> _texture;
	shared_ptr<Shader> _shader;
};

