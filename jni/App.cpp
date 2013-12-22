#include "App.hpp"

#include <stdlib.h>
#include <math.h>

#include "Graphics.hpp"

namespace test {

  void App::Init() {
	asteroids.Init();
	spliceAsteroids.Init();
	progress.Init();
	stars.Init();

	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].Init();
	  bullets[i].Init();
	}
  }

  void App::Update(double dt) {
	progress.Update(dt);

	if (!progress.IsPaused()) {
	  asteroids.Update(dt);
	  spliceAsteroids.Update(dt);
	  stars.Update(dt);

	  int livesTotal = 0;
	  int activeTotal = 0;

	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Update(dt);
		bullets[i].Update(dt);
		bullets[i].SetPos(players[i].GetX(), players[i].GetY());
		bullets[i].SetAngle(players[i].GetAngle());
		bullets[i].SetSpawning(players[i].IsSpawned());

		auto callback = [&] (Asteroid & a, Asteroid & b) {
		  if (&a != &b) {
			// TODO improve algo using absolute rigid body law
			auto deltax = a.x - b.x;
			auto deltay = a.y - b.y;
			auto distance = sqrt(deltax * deltax + deltay * deltay);
			deltax /= distance;
			deltay /= distance;
			a.velX += deltax * b.size;
			a.velY += deltay * b.size;
			b.velX -= deltax * a.size;
			b.velY -= deltay * a.size;
		  }
		};

		asteroids.Collide<Asteroid>(asteroids, callback);
		asteroids.Collide<Asteroid>(spliceAsteroids, callback);
		spliceAsteroids.Collide<Asteroid>(spliceAsteroids, callback);

		asteroids.Collide<Bullet>(bullets[i], [&] (Asteroid & a, Bullet & b) {
			a.dead = true;
			b.dead = true;
		  });
		spliceAsteroids.Collide<Bullet>(bullets[i], [&] (Asteroid & a, Bullet & b) {
			a.dead = true;
			b.dead = true;
		  });
		players[i].Collide<Asteroid>(asteroids, [&] (Asteroid & a, Player & p) {
			p.Kill();
			a.dead = true;
		  });
		players[i].Collide<Asteroid>(spliceAsteroids, [&] (Asteroid & a, Player & p) {
			p.Kill();
			a.dead = true;
		  });

		if (players[i].IsActive()) {
		  activeTotal++;
		  livesTotal += players[i].GetLives();
		}
	  }

	  if (livesTotal < 1 && activeTotal) {
		for (int i = 0; i < maxPlayersCount; i++) {
		  players[i].Reset();
		  bullets[i].Clean();
		}
		progress.RestartGame();
		asteroids.Clean();
		spliceAsteroids.Clean();
		stars.Clean();
	  }
	}
  }

  void App::Draw() {
	SetProjection(fieldWidth, fieldHeight);

	if (!progress.IsPaused()) {
	  asteroids.Draw();
	  spliceAsteroids.Draw();
	  stars.Draw();
	  for (int i = 0; i < maxPlayersCount; i++) {
		players[i].Draw();
		bullets[i].Draw();
	  }
	}

	progress.Draw();
  }

  void App::Release() {
	asteroids.Release();
	spliceAsteroids.Release();
	progress.Release();
	stars.Release();
	for (int i = 0; i < maxPlayersCount; i++) {
	  players[i].Release();
	  bullets[i].Release();
	}
  }

  void App::Touch(int player, float newX, float newY) {
	auto x = newX / screenWidth * fieldWidth;
	auto y = (1.0 - newY / screenHeight) * fieldHeight;

	progress.Touch(newX, newY);

	if (!progress.IsPaused() && players[player].GetLives() > 0) {
	  players[player].Touch(x, y);
	}
  }

  void App::TouchEnd(int player, float newX, float newY) {
  }

  void App::ScreenSize(float newWidth, float newHeight) {
	screenWidth = (newWidth > 0.1 ? newWidth : 1.0f);
	screenHeight = (newHeight > 0.1 ? newHeight : 1.0f);
	fieldHeight = fieldWidth * screenHeight / screenWidth;
	asteroids.FieldSize(fieldWidth, fieldHeight);
	spliceAsteroids.FieldSize(fieldWidth, fieldHeight);
	progress.FieldSize(fieldWidth, fieldHeight);
	stars.FieldSize(fieldWidth, fieldHeight);
	for (int i = 0; i < maxPlayersCount; i++) {
	  bullets[i].FieldSize(fieldWidth, fieldHeight);
	}
  }

}
