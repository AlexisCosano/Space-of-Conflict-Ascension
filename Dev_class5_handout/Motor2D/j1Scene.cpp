#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Scene.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

 // Called before the first frame
bool j1Scene::Start()
{	
	player = App->player;
	player->SetTexture(App->tex->Load("textures/placeholder.png"), App->tex->Load("textures/godmode.png"));
	player->position = App->map->current_spawn_point;

	offset.x = 50;
	offset.y = 50;

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		LoadDesiredMap(1);
		player->position = App->map->current_spawn_point;
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		player->position = App->map->current_spawn_point;
	}

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		App->map->ShowHiddenLayers = !App->map->ShowHiddenLayers;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if(App->player->god_mode == false)
			App->player->god_mode = true;
		else
			App->player->god_mode = false;
	}

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 10;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 10;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 10;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 10;

	App->render->camera.x = ((-player->position.x * App->win->GetScale()) + (offset.x * App->win->GetScale()));
	App->render->camera.y = ((-player->position.y * App->win->GetScale()) + (offset.y * App->win->GetScale()));

	App->map->Draw();

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());

	App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (to_load)
	{
		App->map->Unload();
		App->map->Load(map_to_load);
		player->position = App->map->current_spawn_point;
		to_load = false;
	}

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void j1Scene::LoadDesiredMap(int map_id)
{
	to_load = true;

	if (map_id == 1)
	{
		map_to_load = "level1Test.tmx";
	}
	else
	{
		map_to_load = "level2Test.tmx";
	}
}