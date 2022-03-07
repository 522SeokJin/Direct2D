#include "PreCompile.h"
#include "ItemUI.h"
#include <GameEngine/GameEngineImageUIRenderer.h>

void ItemUI::CreateRenderer()
{
	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.backgrnd.png");
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.backgrnd2.png");
		Renderer->SetLocalPosition({ 0.0f, -7.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.backgrnd3.png");
		Renderer->SetLocalPosition({ 0.5f, -3.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.Tab.enabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 0.0f * 30.0f, 154.0f });
	}

	{
		// disabled size diffrent -> y : 19 -> 17
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.Tab.disabled.1.png");
		Renderer->SetLocalPosition({ -75.0f + 1.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.Tab.disabled.2.png");
		Renderer->SetLocalPosition({ -75.0f + 2.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.Tab.disabled.3.png");
		Renderer->SetLocalPosition({ -75.0f + 3.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.Tab.disabled.4.png");
		Renderer->SetLocalPosition({ -75.0f + 4.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.Tab.disabled.5.png");
		Renderer->SetLocalPosition({ -75.0f + 5.0f * 30.0f, 154.0f - 1.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Coin.normal.0.png");
		Renderer->SetLocalPosition({ -69.0f, -125.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Point.disabled.0.png");
		Renderer->SetLocalPosition({ -48.0f, -143.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Disassemble.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 0.0f * 30.0f, -166.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Extract.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 1.0f * 30.0f, -166.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Appraise.normal.0.png");
		Renderer->SetLocalPosition({ -75.0f + 2.0f * 30.0f, -166.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_ProtectGreenZone.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 3.0f * 30.0f, -166.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.anibutton_Toad.disabled.0.png");
		Renderer->SetLocalPosition({ -75.0f + 4.0f * 30.0f, -166.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Upgrade.normal.0.png");
		Renderer->SetLocalPosition({ -74.5f + 5.0f * 30.0f, -166.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Full.normal.0.png");
		Renderer->SetLocalPosition({ 82.0f, -125.0f });
	}

	{
		GameEngineImageUIRenderer* Renderer = CreateTransformComponent<GameEngineImageUIRenderer>(GetTransform());
		Renderer->SetImage("Item.AutoBuild.button_Sort.normal.0.png");
		Renderer->SetLocalPosition({ 64.0f, -125.0f });
	}
}