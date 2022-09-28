#include "pch.h"
#include "gameobjects/Player.h"

#include "core/InputHandler.h"

Player::Player()
	:SDLGameObject()
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
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
}

void Player::clean()
{
}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void Player::handleInput()
{
	constexpr int MOVEMENT_SPEED = 3;

	//Vector2D mousePos = TheInputHandler::Instance()->getMousePosition();
	//
	//m_velocity = mousePos - m_position;
	////m_velocity /= 50;

	// Set velocity to a vector from the players current position to the mouse position. 
	// Can get this vector by subtracting the desired location from the current location. 
	// Divide the vector by 100 to dampen the speed slightly so that we can see it following rather than just sticking to the mouse position
	//Vector2D vec = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = (vec - m_position) / 100; 

	

	if (TheInputHandler::Instance()->isKeyDown(Keyboard::RIGHT_ARROW))
	{
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(Keyboard::LEFT_ARROW))
	{
		m_velocity.setX(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(Keyboard::UP_ARROW))
	{
		m_velocity.setY(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(Keyboard::DOWN_ARROW))
	{
		m_velocity.setY(2);
	}
}
