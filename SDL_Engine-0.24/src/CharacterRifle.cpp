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
	setMaxSpeed(7.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setAccelerationRate(3.5f);
	setTurnRate(5.0f);
	setTargetRadius(30.0f);
	setSlowRadius(350.0f);
	m_isMoving = false;
}

CharacterRifle::~CharacterRifle()
= default;

void CharacterRifle::draw()
{
	TextureManager::Instance()->draw("CharacterRifle",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 80.0f));
	Util::DrawCircle(getTransform()->position, getWidth() * 0.5f);
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

void CharacterRifle::setTargetRadius(float radius)
{
	m_targetRadius = radius;
}

void CharacterRifle::setSlowRadius(float radius)
{
	m_slowRadius = radius;
}

void CharacterRifle::setIsMoving(bool flag)
{
	m_isMoving = flag;
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

void CharacterRifle::m_MoveAvoiding()
{
	// direction with magnitude. Get the direction to the target
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);
	
	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 3.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		//std::cout << "target_rotation : " << target_rotation << std::endl;
		if (target_rotation > 0.0f)
		{
			//std::cout << "target_rotation++ : " << target_rotation << std::endl;
			if (getRigidBody()->isColliding)
			{
				setRotation(getRotation() + getTurnRate() + 20);
				getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, 0);

				getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
				auto deltaTime = TheGame::Instance()->getDeltaTime();

				getRigidBody()->velocity += getOrientation() * (deltaTime)
					+0.5f * getRigidBody()->acceleration * (deltaTime);
			}
			else
			{
				setRotation(getRotation() + getTurnRate());
				getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

				getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
				auto deltaTime = TheGame::Instance()->getDeltaTime();

				getRigidBody()->velocity += getOrientation() * (deltaTime)
					+0.5f * getRigidBody()->acceleration * (deltaTime);
			}
		}
		else if (target_rotation < 0.0f)
		{
			//std::cout << "target_rotation-- : " << target_rotation << std::endl;
			if (getRigidBody()->isColliding)
			{
					setRotation(getRotation() - getTurnRate() - 20);
					getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, 0);

					getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
					auto deltaTime = TheGame::Instance()->getDeltaTime();

					getRigidBody()->velocity += getOrientation() * (deltaTime)
						+0.5f * getRigidBody()->acceleration * (deltaTime);				
			}
			else
			{
				setRotation(getRotation() - getTurnRate());
				getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

				getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
				auto deltaTime = TheGame::Instance()->getDeltaTime();

				getRigidBody()->velocity += getOrientation() * (deltaTime)
					+0.5f * getRigidBody()->acceleration * (deltaTime);
			}
		}
	}
	//std::cout << target_rotation << std::endl;
	getTransform()->position += getRigidBody()->velocity;
}

void CharacterRifle::m_MoveSeeking()
{
	// direction with magnitude. Get the direction to the target
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	//std::cout << "Target Rotation: " << target_rotation << std::endl;

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

	auto deltaTime = TheGame::Instance()->getDeltaTime();

	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * (deltaTime);
	
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
	if (!m_isMoving)
	{
		SoundManager::Instance().playSound("Step", -1, 1);
		m_isMoving = true;
	}
}

void CharacterRifle::m_MoveFleeing()
{
	// Get the direction away from the target.
	m_targetDirection = getTransform()->position - m_destination;

	// The velocity is along this direction, at full speed. normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	//std::cout << "Target Rotation: " << target_rotation << std::endl;

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

	auto deltaTime = TheGame::Instance()->getDeltaTime();

	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
	//std::cout << getRigidBody()->velocity.x << " ,  " << getRigidBody()->velocity.y << std::endl;
	if (!m_isMoving)
	{
		SoundManager::Instance().playSound("Step", -1, 1);
		m_isMoving = true;
	}
}
void CharacterRifle::m_MoveArriving()
{
	m_targetDirection = m_destination - getTransform()->position;

	m_targetDirection = Util::normalize(m_targetDirection);
	
	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	//std::cout << "Target Rotation: " << target_rotation << std::endl;

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

	auto deltaTime = TheGame::Instance()->getDeltaTime();

	getRigidBody()->velocity += getOrientation() * (deltaTime)
		+0.5f * getRigidBody()->acceleration * (deltaTime);

	m_distance = Util::distance(m_destination, getTransform()->position);
	//std::cout << "distance : " << m_distance << std::endl;
	//std::cout << "m_targetRadius : " << m_targetRadius << std::endl;

	if (m_distance < m_targetRadius) // inside of target
	{
		m_currentSpeed = 0.0f;
	}
	else if (m_distance > m_slowRadius) // outside of slow
	{
		m_currentSpeed = m_maxSpeed;
	}
	else // inside of slow and outside of target
	{
		m_currentSpeed = m_maxSpeed * m_distance / m_slowRadius;
	}

	// The target velocity combines speed and direction
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_currentSpeed);

	getTransform()->position += getRigidBody()->velocity;
	
	if (m_currentSpeed > 0 && !m_isMoving)
	{
		SoundManager::Instance().playSound("Step", -1, 1);
		m_isMoving = true;
	} else if (m_currentSpeed == 0.0f && m_isMoving)
	{
		SoundManager::Instance().pauseSound(1);
		m_isMoving = false;
	}
}
