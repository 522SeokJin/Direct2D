#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class Mouse;
class Player;
class GameEngineRenderWindow;
class InventoryUI;
class PerionNorthernRidgeLevel : public GameEngineLevel
{
public:
	PerionNorthernRidgeLevel();
	~PerionNorthernRidgeLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	PerionNorthernRidgeLevel(const PerionNorthernRidgeLevel& _other) = delete; 
	PerionNorthernRidgeLevel(PerionNorthernRidgeLevel&& _other) noexcept = delete;
	PerionNorthernRidgeLevel& operator=(const PerionNorthernRidgeLevel& _other) = delete;
	PerionNorthernRidgeLevel& operator=(const PerionNorthernRidgeLevel&& _other) = delete;

private:
	Mouse* Cursor_;
	Player* Player_;
	GameEngineRenderWindow* RenderWindow_;
	InventoryUI* Inventory_;
};

