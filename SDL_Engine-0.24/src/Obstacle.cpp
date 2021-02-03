#include "Obstacle.h"

#include "Util.h"

Obstacle::Obstacle()
{
	TextureManager::Instance()->load("../Assets/textures/tank.png", "obstacle");

	auto size = TextureManager::Instance()->getTextureSize("obstacle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(0.0f, 900.0f);
	getRigidBody()->isColliding = false;
	setType(OBSTACLE);
}

Obstacle::~Obstacle()
= default;

void Obstacle::draw()
{
	TextureManager::Instance()->draw("obstacle",
		getTransform()->position.x, getTransform()->position.y, 0, 255, false);
	Util::DrawRect(getTransform()->position, getWidth(), getHeight());
}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
