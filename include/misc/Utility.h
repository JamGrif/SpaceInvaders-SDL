#pragma once


class SDLGameObject;

/// <summary>
/// Bounding box collision check between two SDLGameObjects - returns true if collision
/// </summary>
bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

/// <summary>
/// Return random number between parameter range
/// </summary>
int getRandomNumber(int minimumNum, int maximumNum);
