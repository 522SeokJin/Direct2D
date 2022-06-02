#include "PreCompile.h"
#include "DeepeningForestLevel.h"
#include "Player.h"
#include "DeepeningForest.h"
#include "Mouse.h"

#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>
#include <GameEngine/GameEngineWindow.h>

#include "MenuUI.h"
#include "ExpBarUI.h"
#include "StatusUI.h"
#include "QuickSlotUI.h"
#include "QuickSlotKeyUI.h"
#include "InventoryUI.h"
#include "SkillUI.h"
#include "DeathNotice.h"

#include "ForestDefender.h"

DeepeningForestLevel::DeepeningForestLevel()
	: Cursor_(nullptr)
	, Player_(nullptr)
	, RenderWindow_(nullptr)
	, Inventory_(nullptr)
	, Map_(nullptr)
	, Skill_(nullptr)
	, Status_(nullptr)
	, ExpBar_(nullptr)
	, ReZenTime_(8.0f)
{
}

DeepeningForestLevel::~DeepeningForestLevel()
{
	for (auto& Monster : Monsters_)
	{
		Monster = nullptr;
	}
}

void DeepeningForestLevel::LevelStart()
{
	RenderWindow_ = GameEngineGUI::GetInst()->FindGUIWindowConvert
		<GameEngineRenderWindow>("RenderWindow");

	GetMainCamera()->SetProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		Map_ = CreateActor<DeepeningForest>();
		Map_->GetPixelCollideImage()->Off();
	}

	// Monster Respawn
	AddTimeEvent(ReZenTime_, std::bind(&DeepeningForestLevel::ReZenMoster, this));
}

void DeepeningForestLevel::LevelUpdate(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		CreateActorLevel();
		CreateActorCheck = true;
	}

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GlobalLevelControl::PlayerCameraControl();
	}

	static bool Check = false;

	if (false == Check && nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		RenderWindow_->ClearRenderTarget();

		float4 Size = GameEngineWindow::GetInst().GetSize() * 0.25f;

		RenderWindow_->PushRenderTarget("���� ī�޶� Ÿ��",
			GetMainCamera()->GetCameraRenderTarget(), Size);
		RenderWindow_->PushRenderTarget("UI ī�޶� Ÿ��",
			GetUICamera()->GetCameraRenderTarget(), Size);

		Check = true;
	}

	if (true == GameEngineInput::GetInst().Down("LevelControl"))
	{
		GameEngineGUIWindow* LevelControl = GameEngineGUI::GetInst()->FindGUIWindow("LevelControlWindow");
		LevelControl->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Down("MOn"))
	{
		RenderWindow_->On();
		Cursor_->WindowCursorOn();
	}

	if (true == GameEngineInput::GetInst().Down("MOff"))
	{
		RenderWindow_->Off();
		Cursor_->WindowCursorOff();
	}

	if (true == GameEngineInput::GetInst().Down("Inventory"))
	{
		Inventory_->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Down("Skill"))
	{
		Skill_->OnOffChange();
	}

	if (true == GameEngineInput::GetInst().Down("DebugColOn"))
	{
		GetMainCamera()->DebugOn();
		GetUICamera()->DebugOn();
	}

	if (true == GameEngineInput::GetInst().Down("DebugColOff"))
	{
		GetMainCamera()->DebugOff();
		GetUICamera()->DebugOff();
	}

	if (true == GameEngineInput::GetInst().Down("PixelCollide"))
	{
		Map_->GetPixelCollideImage()->OnOffChange();
	}
}

void DeepeningForestLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{

}

void DeepeningForestLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{

}

void DeepeningForestLevel::CreateActorLevel()
{
	{
		Cursor_ = CreateActor<Mouse>();
	}

	{
		Status_ = CreateActor<StatusUI>();
		Status_->GetTransform()->SetWorldPosition({ 5.0f, 45.0f - GameEngineWindow::GetInst().GetSize().hy() });

		ExpBar_ = CreateActor<ExpBarUI>();
		ExpBar_->GetTransform()->SetWorldPosition(float4(0.0f, 12.0f - GameEngineWindow::GetInst().GetSize().hy()));
		ExpBar_->LinkStatus(Status_);
	}

	{
		MenuUI* Actor = CreateActor<MenuUI>();
		Actor->GetTransform()->SetWorldPosition({ 133.0f, -355.5f });
	}

	{
		QuickSlotUI* Actor = CreateActor<QuickSlotUI>();
		Actor->GetTransform()->SetWorldPosition({ 617.0f, -337.5f });
	}

	{
		QuickSlotKeyUI* Actor = CreateActor<QuickSlotKeyUI>();
		Actor->GetTransform()->SetWorldPosition({ 338.5f, -310.0f });
	}

	{
		Skill_ = CreateActor<SkillUI>();
		Skill_->GetTransform()->SetWorldPosition({ 200.0f, 200.0f });
		Skill_->Off();
	}

	{
		Inventory_ = CreateActor<InventoryUI>();
		Inventory_->GetTransform()->SetWorldPosition({ -200.0f, 0.0f });
		Inventory_->Off();
	}
	
	{
		DeathNotice* Notice = CreateActor<DeathNotice>();
		Notice->GetTransform()->SetWorldPosition({ -0.0f, 0.0f });
	}

	{
		Player_ = CreateActor<Player>();
		GetMainCameraActor()->GetTransform()->SetWorldPosition(
			Player_->GetTransform()->GetLocalPosition());
		Player_->GetTransform()->SetWorldPosition({ 179.0f, -758.0f });
		Player_->Off();
	}

	CreateMonster();

	GlobalValue::CurrentPlayer = Player_;
	GlobalValue::CurrentMouse = Cursor_;
	GlobalValue::CurrentStatusUI = Status_;
	GlobalValue::CurrentExpBarUI = ExpBar_;
	GlobalValue::CurrentInventoryUI = Inventory_;

	Player_->On();
}

void DeepeningForestLevel::CreateMonster()
{

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 379.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 670.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 985.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1355.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1700.0f, -756.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}

	// 2F

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 600.0f, -574.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 845.0f, -574.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1631.0f, -551.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	// 3F

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 644.0f, -398.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1471.0f, -313.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}	

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 1722.0f, -313.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
	
	// 4F

	{
		ForestDefender* Actor = CreateActor<ForestDefender>();
		Actor->SetWorldPosition({ 483.0f, -240.0f, static_cast<float>(DepthOrder::MONSTER) });
		Monsters_.push_back(Actor);
	}
}

void DeepeningForestLevel::ReZenMoster()
{
	for (auto& Monster : Monsters_)
	{
		if (true == Monster->IsUpdate())
		{
			continue;
		}

		Monster->Reset();
	}

	AddTimeEvent(ReZenTime_, std::bind(&DeepeningForestLevel::ReZenMoster, this));
}