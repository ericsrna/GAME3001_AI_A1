#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"
#include "Util.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// getters and seters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	float getRotation() const;

private:
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;

	//pritave method
	void m_buildAnimations();
	void m_MoveSeeking();
	void m_MoveFleeing();
	void m_MoveArriving();
};

#endif /* defined (__PLANE__) */
