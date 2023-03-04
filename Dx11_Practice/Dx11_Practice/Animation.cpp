#include "pch.h"
#include "Animation.h"

Animation::Animation() : Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
}

void Animation::Save(const wstring& path)
{
}

Vec2 Animation::GetTextureSize()
{
	return _texture->GetSize();
}

const KeyFrame& Animation::GetKeyFrame(int32 index)
{
	return _keyframes[index];
}

int32 Animation::GetKeyFrameCount()
{
	return static_cast<int32>(_keyframes.size());
}

void Animation::AddKeyFrame(const KeyFrame& keyframe)
{
	_keyframes.push_back(keyframe);
}
