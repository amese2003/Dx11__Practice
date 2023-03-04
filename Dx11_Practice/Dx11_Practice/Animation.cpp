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
	tinyxml2::XMLDocument doc;
	string pathStr(path.begin(), path.end());
	XMLError error = doc.LoadFile(pathStr.c_str());
	CHECK(error == XMLError::XML_SUCCESS);

	XMLElement* root = doc.FirstChildElement();
	string nameStr = root->Attribute("Name");
	_name = wstring(nameStr.begin(), nameStr.end());

	_loop = root->BoolAttribute("Loop");
	_path = path;

	XMLElement* node = root->FirstChildElement();
	for (; node != nullptr; node = node->NextSiblingElement())
	{
		KeyFrame keyframe;

		keyframe.offset.x = node->FloatAttribute("OffsetX");
		keyframe.offset.y = node->FloatAttribute("OffsetX");
		keyframe.size.x = node->FloatAttribute("SizeX");
		keyframe.size.y = node->FloatAttribute("SizeY");
		keyframe.time = node->FloatAttribute("Time");

		AddKeyFrame(keyframe);
	}
}

void Animation::Save(const wstring& path)
{
	tinyxml2::XMLDocument doc;
	XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);

	string nameString(GetName().begin(), GetName().end());
	root->SetAttribute("Name", nameString.c_str());
	root->SetAttribute("Loop", _loop);
	root->SetAttribute("TexturePath", "TODO");

	for (const auto& keyframe : _keyframes)
	{
		XMLElement* node = doc.NewElement("Keyframe");
		root->LinkEndChild(node);

		node->SetAttribute("OffsetX", keyframe.offset.x);
		node->SetAttribute("OffsetY", keyframe.offset.y);
		node->SetAttribute("SizeX", keyframe.size.x);
		node->SetAttribute("SizeY", keyframe.size.x);
		node->SetAttribute("Time", keyframe.time);
	}

	string pathStr(path.begin(), path.end());
	auto result = doc.SaveFile(pathStr.c_str());
	CHECK(result == XMLError::XML_SUCCESS);
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
