#include "Plane.h"
#include "TextureManager.h"

Plane::Plane()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", getAnimation("plane"),
		x, y, 0.5f, 0, 255, true);
}

void Plane::update()
{
	//m_MoveSeeking();
	m_MoveFleeing();
}

void Plane::clean()
{
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}

void Plane::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void Plane::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Plane::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Plane::setRotation(const float angle)
{
	m_rotationAngle = angle;
}

float Plane::getRotation() const
{
	return m_rotationAngle;
}

void Plane::m_MoveSeeking()
{
	// Get the direction to the target. direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// The velocity is along this direction, at full speed. normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;

}

void Plane::m_MoveFleeing()
{
	// Get the direction away from the target.
	m_targetDirection = getTransform()->position - m_destination;

	// The velocity is along this direction, at full speed. normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	// Todo specific values change to boundaries
	if (getTransform()->position.x > 50.0f || getTransform()->position.y > 50.0f)
		getTransform()->position += getRigidBody()->velocity;
}

void Plane::m_MoveArriving()
{

}