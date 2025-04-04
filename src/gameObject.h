#pragma once

class GameObject {
	public:
		GameObject(){};
		virtual int init() = 0;
		virtual int tick(double deltaTime) = 0;
};