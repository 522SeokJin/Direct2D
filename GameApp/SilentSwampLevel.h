#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class SilentSwampLevel : public GameEngineLevel
{
public:
	SilentSwampLevel();
	~SilentSwampLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	SilentSwampLevel(const SilentSwampLevel& _other) = delete; 
	SilentSwampLevel(SilentSwampLevel&& _other) noexcept = delete;
	SilentSwampLevel& operator=(const SilentSwampLevel& _other) = delete;
	SilentSwampLevel& operator=(const SilentSwampLevel&& _other) = delete;

private:

};

