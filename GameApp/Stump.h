#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>

#define DIRRIGHT (5 < Dir_)
#define DIRLEFT (5 >= Dir_)

// 설명 : 
class SmallMeso;
class RedPotion;
class BluePotion;
class GameEngineImageRenderer;
class GameEngineCollision;
class Stump : public GameEngineActor
{
public:
	Stump();
	~Stump();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetWorldPosition(const float4& _Value);
	void Reset();

protected:
	Stump(const Stump& _other) = delete; 
	Stump(Stump&& _other) noexcept = delete;
	Stump& operator=(const Stump& _other) = delete;
	Stump& operator=(const Stump&& _other) = delete;

private:
	void SkillEvent(GameEngineCollision* _OtherCollision);

	GameEngineFSM FSM_;
	GameEngineRandom Random_;
	int	Dir_;						// 5 < Dir_ : Right
	float MoveTime_;

	bool Hit_;
	bool Die_;

	GameEngineImageRenderer* Renderer_;
	GameEngineImageRenderer* SkillEffectRenderer_;
	GameEngineCollision*	 Collision_;

	// Number Image
	std::map<int, std::vector<GameEngineImageRenderer*>> DmgNumber_[5];	// [최대타수]
	int MaxHitCount_;
	int CurHitCount_;
	float HitTime_;
	
	int DeadHitCount_;

	float4 OriginPos_;

	SmallMeso* Meso_;	// 0~3
	RedPotion*  RedPotion_;	// 4~6 
	BluePotion* BluePotion_;	// 7~9

	int RandomItemSelect_;

	////////////////////////////////////////////	FSM

	std::function<void(GameEngineCollision*)> Func_;

private:
	void stand_Start();
	void stand();
	void stand_End();

	void move_Start();
	void move();
	void move_End();

	void hit_Start();
	void hit();
	void hit_End();

	void die_Start();
	void die();
	void die_End();
};

