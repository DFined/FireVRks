#pragma once

class DFTickableWidget
{
public:
	virtual ~DFTickableWidget() = default;

	virtual void Tick() = 0;
};
