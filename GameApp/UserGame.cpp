#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

#include "TitleLevel.h"
#include "LithHarborLevel.h"
#include "PerionLevel.h"
#include "PerionRoomLevel.h"
#include "PerionNorthernRidgeLevel.h"
#include "DeepeningForestLevel.h"
#include "SilentSwampLevel.h"
#include "SahelLevel.h"
#include "EntranceDemianLevel.h"
#include "DemianLevel.h"

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

void UserGame::Initialize()
{
	// Title
	LevelCreate<TitleLevel>("Title");

	// Town
	LevelCreate<LithHarborLevel>("LithHarbor");
	LevelCreate<PerionLevel>("Perion");
	LevelCreate<PerionRoomLevel>("PerionRoom");

	// Hunting Ground
	LevelCreate<PerionNorthernRidgeLevel>("PerionNorthernRidge");
	LevelCreate<DeepeningForestLevel>("DeepeningForest");
	LevelCreate<SilentSwampLevel>("SilentSwamp");
	LevelCreate<SahelLevel>("Sahel");

	// Demian
	LevelCreate<EntranceDemianLevel>("EntranceDemian");
	LevelCreate<DemianLevel>("Demian");

	LevelChange("Perion");
}

void UserGame::Release()
{
	
}


