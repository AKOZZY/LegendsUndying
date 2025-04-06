#include "Game.h"

Game::Game()
{
	Start();
}

Game::~Game()
{
	// Unload textures
	UnloadTexture(floor);
	UnloadTexture(woodenSwordSprite);
	UnloadTexture(heart_UI);
	UnloadTexture(titleScreenLogo);
	UnloadTexture(backdropUI);

	Log("Unloaded Textures");
}

void Game::Start()
{
	floor = LoadTexture("Assets/FloorTexture.png");

	// Init Player
	player.UpdatePosition(Vector2{ 400, 400 });
	player_front = LoadTexture("Assets/Player_Front.png");
	player_back = LoadTexture("Assets/Player_Back.png");
	player_left = LoadTexture("Assets/Player_Left.png");
	player_right = LoadTexture("Assets/Player_Right.png");
	player.current_sprite = player_front;

	// Load enemy sprites
	cheese_left = LoadTexture("Assets/FlyingEyeBall_L.png");
	cheese_right = LoadTexture("Assets/FlyingEyeBall_R.png");

	// Load UI
	heart_UI = LoadTexture("Assets/Heart.png");

	player.LoadSprites(player_front, player_back, player_left, player_right);
	player.speed = 100;

	// Init weapons
	WeaponInit();

	// Init items
	ItemInit();

	// Init enemies
	EnemyInit();

	titleScreenLogo = LoadTexture("Assets/TitleScreenLogo.png");
	titleScreenArt = LoadTexture("Assets/TitleScreenArt.png");
	backdropUI = LoadTexture("Assets/Backdrop.png");
}

void Game::UpdateGameplay()
{
	UpdateCamera();
	ProcessCollisions();

	UpdateEnemies();

	player.InvisibilityFrames();
	player.CheckIfDead();

	UpdateInventory();

	ReviveEnemiesUponDeath();

	BoidManager();

	if (IsKeyDown(KEY_Z)) currentWeaponPtr = &woodenSword;
	if (IsKeyDown(KEY_X)) currentWeaponPtr = &steelSword;
	if (IsKeyDown(KEY_C)) currentWeaponPtr = &darkBlade;
	if (IsKeyDown(KEY_V)) currentWeaponPtr = &demonBook;

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].isActive)
		{
			projectiles[i].Move();
		}
		else
		{
			projectiles[i].position = player.position;
			projectiles[i].collider.UpdatePosition(player.position);
		}
	}

	debugButton.MouseHover(GetMousePosition());
	if (debugButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		isDebugMenuOpen = true;
	}

	closeDebugButton.MouseHover(GetMousePosition());
	if (closeDebugButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isDebugMenuOpen)
	{
		isDebugMenuOpen = false;
	}
}

void Game::UpdateMainMenu()
{
	// camera
	camera.zoom = 1.0f;

	// play button
	playButton.MouseHover(GetMousePosition());
	if (playButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		gameCurrentState = IN_GAME;
	}

	// stats button
	statsButton.MouseHover(GetMousePosition());
	if (statsButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		menuCurrentState = STATS;
	}

	// options button
	optionsButton.MouseHover(GetMousePosition());
	if (optionsButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		menuCurrentState = SETTINGS;
	}

	// quit button
	quitButton.MouseHover(GetMousePosition());
	if (quitButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		hasQuitGame = true;
	}

	// close panel button
	closePanelButton.MouseHover(GetMousePosition());
	if (closePanelButton.isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		menuCurrentState = DEFAULT;
	}
}

void Game::Render()
{
	RenderBackground();
	
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].DrawSprite();
	}

	player.DrawSprite();

	if (IsKeyDown(KEY_UP))
	{
		currentWeaponPtr->DrawWeapon(player.position, Vector2{0, -1});
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		currentWeaponPtr->DrawWeapon(player.position, Vector2{ 0, 1 });
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		currentWeaponPtr->DrawWeapon(player.position, Vector2{ -1, 0 });
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		currentWeaponPtr->DrawWeapon(player.position, Vector2{ 1, 0 });
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].isActive)
		{
			projectiles[i].Draw();
		}
	}
}

void Game::Input()
{
	// Player Input
	if (IsKeyDown(KEY_W)) player.position.y -= player.speed * GetFrameTime(), player.direction = Vector2{ 0 , -1 };
	if (IsKeyDown(KEY_A)) player.position.x -= player.speed * GetFrameTime(), player.direction = Vector2{ -1 , 0 };
	if (IsKeyDown(KEY_S)) player.position.y += player.speed * GetFrameTime(), player.direction = Vector2{ 0 , 1 };
	if (IsKeyDown(KEY_D)) player.position.x += player.speed * GetFrameTime(), player.direction = Vector2{ 1 , 0 };

	// Check Weapon Type
	if (currentWeaponPtr->weaponType == MELEE)
	{
		if (IsKeyDown(KEY_UP))
		{
			currentWeaponPtr->collider.Enable();
			currentWeaponPtr->collider.UpdatePosition(Vector2{ player.position.x, player.position.y - 16 });
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			currentWeaponPtr->collider.Enable();
			currentWeaponPtr->collider.UpdatePosition(Vector2{ player.position.x, player.position.y + 16});
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			currentWeaponPtr->collider.Enable();
			currentWeaponPtr->collider.UpdatePosition(Vector2{ player.position.x - 16, player.position.y });
		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			currentWeaponPtr->collider.Enable();
			currentWeaponPtr->collider.UpdatePosition(Vector2{ player.position.x + 16, player.position.y });
		}
		else
		{
			currentWeaponPtr->collider.Disable();
		}
	}
	else if (currentWeaponPtr->weaponType == MAGIC)
	{
		if (IsKeyPressed(KEY_UP))
		{
			if (projectileCounter < 63)
			{
				projectileCounter++;
			}
			else
			{
				projectileCounter = 0;
			}

			projectiles[projectileCounter].sprite = currentWeaponPtr->GetProjectileSprite();
			projectiles[projectileCounter].isActive = true;
			projectiles[projectileCounter].damage = currentWeaponPtr->weaponDamage;
			projectiles[projectileCounter].position = player.position;
			projectiles[projectileCounter].firedDirection = Vector2{ 0, -1 };

			
		}
		else if (IsKeyPressed(KEY_DOWN))
		{
			if (projectileCounter < 63)
			{
				projectileCounter++;
			}
			else
			{
				projectileCounter = 0;
			}

			projectiles[projectileCounter].sprite = currentWeaponPtr->GetProjectileSprite();
			projectiles[projectileCounter].isActive = true;
			projectiles[projectileCounter].damage = currentWeaponPtr->weaponDamage;
			projectiles[projectileCounter].position = player.position;
			projectiles[projectileCounter].firedDirection = Vector2{ 0, 1 };
			
		}
		else if (IsKeyPressed(KEY_LEFT))
		{
			if (projectileCounter < 63)
			{
				projectileCounter++;
			}
			else
			{
				projectileCounter = 0;
			}

			projectiles[projectileCounter].sprite = currentWeaponPtr->GetProjectileSprite();
			projectiles[projectileCounter].isActive = true;
			projectiles[projectileCounter].damage = currentWeaponPtr->weaponDamage;
			projectiles[projectileCounter].position = player.position;
			projectiles[projectileCounter].firedDirection = Vector2{ -1, 0 };

			
		}
		else if (IsKeyPressed(KEY_RIGHT))
		{
			if (projectileCounter < 63)
			{
				projectileCounter++;
			}
			else
			{
				projectileCounter = 0;
			}

			projectiles[projectileCounter].sprite = currentWeaponPtr->GetProjectileSprite();
			projectiles[projectileCounter].isActive = true;
			projectiles[projectileCounter].damage = currentWeaponPtr->weaponDamage;
			projectiles[projectileCounter].position = player.position;
			projectiles[projectileCounter].firedDirection = Vector2{ 1, 0 };
		}
	}

	// Item Usage
	if (IsKeyPressed(KEY_ONE)) UseItem(0);
	if (IsKeyPressed(KEY_TWO)) UseItem(1);
	if (IsKeyPressed(KEY_THREE)) UseItem(2);
	if (IsKeyPressed(KEY_FOUR)) UseItem(3);
	if (IsKeyPressed(KEY_FIVE)) UseItem(4);
}

void Game::RenderUI()
{
	// Player hearts
	for (int i = 0; i < player.hp; i++)
	{
		float x = i * 50;
		DrawTextureEx(heart_UI, Vector2{ x, 680 }, 0, 3, WHITE);
	}

	// Inventory
	playerInventory.RenderInventory();
	playerInventory.RenderItemsInInventory(itemsInInventory);
	playerInventory.RenderWeaponSlot();
	DrawTextureEx(currentWeaponPtr->GetWeaponSprite(), Vector2{ 768 , 735 }, 45, 3, WHITE);

	// Debug Button
	debugButton.Draw();

	// Debug
	if (isDebugMenuOpen)
	{
		DrawDebugText();
		closeDebugButton.Draw();
	}
}

void Game::RenderMainMenu()
{
	// draw play button
	playButton.Draw();
	statsButton.Draw();
	optionsButton.Draw();
	quitButton.Draw();
	
	// Draw title screen logo with other images
	DrawTextureEx(titleScreenLogo, Vector2{ 0, 0 }, 0, 5, WHITE);
	DrawTextureEx(titleScreenArt, Vector2{ 0, 480 }, 0, 4, WHITE);

	switch (menuCurrentState)
	{
	case DEFAULT:

		break;
	case STATS:

		DrawTextureEx(backdropUI, Vector2{ 280, 315 }, 0, 3.5, WHITE);
		DrawText("MY STATS: ", 300, 325, 24, Color{ 251, 247, 160, 255 });
		closePanelButton.Draw();

		break;
	case SETTINGS:

		DrawTextureEx(backdropUI, Vector2{ 280, 315 }, 0, 3.5, WHITE);
		DrawText("OPTIONS: ", 300, 325, 24, Color{ 251, 247, 160, 255 });
		closePanelButton.Draw();

		break;
	default:
		break;
	}
}

void Game::RenderBackground()
{
	int row{ 24 }, col{ 24 };

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int x = j * 32;
			int y = i * 32;
			DrawTexture(floor, x, y, WHITE);
		}
	}
}

template <typename T> void Game::Log(T input)
{
	std::cout << input << std::endl;
}

void Game::DrawDebugText()
{
	DrawText("Debug: ", 0, 300, 20, WHITE);
	DrawText(TextFormat("Kills: %i", score), 0, 330, 20, WHITE);
	DrawText(TextFormat("Health: %i", player.hp), 0, 360, 20, WHITE);
	DrawText(TextFormat("Speed: %i", (int)player.speed), 0, 390, 20, WHITE);
	DrawText(("Current Weapon: " + currentWeaponPtr->weaponName).c_str(), 0, 420, 20, WHITE);
	DrawText(TextFormat("Weapon Damage: %i", (int)currentWeaponPtr->weaponDamage), 0, 450, 20, WHITE);
}

Camera2D Game::GetCamera()
{
	return camera;
}

void Game::UpdateCamera()
{
	// default = 2.5f
	camera.zoom = 2;

	camera.offset.x = player.position.x;
	camera.offset.y = player.position.y;

	camera.target.x = player.position.x;
	camera.target.y = player.position.y;
}

void Game::ProcessCollisions()
{
	// Check collisions between enemy and player and enemy and weapon/projectiles
	for (int i = 0; i < enemies.size(); i++)
	{
		if (OnCollision(player.collider, enemies[i].collider) && player.canBeHurt)
		{
			player.Hurt(1);
		}

		if (OnCollision(enemies[i].collider, currentWeaponPtr->collider) && enemies[i].canBeHurt)
		{
			enemies[i].Hurt(currentWeaponPtr->weaponDamage);
		}
		enemies[i].collider.UpdatePosition(enemies[i].position);
	}

	// Prevent enemies from overlapping eachother
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < enemies.size(); j++)
		{
			if (OnCollision(enemies[i].collider, enemies[j].collider))
			{
				PreventOverlap(enemies[i], enemies[j]);
			}
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < projectiles.size(); j++) 
		{
			if (OnCollision(enemies[i].collider, projectiles[j].collider) && projectiles[j].isActive)
			{
				projectiles[j].isActive = false;
				enemies[i].Hurt(projectiles[j].damage);
			}
		}
	}

	player.collider.UpdatePosition(player.position);
}

bool Game::OnCollision(Collider first, Collider other)
{
	if (first.canCollide && other.canCollide)
	{
		if (first.GetPosition().x < other.GetPosition().x + other.GetWidth() &&
			first.GetPosition().x + first.GetWidth() > other.GetPosition().x &&
			first.GetPosition().y < other.GetPosition().y + other.GetHeight() &&
			first.GetPosition().y + first.GetHeight() > other.GetPosition().y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

Vector2 Game::MoveToPos(Vector2 self, Vector2 target, double speed)
{
	if (self.x > target.x) self.x -= speed * GetFrameTime();
	else self.x += speed * GetFrameTime();

	if (self.y > target.y) self.y -= speed * GetFrameTime();
	else self.y += speed * GetFrameTime();

	return Vector2{ self.x, self.y };
}

void Game::ReviveEnemiesUponDeath()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isDead)
		{
			int randNum = GetRandomValue(1, 4);

			enemies[i].Revive();

			if (randNum == 1) enemies[i].UpdatePosition(Vector2{ (float)GetRandomValue(0, 800), 0 });
			if (randNum == 2) enemies[i].UpdatePosition(Vector2{ 0, (float)GetRandomValue(0, 800) });
			if (randNum == 3) enemies[i].UpdatePosition(Vector2{ (float)GetRandomValue(0, 800), 800 });
			if (randNum == 4) enemies[i].UpdatePosition(Vector2{ 800, (float)GetRandomValue(0, 800) });
			
			enemies[i].collider.UpdatePosition(enemies[i].position);
			enemies[i].collider.Enable();

			score++;
			Log(score);

			if (GetRandomValue(0, 2) == 1)
			{
				RewardItemOnKill();
			}
		}
	}
}

void Game::BoidManager()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < enemies.size(); j++)
		{
			if (DistanceBetweenVectors(enemies[i].position, enemies[j].position) > 10)
			{
				enemies[i].position.x += -enemies[i].speed * enemies[j].position.x * GetFrameTime();
				enemies[i].position.y += -enemies[i].speed * enemies[j].position.y * GetFrameTime();
			}
		}
	}
}

void Game::PreventOverlap(Entity& e1, Entity& e2)
{
	float overlapX = std::min(e1.position.x + e1.width, e2.position.x + e2.width) - std::max(e1.position.x, e2.position.x);
	float overlapY = std::min(e1.position.y + e1.height, e2.position.y + e2.height) - std::max(e1.position.y, e2.position.y);

	if (overlapX < overlapY) 
	{
		if (e1.position.x < e2.position.x) 
		{
			e1.position.x -= overlapX / 2;
			e2.position.x += overlapX / 2;
		}
		else 
		{
			e1.position.x += overlapX / 2;
			e2.position.x -= overlapX / 2;
		}
	}
	else 
	{
		if (e1.position.y < e2.position.y) 
		{
			e1.position.y -= overlapY / 2;
			e2.position.y += overlapY / 2;
		}
		else 
		{
			e1.position.y += overlapY / 2;
			e2.position.y -= overlapY / 2;
		}
	}
}

void Game::WeaponInit()
{
	// Init Wooden Blade
	woodenSwordSprite = LoadTexture("Assets/BasicSword.png");
	woodenSword.SetWeaponSprite(woodenSwordSprite);
	woodenSword.weaponType = MELEE;
	woodenSword.weaponName = "Wooden Sword";
	woodenSword.weaponDamage = 1;

	// Init Steel Blade
	steelSwordSprite = LoadTexture("Assets/SteelSword.png");
	steelSword.SetWeaponSprite(steelSwordSprite);
	steelSword.weaponType = MELEE;
	steelSword.weaponName = "Steel Sword";
	steelSword.weaponDamage = 2;

	// Init Dark Blade
	darkBladeSprite = LoadTexture("Assets/DarkBlade.png");
	darkBlade.SetWeaponSprite(darkBladeSprite);
	darkBlade.weaponType = MELEE;
	darkBlade.weaponName = "Dark Blade";
	darkBlade.weaponDamage = 3;

	// Init Demon Book
	demonBookSprite = LoadTexture("Assets/DemonBook.png");
	demonBookProjSprite = LoadTexture("Assets/BlueFireball.png");
	demonBook.SetWeaponSprite(demonBookSprite);
	demonBook.SetProjectileSprite(demonBookProjSprite);
	demonBook.weaponType = MAGIC;
	demonBook.weaponName = "Demonic Tome";
	demonBook.weaponDamage = 1;

	// Set Default Weapon
	currentWeaponPtr = &woodenSword;
}

void Game::ItemInit()
{
	healthPotion.SetItemSprite(LoadTexture("Assets/HealthPotion.png"));
	healthPotion.itemName = "HEALTH_POTION";

	speedPotion.SetItemSprite(LoadTexture("Assets/SpeedPotion.png"));
	speedPotion.itemName = "SPEED_POTION";

	itemsInScene.push_back(healthPotion);
	itemsInScene.push_back(speedPotion);
}

void Game::UpdateInventory()
{
	if (itemsInInventory.size() > 4)
	{
		itemPickupDisabled = true;
	}
	else
	{
		itemPickupDisabled = false;
	}
}

void Game::RewardItemOnKill()
{
	if (!itemPickupDisabled)
	{
		Item reward = itemsInScene[GetRandomValue(0, itemsInScene.size() - 1)];
		itemsInInventory.push_back(reward);
	}
}


void Game::UseItem(int slot)
{
	if (itemsInInventory.size() > slot)
	{
		if (itemsInInventory[slot].itemName == "HEALTH_POTION")
		{
			if (player.hp != 6)
			{
				player.hp++;
				itemsInInventory.erase(itemsInInventory.begin() + slot);
			}		
		}
		else if(itemsInInventory[slot].itemName == "SPEED_POTION")
		{
			player.speed += 5;
			itemsInInventory.erase(itemsInInventory.begin() + slot);
		}
	}
}

void Game::EnemyInit()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		int randNum = GetRandomValue(1, 4);

		enemies[i].right_sprite = cheese_right;
		enemies[i].left_sprite = cheese_left;
		enemies[i].current_sprite = cheese_right;

		if (randNum == 1) enemies[i].UpdatePosition(Vector2{ (float)GetRandomValue(0, 800), 0 });
		if (randNum == 2) enemies[i].UpdatePosition(Vector2{ 0, (float)GetRandomValue(0, 800) });
		if (randNum == 3) enemies[i].UpdatePosition(Vector2{ (float)GetRandomValue(0, 800), 800 });
		if (randNum == 4) enemies[i].UpdatePosition(Vector2{ 800, (float)GetRandomValue(0, 800) });

		enemies[i].collider.UpdatePosition(enemies[i].position);
	}
}

void Game::UpdateEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].UpdatePosition(Vector2MoveTowards(enemies[i].position, player.position, 60 * GetFrameTime()));

		enemies[i].InvisibilityFrames();
		enemies[i].CheckIfDead();

		if (enemies[i].position.x > player.position.x) enemies[i].current_sprite = enemies[i].left_sprite;
		else enemies[i].current_sprite = enemies[i].right_sprite;

		if (enemies[i].isDead)
		{
			enemies[i].collider.Disable();
		}
	}
}

float Game::DistanceBetweenVectors(Vector2 v1, Vector2 v2)
{
	float a = v1.x - v2.x;
	float b = v1.y - v2.y;

	a = a * a;
	b = b * b;

	float c = a + b;

	return sqrt(c);
}
