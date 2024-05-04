#include "Wall_Window.h"
#include"Engine/Systems/ModelSystem.h"
Wall_Window::Wall_Window(Object* parent)
	:GameObject(parent,"Wall_Window")
{
}

Wall_Window::~Wall_Window()
{
}

void Wall_Window::Initialize()
{
	Test_Model_ECSver model(this);
	model.Load("Assets/Model/wallWindowSlide.fbx");
	AddComponent<Test_Model_ECSver>(model);
}

void Wall_Window::Start()
{
}

void Wall_Window::Update()
{
}

void Wall_Window::Release()
{
}
