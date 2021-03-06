#include "PreCompile.h"
#include "GameEngineSoundPlayer.h"
#include "GameEngineSound.h"
#include "GameEngineDebug.h"


// Static Var
// Static Func

// constructer destructer
GameEngineSoundPlayer::GameEngineSoundPlayer()
	: playSoundFile_(nullptr)
	, playChannel_(nullptr)
	, PlayCount(-1)
	, Volume_(1.0f)
{
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept
	: playSoundFile_(_other.playSoundFile_)
	, playChannel_(_other.playChannel_)
	, PlayCount(_other.PlayCount)
{
}

//member Func

bool GameEngineSoundPlayer::IsPlay() 
{
	bool Check = false;
	// 이 FMOD를 짠사람이 그냥 이렇게 짠거에요.
	playChannel_->isPlaying(&Check);
	return Check;
}

void GameEngineSoundPlayer::PlayCountReset(int _Count /*= -1*/) 
{
	PlayCount = _Count;
}

void GameEngineSoundPlayer::PlayOverLap(const std::string& _name, int _LoopCount/* = 1*/)
{
	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSound(_name);

	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
	
}

void GameEngineSoundPlayer::PlayAlone(const std::string& _name, int _LoopCount /*= 1*/) 
{
	// 함수를 만들어서 그함수를 다시 실행
	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSound(_name);

	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (true == IsPlay())
	{
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
}

void GameEngineSoundPlayer::Stop()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	playChannel_->stop();
	playChannel_ = nullptr;
}

void GameEngineSoundPlayer::VolumeUp()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	Volume_ += 0.1f;

	playChannel_->setVolume(Volume_);
}

void GameEngineSoundPlayer::VolumeDown()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	Volume_ -= 0.1f;

	playChannel_->setVolume(Volume_);
}