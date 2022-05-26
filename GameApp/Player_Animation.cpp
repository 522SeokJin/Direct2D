#include "PreCompile.h"
#include "Player.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player_Define.h"

void Player::CreateAnimation()
{
	Avatar_ = CreateTransformComponent<GameEngineImageRenderer>();

	LevelUpEffect_ = CreateTransformComponent<GameEngineImageRenderer>();
	LevelUpEffect_->SetLocalPosition({0.0f, 160.0f, static_cast<float>(DepthOrder::SKILL)});
	JobsChangedEffect_ = CreateTransformComponent<GameEngineImageRenderer>();
	JobsChangedEffect_->SetLocalPosition({ 0.0f, 182.5f, static_cast<float>(DepthOrder::SKILL)});

	LevelUpEffect_->CreateAnimationFolder("LevelUp", 0.09f, false);
	JobsChangedEffect_->CreateAnimationFolder("JobChanged", 0.1f, false);

	LevelUpEffect_->SetChangeAnimation("LevelUp");
	LevelUpEffect_->AnimationStop();
	JobsChangedEffect_->SetChangeAnimation("JobChanged");
	JobsChangedEffect_->AnimationStop();

	LevelUpEffect_->Off();
	JobsChangedEffect_->Off();

	LevelUpEffect_->SetEndCallBack("LevelUp", [&]()
		{
			LevelUpEffect_->AnimationStop();
			LevelUpEffect_->Off();
		}
	);

	JobsChangedEffect_->SetEndCallBack("JobChanged", [&]() 
		{ 
			JobsChangedEffect_->AnimationStop();
			JobsChangedEffect_->Off();
		}
	);

	Avatar_->CreateAnimationFolder("avatar_dead", "dead", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_jump", "jump", 0.5f, false);
	Avatar_->CreateAnimationFolder("avatar_ladder", "ladder", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_prone", "prone", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_proneStab", "proneStab", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_rope", "rope", 0.25f);
	Avatar_->CreateAnimationFolder("avatar_stabO1", "stabO1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabO2", "stabO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stabOF", "stabOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_stand1", "stand1", 0.5f);

	Avatar_->CreateAnimationFolder("avatar_swingO1", "swingO1", { 0.3f, 0.15f, 0.35f }, false);	// 300 150 350

	Avatar_->CreateAnimationFolder("avatar_swingO2", "swingO2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingO3", "swingO3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingOF", "swingOF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingP2", "swingP2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingPF", "swingPF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT1", "swingT1", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT2", "swingT2", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingT3", "swingT3", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_swingTF", "swingTF", 0.5f);
	Avatar_->CreateAnimationFolder("avatar_walk1", "walk1", 0.180f);

	// Skill Animation
	Avatar_->CreateAnimationFolder("slashBlast", 0.180f);

	// animation frame별 웨잇 설정기능 필요

	Avatar_->SetChangeAnimation("stand1");
}
