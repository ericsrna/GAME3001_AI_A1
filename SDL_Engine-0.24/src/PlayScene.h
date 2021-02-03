#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "CharacterRifle.h"
#include "Label.h"
#include "Obstacle.h"
#include "Target.h"
#include "SoundManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void setInstruction();
	void setInstructionVisibility(bool flag);

private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Obstacle* m_pObstacle;
	Target* m_pTarget;
	CharacterRifle* m_pCharacterRifle;
	std::vector<ObstaclePath*> m_pObstaclePath;
	SoundManager* m_pSoundManager;

	bool m_isWorking;

	Label* m_pInstructionPress1{};
	Label* m_pInstructionPress2{};
	Label* m_pInstructionPress3{};
	Label* m_pInstructionPress4{};
	Label* m_pInstructionPress5{};
	
	/*Player* m_pPlayer;
	bool m_playerFacingRight;*/

	// UI Items
	/*Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;*/
};

#endif /* defined (__PLAY_SCENE__) */