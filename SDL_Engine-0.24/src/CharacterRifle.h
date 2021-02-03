#pragma once
#ifndef __CHARACTER_RIFLE__
#define __CHARACTER_RIFLE__

#include "Sprite.h"
#include "TextureManager.h"
#include "SoundManager.h"

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

	// getters
	glm::vec2 getOrientation();
	float getRotation();
	float getTurnRate();
	float getAccelerationRate();
	
	// setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	void setTurnRate(float rate);
	void setAccelerationRate(float rate);
	void setAlgorithmIndex(short index);
	void setTargetRadius(float radius);
	void setSlowRadius(float radius);
	void setIsMoving(bool flag);

private:
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	glm::vec2 m_targetVelocity;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	float m_targetRadius;
	float m_slowRadius;
	float m_distance;
	float m_currentSpeed;

	bool m_isMoving;
	short m_algorithmIndex;

	// private method
	void m_MoveSeeking();
	void m_MoveFleeing();
	void m_MoveArriving();
	void m_MoveAvoiding();
};

#endif