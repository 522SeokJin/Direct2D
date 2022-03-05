#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class SahelLevel : public GameEngineLevel
{
public:
	SahelLevel();
	~SahelLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

protected:
	SahelLevel(const SahelLevel& _other) = delete; 
	SahelLevel(SahelLevel&& _other) noexcept = delete;
	SahelLevel& operator=(const SahelLevel& _other) = delete;
	SahelLevel& operator=(const SahelLevel&& _other) = delete;

private:

};

