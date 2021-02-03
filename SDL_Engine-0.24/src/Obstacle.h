#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__

#include "DisplayObject.h"
#include "TextureManager.h"
#include "ObstaclePath.h"

class Obstacle final : public DisplayObject
{
public:
	// constructors
	Obstacle();

	// destructor
	~Obstacle();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;

	std::vector<ObstaclePath>* m_pObstaclePath[];
};


#endif // !__OBSTACLE__
