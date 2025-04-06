#pragma once

#include "raylib.h"
#include "raymath.h"
#include "Entity.h"
#include "Weapon.h"
#include "Collider.h"
#include "Inventory.h"
#include "Item.h"
#include "Button.h"
#include "HealthPotion.h"
#include "Projectile.h"

#include <iostream>
#include <string>
#include <math.h>

enum GameState
{
	MAIN_MENU,
	IN_GAME,
	DEATH_SCREEN
};

enum MenuState
{
	DEFAULT,
	STATS,
	SETTINGS
};

class Game
{
public:
	// Initiate
	Game();
	~Game();

	// Game loop functions
	void Start();
	void UpdateGameplay();
	void UpdateMainMenu();
	void Render();
	void Input();
	void RenderUI();
	void RenderMainMenu();

	// Render
	void RenderBackground();

	// Debug
	template <typename T> void Log(T input);
	void DrawDebugText();

	// Get
	Camera2D GetCamera();

	// Camera functions
	void UpdateCamera();

	// Collision
	void ProcessCollisions();
	bool OnCollision(Collider first, Collider other);

	// AI
	Vector2 MoveToPos(Vector2 self, Vector2 target, double speed);
	void ReviveEnemiesUponDeath();
	void BoidManager();
	void PreventOverlap(Entity& e1, Entity& e2);

	// Weapons
	void WeaponInit();

	// Inventory and Items
	void ItemInit();
	void UpdateInventory();
	void RewardItemOnKill();
	void UseItem(int slot);

	// Enemy
	void EnemyInit();
	void UpdateEnemies();

	// Math
	float DistanceBetweenVectors(Vector2 v1, Vector2 v2);

	// State machine
	GameState gameCurrentState{ MAIN_MENU };
	MenuState menuCurrentState{ DEFAULT };
	bool hasQuitGame{};

private:
	// Camera
	Camera2D camera{ 0 };

	// Entity
	Entity player{};
	std::vector<Entity> enemies{ 6 };

	// Weapons
	Weapon* currentWeaponPtr{};
	// Wooden Blade
	Weapon woodenSword{};
	Texture2D woodenSwordSprite{};
	// Steel Blade
	Weapon steelSword{};
	Texture2D steelSwordSprite{};
	// Dark Blade
	Weapon darkBlade{};
	Texture2D darkBladeSprite{};
	// Demon Book
	Weapon demonBook{};
	Texture2D demonBookSprite{};
	Texture2D demonBookProjSprite{};

	// Projectiles
	std::vector<Projectile> projectiles{ 64 };
	int projectileCounter{};

	// Textures
	Texture2D floor{};

	// Player
	Texture2D player_front{};
	Texture2D player_back{};
	Texture2D player_left{};
	Texture2D player_right{};

	// Enemy
	Texture2D cheese_front{};
	Texture2D cheese_back{};
	Texture2D cheese_left{};
	Texture2D cheese_right{};

	// UI
	Texture2D titleScreenLogo{};
	Texture2D titleScreenArt{};
	Texture2D backdropUI{};
	Texture2D heart_UI;

	// Buttons
	Button playButton{ "PLAY", 28, 144, 48, Vector2{ 0, 300} };
	Button statsButton{ "STATS", 28, 144, 48, Vector2{0, 350} };
	Button optionsButton{ "OPTIONS", 28, 144, 48, Vector2{0, 400} };
	Button quitButton{ "QUIT", 28, 144, 48, Vector2{ 0, 450} };
	Button closePanelButton{ "CLOSE", 28, 144, 48, Vector2{ 600 , 675 } };
	Button debugButton{ "DEBUG", 28, 144, 48, Vector2{ 625, 0 } };
	Button closeDebugButton{ "HIDE", 28, 144, 48, Vector2{ 625, 50 } };

	// Menu Stuff
	bool isStatsOpen{};
	bool isOptionsOpen{};
	bool isDebugMenuOpen{};

	// Inventory
	Inventory playerInventory{};
	std::vector<Item> itemsInInventory{};
	std::vector<Item> itemsInScene{};
	std::vector<Weapon> playerCurrentWeapon{};
	bool itemPickupDisabled{ false };

	// Item
	Item healthPotion{};
	Item speedPotion{};
	HealthPotion testHealthPotion{};

	int score{};
};
