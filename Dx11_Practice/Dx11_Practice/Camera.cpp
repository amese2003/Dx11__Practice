#include "pch.h"
#include "Camera.h"

void Camera::Update()
{
}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vec3 upDirection =  GetTransform()->GetUp();
	S_MatViews = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	if (_type == ProjectionType::Perspective)
	{
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	}
	else
	{
		S_MatProjection = ::XMMatrixOrthographicLH(800, 600, 0.f, 1.f);
	}

}

