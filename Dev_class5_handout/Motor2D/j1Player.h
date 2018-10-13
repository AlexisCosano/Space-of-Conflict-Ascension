#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;
struct SDL_Rect;

class j1Player : public j1Module
{
public:

	j1Player();

	// Destructor
	virtual ~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Update
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Save & Load
	bool Save(pugi::xml_node&);
	bool Load(pugi::xml_node&);

	bool CheckCollisions();
	bool CheckDeath();
	bool CheckWin();

	void SetTexture(SDL_Texture* texture);

	bool SavePlayerState(pugi::xml_node& node);
	bool LoadState(pugi::xml_node& node);

public:

	SDL_Rect player_rect;
	p2Point<int> position;
	SDL_Texture* texture = nullptr;

	int speed;
	int direction;
	int gravity;
	int jump_force;
	int jump_distance;
	int current_jump_distance;

	bool jumping;

private:
	int current_map = 1;
};

#endif //__j1PLAYER_H__