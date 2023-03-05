#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Mesh.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraMove.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics) : _graphics(graphics)
{
}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();

	_activeScene->FixedUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
	_activeScene = LoadTestScene();
	Init();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

	shared_ptr<GameObject> camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		camera->GetOrAddTransform();
		camera->AddComponent(make_shared<Camera>());
		scene->AddGameObject(camera);
	}
	{
		camera->AddComponent(make_shared<CameraMove>());
	}

	shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		monster->GetOrAddTransform();
		auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		monster->AddComponent(meshRenderer);

		auto material = RESOURCES->Get<Material>(L"Default");
		meshRenderer->SetMaterial(material);

		auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
		meshRenderer->SetMesh(mesh);

		//monster->GetTransform()->SetRotation(Vec3(0, 45, 0));
		monster->GetTransform()->SetPosition(Vec3(1.414f, 0, 1.414));
		monster->GetTransform()->SetRotation(Vec3(0, -45, 0));
	}
	{
		auto animator = make_shared<Animator>();
		monster->AddComponent(animator);
		auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
		animator->SetAnimation(anim);
	}
	scene->AddGameObject(monster);

	shared_ptr<GameObject> childMonster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		childMonster->GetOrAddTransform();
		auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		childMonster->AddComponent(meshRenderer);

		auto material = RESOURCES->Get<Material>(L"Default");
		meshRenderer->SetMaterial(material);

		auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
		meshRenderer->SetMesh(mesh);

		//monster->GetTransform()->SetRotation(Vec3(0, 45, 0));
		childMonster->GetTransform()->SetPosition(Vec3(3, 0, 0));
		childMonster->GetTransform()->SetRotation(Vec3(0, 45, 0));
	}
	scene->AddGameObject(childMonster);

	return scene;
}
