#include "Player.h"

#include <iostream>

#include "InputHandler.h"

Player::Player(const LoaderParams* pParams)
	:SDLGameObject(pParams)
{

}

Player::~Player()
{

}



void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

	SDLGameObject::update();
	// Animation stuff
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	//std::cout << m_acceleration.getX() << std::endl;
	//std::cout << m_velocity.getX() << std::endl;
}

void Player::clean()
{
}

void Player::handleInput()
{
	constexpr int MOVEMENT_SPEED = 3;

	

	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(-1);
	}

	// Set velocity to a vector from the players current position to the mouse position. 
	// Can get this vector by subtracting the desired location from the current location. 
	// Divide the vector by 100 to dampen the speed slightly so that we can see it following rather than just sticking to the mouse position
	//Vector2D vec = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = (vec - m_position) / 100; 

	if (TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		m_velocity.setX(1);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}

	if (TheInputHandler::Instance()->joysticksInitialized())
	{
		// Check if the xvalue of the left stick is more than 0 (that it has moved)
		if (TheInputHandler::Instance()->xValue(0, 1) > 0 || TheInputHandler::Instance()->xValue(0, 1) < 0)
		{
			m_velocity.setX(MOVEMENT_SPEED * TheInputHandler::Instance()->xValue(0, 1));
		}
	
		if (TheInputHandler::Instance()->yValue(0, 1) > 0 || TheInputHandler::Instance()->yValue(0, 1) < 0)
		{
			m_velocity.setY(MOVEMENT_SPEED * TheInputHandler::Instance()->yValue(0, 1));
		}
	
		if (TheInputHandler::Instance()->xValue(0, 2) > 0 || TheInputHandler::Instance()->xValue(0, 2) < 0)
		{
			m_velocity.setX(MOVEMENT_SPEED * TheInputHandler::Instance()->xValue(0, 2));
		}
	
		if (TheInputHandler::Instance()->yValue(0, 2) > 0 || TheInputHandler::Instance()->yValue(0, 2) < 0)
		{
			m_velocity.setY(MOVEMENT_SPEED * TheInputHandler::Instance()->yValue(0, 2));
		}

		if (TheInputHandler::Instance()->getButtonState(0, 3)) // Check if button 3 has been pressed ( Y on Xbox controller)
		{
			m_velocity.setX(1);
		}
	}
}
