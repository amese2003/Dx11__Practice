#include "pch.h"
#include "Animator.h"
#include "Game.h"
#include "TimeManager.h"

Animator::Animator() : Super(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update()
{
	shared_ptr<Animation> animation = GetCurrentAnimation();
	if (animation == nullptr)
		return;

	const KeyFrame& keyFrame = animation->GetKeyFrame(_currentKeyFrameIndex);

	float deltaTime = TIME->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= keyFrame.time)
	{
		_currentKeyFrameIndex++;
		int32 totalCount = animation->GetKeyFrameCount();

		if (_currentKeyFrameIndex >= totalCount)
		{
			if (animation->IsLoop())
				_currentKeyFrameIndex = 0;
			else
				_currentKeyFrameIndex = totalCount - 1;
		}
			
		_sumTime = 0.f;
	}
}

shared_ptr<Animation> Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const KeyFrame& Animator::GetCurrentKeyFrame()
{
	return _currentAnimation->GetKeyFrame(_currentKeyFrameIndex);
}
