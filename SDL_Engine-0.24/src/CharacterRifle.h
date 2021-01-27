#pragma once
#ifndef __CHARACTER_RIFLE__
#define __CHARACTER_RIFLE__

#include "Sprite.h"
#include "TextureManager.h"
#include "Util.h"

class CharacterRifle final : public Sprite
{
public:
	// Constructors
	CharacterRifle();

	// Destructor
	~CharacterRifle();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation();
	void setOrientation(glm::vec2 orientation);
	float getRotation();
	void setRotation(float angle);
	float getTurnRate();
	void setTurnRate(float rate);
	float getAccelerationRate();
	void setAccelerationRate(float rate);
	void setAlgorithmIndex(short index);

private:
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	short m_algorithmIndex;

	// private method
	void m_MoveSeeking();
	void m_MoveFleeing();
	void m_MoveArriving();
	void m_MoveAvoiding();
	
};

#endif