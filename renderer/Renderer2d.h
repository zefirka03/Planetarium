#pragma once
#include "../core/AirCore.h"
#include "Camera2d.h"
#include "Sprite.h"

AIR_NAMESPACE_BEGIN

class SRenderer2d : public System {
public:
	SRenderer2d() = default;
	~SRenderer2d() {};

	void start() override;
	void update() override;
private:
};

AIR_NAMESPACE_END