#pragma once


// Base class
class BaseLayer
{
public:
	BaseLayer();
	virtual ~BaseLayer();

	virtual void renderLayer() = 0;
	virtual void updateLayer() = 0;



protected:

	
};

