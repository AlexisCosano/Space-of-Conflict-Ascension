#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "j1Collisions.h"
#include "p2Point.h"

struct SDL_Texture;

class j1Player : public j1Module
{
public:

	j1Player();
	~j1Player();

	bool Start();
	bool PostUpdate();
	bool Update();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void Jump();

public:

	Uint32 time = 0;
	bool allowtime = true;

	bool jumping = false;
	bool flip = false;
	bool dead = false;
	int jcontact = 0;

	iPoint contact;
	fPoint speed;
	fPoint position;
	iPoint sprite_distance;
	float gravity;
	float player_x_displacement;

public:

	SDL_Texture * graphics = nullptr;
};

#endif //__j1PLAYER_H__