#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"

GameEngineRenderTarget::GameEngineRenderTarget() // default constructer ����Ʈ ������
{

}

GameEngineRenderTarget::~GameEngineRenderTarget() // default destructer ����Ʈ �Ҹ���
{
	
}

GameEngineRenderTarget::GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineRenderTarget::Clear()
{
	for (size_t i = 0; i < RenderTargetViews_.size(); i++)
	{
		GameEngineDirectXDevice::GetContext()->ClearRenderTargetView(
			RenderTargetViews_[i], ClearColor_[i].Arr1D);
	}
}

void GameEngineRenderTarget::Create(const std::string& _TextureName, float4 _ClearColor)
{
	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_TextureName);
	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("FindTexture is null Create RenderTarget Error");
	}
	
	Textures_.push_back(FindTexture);
	RenderTargetViews_.push_back(FindTexture->CreateRenderTargetView());
	ClearColor_.push_back(_ClearColor);
}

void GameEngineRenderTarget::Setting(int _Index)
{
	if ( 0 >= RenderTargetViews_.size())
	{
		GameEngineDebug::MsgBoxError("RenderTarget Setting Error Size Zero");
	}

	if (-1 == _Index)
	{
		GameEngineDirectXDevice::GetContext()->OMSetRenderTargets(RenderTargetViews_.size(),
			&RenderTargetViews_[0], nullptr);
	}
	else
	{
		GameEngineDirectXDevice::GetContext()->OMSetRenderTargets(1, &RenderTargetViews_[_Index], nullptr);
	}
}