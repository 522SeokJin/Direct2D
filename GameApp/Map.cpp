#include "PreCompile.h"
#include "Map.h"
#include <GameEngine/GameEngineImageRenderer.h>

Map* Map::CurrentMap = nullptr;

Map::Map()
	: PixelCollideImage_(nullptr)
	, MapImage_(nullptr)
{

}

Map::~Map()
{

}

void Map::Start()
{
}

void Map::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
}

float4 Map::GetColor(GameEngineTransform* _Ptr, bool _YReverse/* = true*/)
{
	float4 Pos = _Ptr->GetWorldPosition();

	if (true == _YReverse)
	{
		Pos.y *= -1.0f;
	}

	return GetColor(Pos);
}

float4 Map::GetColor(float4 _Position)
{
	return CurrentMap->PixelCollideImage_->GetCurrentTexture()->GetPixel(_Position.ix(), _Position.iy());
}

float4 Map::GetMapSize()
{
	return PixelCollideImage_->GetImageSize();
}