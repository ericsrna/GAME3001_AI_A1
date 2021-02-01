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

	if (CollisionManager::lineAABBCheck(m_pCharacterRifle, m_pObstacle))
	{
		m_pCharacterRifle->getRigidBody()->isColliding = true;
	}
	else
	{
		m_pCharacterRifle->getRigidBody()->isColliding = false;
	}
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
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1) && !m_isWorking) // Seeking
	{
		m_isWorking = true;
		m_pTarget->getTransform()->position = glm::vec2(500.0f, 400.0f);
		m_pTarget->setEnabled(true);

		m_pCharacterRifle->setAlgorithmIndex(1);
		m_pCharacterRifle->getTransform()->position = glm::vec2(50.0f, 40.0f);
		m_pCharacterRifle->setEnabled(true);
		m_pCharacterRifle->setDestination(m_pTarget->getTransform()->position);
		m_pCharacterRifle->setRotation(m_pCharacterRifle->getRotation() * Util::Rad2Deg);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2) && !m_isWorking) // Fleeing
	{
		m_isWorking = true;
		m_pTarget->getTransform()->position = glm::vec2(750.0f, 550.0f);
		m_pTarget->setEnabled(true);

		m_pCharacterRifle->setAlgorithmIndex(2);
		m_pCharacterRifle->getTransform()->position = glm::vec2(650.0f, 480.0f);
		m_pCharacterRifle->setEnabled(true);
		m_pCharacterRifle->setDestination(m_pTarget->getTransform()->position);
		m_pCharacterRifle->setRotation(m_pCharacterRifle->getRotation() * Util::Rad2Deg);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3) && !m_isWorking) // Arrival
	{
		m_isWorking = true;
		
		m_pTarget->getTransform()->position = glm::vec2(500.0f, 400.0f);
		m_pTarget->setEnabled(true);

		m_pCharacterRifle->setAlgorithmIndex(3);
		m_pCharacterRifle->getTransform()->position = glm::vec2(50.0f, 40.0f);
		m_pCharacterRifle->setEnabled(true);
		m_pCharacterRifle->setDestination(m_pTarget->getTransform()->position);
		m_pCharacterRifle->setRotation(m_pCharacterRifle->getRotation() * Util::Rad2Deg);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4) && !m_isWorking) // Obstacle Avoidance
	{
		m_isWorking = true;
		m_pTarget->getTransform()->position = glm::vec2(700.0f, 300.0f);
		m_pTarget->setEnabled(true);
		m_pObstacle->getTransform()->position = glm::vec2(400.0f, 300.0f);
		m_pObstacle->setEnabled(true);
		
		m_pCharacterRifle->setAlgorithmIndex(4);
		m_pCharacterRifle->getTransform()->position = glm::vec2(50.0f, 300.0f);
		m_pCharacterRifle->setEnabled(true);
		m_pCharacterRifle->setDestination(m_pTarget->getTransform()->position);
		m_pCharacterRifle->setRotation(m_pCharacterRifle->getRotation() * Util::Rad2Deg);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_5)) // Reset
	{
		m_isWorking = false;
		m_pTarget->setEnabled(false);
		m_pObstacle->setEnabled(false);
		
		m_pCharacterRifle->setEnabled(false);
		m_pCharacterRifle->getTransform()->position = glm::vec2(50.0f, 50.0f);
		m_pCharacterRifle->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pCharacterRifle->setRotation(0.0f);

		std::cout << "============ Reset ============" << std::endl;
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Plane Sprite
	m_pObstacle = new Obstacle();
	m_pObstacle->setEnabled(false);
	addChild(m_pObstacle);

	m_pCharacterRifle = new CharacterRifle();
	m_pCharacterRifle->setEnabled(false);
	addChild(m_pCharacterRifle);

	// Target
	m_pTarget = new Target();
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);

	m_isWorking = false;
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
