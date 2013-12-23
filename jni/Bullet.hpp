#ifndef BULLET_HPP
#define BULLET_HPP

#include "Dimensions.hpp"

namespace test {

  // Bullets particle system product
  class Bullet {

  public:
	float x = 0;
	float y = 0;
	float angle = 0;
	float size = 0.1;
	float velX = 0;
	float velY = 0;
	float velAngle = 0;
	bool dead = false;
	float lifeTimer = 0.0f;

	void Init();
	void Update(double dt);
	void Draw();
	void Release();
	Dimensions GetDimensions() const;

  protected:
  private:
  };

}

#endif// BULLET_HPP
