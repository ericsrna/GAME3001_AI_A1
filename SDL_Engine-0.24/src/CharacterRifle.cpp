#include "CharacterRifle.h"
#include "Game.h"

CharacterRifle::CharacterRifle()
{
	TextureManager::Instance()->load("../Assets/textures/rifle/move/survivor-move_rifle_0.png", "CharacterRifle");

	auto size = TextureManager::Instance()->getTextureSize("CharacterRifle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(CHARACTER_RIFLE);
	setMaxSpeed(5.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setAccelerationRate(2.0f);
	setTurnRate(5.0f);
}

CharacterRifle::~CharacterRifle()
= default;

void CharacterRifle::draw()
{
	TextureManager::Instance()->draw("CharacterRifle",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f));
}

void CharacterRifle::update()
{
	switch (m_algorithmIndex)
	{
	case 1:
		m_MoveSeeking();
		break;
	case 2:
		m_MoveFleeing();
		break;
	case 3:
		m_MoveArriving();
		break;
	case 4:
		m_MoveAvoiding();
		break;
	default:
		break;	
	}
}

void CharacterRifle::clean()
{
}

void CharacterRifle::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void CharacterRifle::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 CharacterRifle::getOrientation()
{
	return m_orientation;
}

void CharacterRifle::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float CharacterRifle::getRotation()
{
	return m_rotationAngle;
}

void CharacterRifle::setRotation(float angle)
{
	m_rotationAngle = angle;

	const auto offset = 3.0f;
	const auto angle_in_radians = (angle - offset) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);

	// Convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float CharacterRifle::getTurnRate()
{
	return m_turnRate;
}

void CharacterRifle::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float CharacterRifle::getAccelerationRate()
{
	return m_accelerationRate;
}

void CharacterRifle::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void CharacterRifle::setAlgorithmIndex(short index)
{
	m_algorithmIndex = index;
}

void CharacterRifle::m_MoveSeeking()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	std::cout << "Target Rotation: " << target_rotation << std::endl;
	
	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}
	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void CharacterRifle::m_MoveFleeing()
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

void CharacterRifle::m_MoveArriving()
{
}

void CharacterRifle::m_MoveAvoiding()
{
}