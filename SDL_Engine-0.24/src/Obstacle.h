#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__

#include "DisplayObject.h"
#include "TextureManager.h"

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
};


#endif // !__OBSTACLE__
