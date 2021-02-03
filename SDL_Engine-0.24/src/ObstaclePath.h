#pragma once
#ifndef __OBSTACLE_PATH__
#define __OBSTACLE_PATH__

#include "Sprite.h"
#include "TextureManager.h"

class ObstaclePath : public Sprite
{
public:
	// constructors
	ObstaclePath();
	ObstaclePath(glm::vec2 target);

	// destructor
	~ObstaclePath();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;

	glm::vec2 getOrientation();
	glm::vec2 getDestination();
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	void SetRotationToTarget();
	float getRotation();
	void setDestination(glm::vec2 destination);

	ObstaclePath* m_pNextPath;
	glm::vec2 m_orientation;
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	float m_rotationAngle;
	
};


#endif // !__OBSTACLE_PATH__
