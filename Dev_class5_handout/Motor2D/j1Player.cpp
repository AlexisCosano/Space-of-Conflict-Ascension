#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Audio.h"


j1Player::j1Player()
{
	name.create("player");
	position.x = 0;
	position.y = 0;
	int row = 0;

	sprite_distance.x = 548;
	sprite_distance.y = 482;
}

j1Player::~j1Player()
{
	App->tex->UnLoad(graphics);
}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	graphics = App->tex->Load("textures/placeholder.png");

	if (graphics != nullptr)
	{
		LOG("Player texture loaded successfully.");
	}

	SDL_Rect r{ 0, 0, 481, 547 };

	SDL_Rect ground{ r.x + 1000, r.y + 900, r.w, 100 };

	SDL_Rect collider_rect{ 0, 0, r.w * 0.2, r.h * 0.2 };

	contact.x = 0;
	contact.y = 0;

	gravity = 1;

	return ret;
}

// Update: draw background
bool j1Player::PostUpdate()
{
	player_x_displacement = App->map->data.player_starting_value.x - position.x;

	speed.x = 0;
	speed.y = 2;

	if (dead)
	{
		position.x = App->map->data.player_starting_value.x;
		position.y = App->map->data.player_starting_value.y - 5;

		dead = false;
	}

	// Jump
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (contact.y == 1)
		{
			jumping = true;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (App->map->map != 0)
		{
			App->map->Load("Level1Test.tmx");
		}
		position.x = App->map->data.player_starting_value.x;
		position.y = App->map->data.player_starting_value.y - 5;
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		position.x = App->map->data.player_starting_value.x;
		position.y = App->map->data.player_starting_value.y - 5;
	}

	Jump();

	if (contact.y != 1)
		position.y += gravity;

	contact.x = 0;
	contact.y = 0;

	// Draw everything --------------------------------------
	//App->render->Blit(graphics, position.x, position.y, 0.3, &current_animation->GetCurrentFrame(), flip);

	// Set camera to follow the player
	App->render->camera.x = -position.x + 400;
	App->render->camera.y = -position.y + 400;

	//Put collider next to player

	return true;
}

void j1Player::Jump()
{
	// Jump
	if (jumping)
	{
		if (allowtime)
		{
			time = SDL_GetTicks();
			allowtime = false;
			contact.y = 0;
			App->audio->PlayFx(1);
		}

		if (SDL_GetTicks() - time <= 400 && contact.y == 0)
		{
			position.y -= speed.y;
		}
		else
		{
			jumping = false;
			allowtime = true;
		}

		if (contact.y == 1 && (contact.x == 1 || contact.x == 2))
		{
			jumping = false;
			allowtime = true;
		}
	}
}

bool j1Player::Update()
{
	// Move right
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		flip = false;

		if (contact.x != 2)
			speed.x = 1;
	}

	// Move left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		flip = true;

		if (contact.x != 1)
			speed.x = -1;
	}
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	position.x = data.child("player_position").attribute("x").as_float();
	position.y = data.child("player_position").attribute("y").as_float() - 3;

	return true;
}

// Save Game State
bool j1Player::Save(pugi::xml_node& data) const
{
	pugi::xml_node player = data.append_child("player_position");

	player.append_attribute("x") = position.x;
	player.append_attribute("y") = position.y;

	return true;
}