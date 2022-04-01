#pragma once
#include "GameEngine/GameEngineActor.h"

enum class InventoryTab
{
	Equipment,
	Useable,
	Etc,
};

// ���� : 
class Item;
class GameEngineCollision;
class GameEngineUIRenderer;
class InventoryUI : public GameEngineActor
{
public:
	InventoryUI();
	~InventoryUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	InventoryUI(const InventoryUI& _other) = delete;
	InventoryUI(InventoryUI&& _other) noexcept = delete;
	InventoryUI& operator=(const InventoryUI& _other) = delete;
	InventoryUI& operator=(const InventoryUI&& _other) = delete;

private:
	void CreateRenderer();

	void TitleBarEvent(GameEngineCollision* _OtherCollision);

	void ChangeTabEvent();

	void PushItem(InventoryTab _Category, Item* _Item);

	void EraseItem(InventoryTab _Category, int _Index);

	std::map<int, std::vector<Item*>> ItemList_;

	GameEngineCollision* TitleBar_;
	GameEngineCollision* ItemBlocks_[32];

	GameEngineUIRenderer* EquipmentRenderer_;
	GameEngineUIRenderer* UseableRenderer_;
	GameEngineUIRenderer* EtcRenderer_;

	GameEngineCollision* EquipmentTab_;
	GameEngineCollision* UseableTab_;
	GameEngineCollision* EtcTab_;

	InventoryTab EnabledTab_;
};

