#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineBase/GameEngineString.h"

#pragma comment(lib, "DirectXTex.lib")

GameEngineTexture::GameEngineTexture() // default constructer 디폴트 생성자
	: TextureDesc_()
	, Texture2D_(nullptr)
	, RenderTargetView_(nullptr)
	, ShaderResourceView_(nullptr)
{

}

GameEngineTexture::~GameEngineTexture() // default destructer 디폴트 소멸자
{
	
	if (nullptr != ShaderResourceView_)
	{
		ShaderResourceView_->Release();
		ShaderResourceView_ = nullptr;
	}

	if (nullptr != RenderTargetView_)
	{
		RenderTargetView_->Release();
		RenderTargetView_ = nullptr;
	}

	if (nullptr != Texture2D_)
	{
		Texture2D_->Release();
		Texture2D_ = nullptr;
	}
}

ID3D11RenderTargetView* GameEngineTexture::GetRenderTargetView()
{
	return RenderTargetView_;
}

ID3D11ShaderResourceView** GameEngineTexture::GetShaderResourceView()
{
	return &ShaderResourceView_;
}

void GameEngineTexture::Create(ID3D11Texture2D* _Texture2D)
{
	if (nullptr == _Texture2D)
	{
		GameEngineDebug::MsgBoxError("Texture is null GameEngineTexture Create Error");
	}

	Texture2D_ = _Texture2D;
}

void GameEngineTexture::Load(const std::string& _Path)
{
	GameEngineFile NewFile = GameEngineFile(_Path);

	std::string Extension = NewFile.GetExtension();
	GameEngineString::toupper(Extension);

	std::wstring wPath;
	GameEngineString::StringToWString(_Path, wPath);

	if ("TGA" == Extension)
	{
		GameEngineDebug::MsgBoxError("로드 할수없는 이미지 포맷입니다." + Extension);
	}
	else if ("DDS" == Extension)
	{
		GameEngineDebug::MsgBoxError("로드 할수없는 이미지 포맷입니다." + Extension);
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, Image_))
		{
			GameEngineDebug::MsgBoxError("로드 할수없는 이미지 포맷입니다." + _Path);
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(GameEngineDevice::GetDevice(),
		Image_.GetImages(), Image_.GetImageCount(), Image_.GetMetadata(), &ShaderResourceView_))
	{
		GameEngineDebug::MsgBoxError("ShaderResourceView_ 생성을 실패했습니다." + _Path);
	}

	TextureDesc_.Width = static_cast<UINT>(Image_.GetMetadata().width);
	TextureDesc_.Height = static_cast<UINT>(Image_.GetMetadata().height);
}

ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RenderTargetView_)
	{
		GameEngineDebug::MsgBoxError("RenderTargetView OverLap Create Error");
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D_,
		nullptr, &RenderTargetView_))
	{
		GameEngineDebug::MsgBoxError("RenderTargetView Create Error");
	}

	return RenderTargetView_;
}