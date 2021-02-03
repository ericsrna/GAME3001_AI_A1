#include "ObstaclePath.h"

#include "Util.h"

ObstaclePath::ObstaclePath()
{
	setWidth(40);
	setHeight(40);

	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->isColliding = false;
	setOrientation(glm::vec2(0.0f, -1.0f));
	setType(OBSTACLE);
}

ObstaclePath::ObstaclePath(glm::vec2 target)
{
	setWidth(40);
	setHeight(40);

	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->isColliding = false;
	
	setOrientation(glm::vec2(0.0f, -1.0f));
	setType(OBSTACLE);
}

ObstaclePath::~ObstaclePath()
= default;

void ObstaclePath::draw()
{
	Util::DrawRect(getTransform()->position, getWidth(), getHeight());
	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 500.0f));
	//std::cout << "m_orientation : " << m_orientation.x << ",  " <<  m_orientation.y << std::endl;
}

void ObstaclePath::update()
{
	SetRotationToTarget();
	//std::cout << "Colliding : " << getRigidBody()->isColliding << std::endl;
}

void ObstaclePath::clean()
{
}

glm::vec2 ObstaclePath::getOrientation()
{
	return m_orientation;
}

glm::vec2 ObstaclePath::getDestination()
{
	return m_destination;
}
void ObstaclePath::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float ObstaclePath::getRotation()
{
	return m_rotationAngle;
}

void ObstaclePath::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void ObstaclePath::setRotation(float angle)
{
	m_rotationAngle = angle;

	const auto offset = 3.0f;
	const auto angle_in_radians = (angle - offset) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);

	// Convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

void ObstaclePath::SetRotationToTarget()
{
	// direction with magnitude. Get the direction to the target
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);
	setRotation(target_rotation);
}