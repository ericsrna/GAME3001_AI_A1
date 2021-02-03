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
	
	CollisionManager::circleAABBCheck(m_pCharacterRifle, m_pTarget);
	
	if (CollisionManager::lineAABBCheck(m_pCharacterRifle, m_pObstacle))
	{
		m_pCharacterRifle->getRigidBody()->isColliding = true;
	}
	else
	{
		m_pCharacterRifle->getRigidBody()->isColliding = false;
	}
	
	for (int i = 0; i < 4; i++)
	{
		//std::cout << " <<<<<< " << m_pObstaclePath[i]->getDestination().x << ",   " << m_pObstaclePath[i]->getDestination().y <<std::endl;
		if(CollisionManager::lineAABBCheck(m_pObstaclePath[i], m_pObstacle))
		{
			//std::cout << " <<<<<< " << i << std::endl;
			m_pObstaclePath[i]->getRigidBody()->isColliding = true;
		}
	}
}

void PlayScene::clean()
{
	m_pObstaclePath.clear();
	m_pObstaclePath.shrink_to_fit();
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
		setInstructionVisibility(false);
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
		setInstructionVisibility(false);
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
		setInstructionVisibility(false);
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
		setInstructionVisibility(false);
		m_isWorking = true;
		
		m_pTarget->getTransform()->position = glm::vec2(700.0f, 300.0f);
		m_pTarget->setEnabled(true);
		
		m_pObstacle->getTransform()->position = glm::vec2(300.0f, 200.0f);
		m_pObstacle->setEnabled(true);
		
		m_pCharacterRifle->setAlgorithmIndex(4);
		m_pCharacterRifle->getTransform()->position = glm::vec2(50.0f, 300.0f);
		m_pCharacterRifle->setEnabled(true);
		m_pCharacterRifle->setDestination(m_pTarget->getTransform()->position);
		m_pCharacterRifle->setRotation(m_pCharacterRifle->getRotation() * Util::Rad2Deg);

		for (int i = 0; i < 4; i++)
		{
			m_pObstaclePath[i]->setEnabled(true);
			m_pObstaclePath[i]->setDestination(m_pTarget->getTransform()->position);
			m_pObstaclePath[i]->setRotation(m_pObstaclePath[i]->getRotation() * Util::Rad2Deg);
		}
		m_pObstaclePath[0]->getTransform()->position =
			glm::vec2(m_pObstacle->getTransform()->position.x - 50.0f,
				m_pObstacle->getTransform()->position.y - 50.0f);
		m_pObstaclePath[1]->getTransform()->position =
			glm::vec2(m_pObstacle->getTransform()->position.x + 210.0f,
				m_pObstacle->getTransform()->position.y - 50.0f);
		m_pObstaclePath[2]->getTransform()->position =
			glm::vec2(m_pObstacle->getTransform()->position.x - 50.0f,
				m_pObstacle->getTransform()->position.y + 233.0f);
		m_pObstaclePath[3]->getTransform()->position =
			glm::vec2(m_pObstacle->getTransform()->position.x + 210.0f,
				m_pObstacle->getTransform()->position.y + 233.0f);
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_5)) // Reset
	{
		setInstructionVisibility(true);
		m_isWorking = false;
		m_pTarget->setEnabled(false);
		m_pObstacle->setEnabled(false);
		m_pObstacle->getTransform()->position = glm::vec2(0.0f, 900.0f);
		for (int i = 0; i < 4; i++)
		{
			m_pObstaclePath[i]->setEnabled(false);
			m_pObstaclePath[i]->setDestination(m_pTarget->getTransform()->position);
			m_pObstaclePath[i]->setRotation(m_pObstaclePath[i]->getRotation() * Util::Rad2Deg);
			m_pObstaclePath[i]->setRotation(0.0f);
		}
		
		m_pCharacterRifle->setEnabled(false);
		m_pCharacterRifle->getTransform()->position = glm::vec2(50.0f, 50.0f);
		m_pCharacterRifle->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pCharacterRifle->setRotation(0.0f);
		m_pCharacterRifle->setIsMoving(false);
		SoundManager::Instance().pauseSound(1);

		std::cout << "============ Reset ============" << std::endl;
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Obstacle
	m_pObstacle = new Obstacle();
	m_pObstacle->setEnabled(false);
	addChild(m_pObstacle);

	for (int i = 0; i < 4; i++)
	{
		m_pObstaclePath.push_back(new ObstaclePath());
		m_pObstaclePath[i]->setEnabled(false);
		addChild(m_pObstaclePath[i]);
		m_pObstaclePath.shrink_to_fit();
	}

	// Actor
	m_pCharacterRifle = new CharacterRifle();
	m_pCharacterRifle->setEnabled(false);
	addChild(m_pCharacterRifle);

	// Target
	m_pTarget = new Target();
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);

	m_isWorking = false;

	// Instructions
	setInstruction();

	// Sounds
	if (Mix_Init(MIX_INIT_MP3) !=0)
	{
		m_pSoundManager->Instance().load("../Assets/audio/BGM.mp3", "BGM", SOUND_MUSIC);
		m_pSoundManager->Instance().setMusicVolume(40);
		m_pSoundManager->Instance().playMusic("BGM");

		m_pSoundManager->Instance().load("../Assets/audio/saw.wav", "Saw", SOUND_SFX);
		m_pSoundManager->Instance().load("../Assets/audio/stepstone_7.wav", "Step", SOUND_SFX);
	}
}

void PlayScene::setInstruction()
{
	const SDL_Color black = { 0, 0, 0, 255 };
	m_pInstructionPress1 = new Label("Press 1 to play Seeking", "Consolas", 20, black, glm::vec2(400.0f, 20.0f));
	m_pInstructionPress1->setParent(this);
	addChild(m_pInstructionPress1);

	m_pInstructionPress2 = new Label("Press 2 to play Fleeing", "Consolas", 20, black, glm::vec2(400.0f, 70.0f));
	m_pInstructionPress2->setParent(this);
	addChild(m_pInstructionPress2);

	m_pInstructionPress3 = new Label("Press 3 to play Arrival", "Consolas", 20, black, glm::vec2(400.0f, 120.0f));
	m_pInstructionPress3->setParent(this);
	addChild(m_pInstructionPress3);

	m_pInstructionPress4 = new Label("Press 4 to play Obstacle Avoidance", "Consolas", 20, black, glm::vec2(400.0f, 170.0f));
	m_pInstructionPress4->setParent(this);
	addChild(m_pInstructionPress4);

	m_pInstructionPress5 = new Label("Press 5 to Reset (reset each time want to change algorithms)", "Consolas", 20, { 255, 0, 0, 255 }, glm::vec2(400.0f, 220.0f));
	m_pInstructionPress5->setParent(this);
	addChild(m_pInstructionPress5);

	setInstructionVisibility(true);
}

void PlayScene::setInstructionVisibility(bool flag)
{
	m_pInstructionPress1->setEnabled(flag);
	m_pInstructionPress2->setEnabled(flag);
	m_pInstructionPress3->setEnabled(flag);
	m_pInstructionPress4->setEnabled(flag);
	m_pInstructionPress5->setEnabled(flag);
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
