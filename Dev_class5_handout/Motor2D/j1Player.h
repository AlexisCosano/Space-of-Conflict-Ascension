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

	void SetTexture(SDL_Texture* normal_texture, SDL_Texture* god_mode_texture);

	bool SavePlayerState(pugi::xml_node& node);
	bool LoadState(pugi::xml_node& node);

public:

	int speed;
	int gravity;
	int direction;
	int jump_force;
	int jump_distance;
	int current_jump_distance;

	SDL_Rect player_rect;
	p2Point<int> position;
	SDL_Texture* texture = nullptr;
	SDL_Texture* god_mode_texture = nullptr;

	bool jump_banned;
	bool god_mode = false;

private:
	int current_map = 1;

	bool grounded = false;
	bool jumping = false;

	void FallDown();
	void Jump();
};

#endif //__j1PLAYER_H__