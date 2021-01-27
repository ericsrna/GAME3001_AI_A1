#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1)) // Seeking
	{
		m_pTarget->getTransform()->position = glm::vec2(750.0f, 550.0f);
		m_pTarget->setEnabled(true); 
		m_pPlaneSprite->getTransform()->position = glm::vec2(50.0f, 50.0f);
		m_pPlaneSprite->setEnabled(true);
		m_pPlaneSprite->setDestination(m_pTarget->getTransform()->position);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2)) // Fleeing
	{
		m_pTarget->getTransform()->position = glm::vec2(750.0f, 550.0f);
		m_pTarget->setEnabled(true);
		m_pPlaneSprite->getTransform()->position = glm::vec2(650.0f, 480.0f);
		m_pPlaneSprite->setEnabled(true);
		m_pPlaneSprite->setDestination(m_pTarget->getTransform()->position);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3)) // Arrival
	{

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4)) // Obstacle Avoidance
	{

	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Plane Sprite
	m_pPlaneSprite = new Plane();
	m_pPlaneSprite->getTransform()->position = glm::vec2(50.0f, 50.0f);
	m_pPlaneSprite->setEnabled(false);
	m_pPlaneSprite->setMaxSpeed(10.0f);
	addChild(m_pPlaneSprite);

	// Target
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(700.0f, 500.0f);
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
