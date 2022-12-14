#pragma once

class SDLGameObject;

/// <summary>
/// Bounding box collision check between two SDLGameObjects - returns true if collision
/// </summary>
bool checkCollision(const SDLGameObject* p1, const SDLGameObject* p2);

/// <summary>
/// Return random number between parameter range
/// </summary>
uint32_t getRandomNumber(uint32_t minimumNum, uint32_t maximumNum);
