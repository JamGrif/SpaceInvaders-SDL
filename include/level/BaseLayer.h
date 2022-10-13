#pragma once

/// <summary>
/// Base class of a level layer
/// Layers are set in the level editor and contain either a tilemap or objects
/// </summary>
class BaseLayer
{
public:
	BaseLayer() {}
	virtual ~BaseLayer() {}

	virtual void renderLayer() = 0;
	virtual void updateLayer() = 0;
};

