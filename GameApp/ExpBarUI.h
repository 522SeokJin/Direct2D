#pragma once
#include "GameEngine/GameEngineActor.h"

// ���� : 
class ExpBarUI : public GameEngineActor
{
public:
	ExpBarUI();
	~ExpBarUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	ExpBarUI(const ExpBarUI& _other) = delete; 
	ExpBarUI(ExpBarUI&& _other) noexcept = delete;
	ExpBarUI& operator=(const ExpBarUI& _other) = delete;
	ExpBarUI& operator=(const ExpBarUI&& _other) = delete;

private:

};
