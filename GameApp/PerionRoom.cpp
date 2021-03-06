#include "PreCompile.h"
#include "PerionRoom.h"
#include <GameEngine/GameEngineImageRenderer.h>

PerionRoom::PerionRoom()
{

}

PerionRoom::~PerionRoom()
{

}

void PerionRoom::Start()
{
	{
		MapImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		MapImage_->CreateAnimationFolder("PerionRoom", 0.4f);
		MapImage_->SetChangeAnimation("PerionRoom");
		MapImage_->GetTransform()->SetLocalPosition({400.0f, -300.0f});
		MapImage_->SetLocalMove({0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) });
	}

	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
		Renderer->SetImage("blackimage.png");
		Renderer->GetTransform()->SetLocalPosition(MapImage_->GetImageSize().halffloat4().InvertY());
		Renderer->SetLocalMove({ 0.0f, 0.0f, static_cast<float>(DepthOrder::MAP) + 1.0f });
	}

	{
		PixelCollideImage_ = CreateTransformComponent<GameEngineImageRenderer>();
		PixelCollideImage_->SetImage("20220406190451543_102000003.png");
		PixelCollideImage_->GetTransform()->SetLocalPosition(PixelCollideImage_->GetImageSize().halffloat4().InvertY());
		PixelCollideImage_->SetAlpha(0.5f);
	}
}

void PerionRoom::Update(float _DeltaTime)
{
}

void PerionRoom::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	SetCurrentMap(this);
}

