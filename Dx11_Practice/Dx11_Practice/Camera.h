#pragma once
#include "Component.h"
#include "Transform.h"

enum class ProjectionType
{
	Perspective,
	Orthographic,
};

class Camera : public Component
{
	using Super = Component;

public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void SetProjectionType(ProjectionType type);
	ProjectionType GetProjectionType() { return _type; }

	void UpdateMatrix();

private: 
	ProjectionType _type = ProjectionType::Orthographic;

public:
	static Matrix S_MatViews;
	static Matrix S_MatProjection;

};

