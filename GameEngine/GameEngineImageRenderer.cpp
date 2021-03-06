#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransform.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSamplerManager.h"

GameEngineImageRenderer::GameEngineImageRenderer()
	: ScaleToImageSize_(true)
	, ImageSize_()
	, CurTexture_(nullptr)
	, CurAnimation_(nullptr)
	, CutData_(0, 0, 1, 1)
	, IsPlay_(true)
	, IsLeft_(true)
{

}

GameEngineImageRenderer::~GameEngineImageRenderer()
{
	for (auto& Animation : AllAnimations_)
	{
		if (nullptr == Animation.second)
		{
			continue;
		}

		delete Animation.second;
		Animation.second = nullptr;
	}
}

void GameEngineImageRenderer::SetImageSize(const float4& _ImageSize)
{
	ImageSize_ = _ImageSize;

	GetTransform()->SetLocalScaling(ImageSize_);
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName,
	bool _ScaleToImageSize/* = true*/,
	const std::string& _Sampler)
{
	CurTexture_ = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (nullptr == CurTexture_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처를 세팅하려고 했습니다");
		return;
	}

	if (true == _ScaleToImageSize)
	{
		SetImageSize(CurTexture_->GetImageSize());
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);

	GameEngineSampler* Sampler = GameEngineSamplerManager::GetInst().Find(_Sampler);

	if (nullptr == Sampler)
	{
		return;
	}

	ShaderHelper.SettingSampler("Smp", _Sampler);

}

void GameEngineImageRenderer::ImageLocalFlipYAxis()
{
	if (nullptr == this)
	{
		return;
	}

	SetLocalPosition(GetLocalPosition().InvertX());
	AddLocalRotation(float4(0.0f, 180.0f, 0.0f));

	if (nullptr == CurAnimation_)
	{
		return;
	}

	if (nullptr == CurAnimation_->FolderTextures_)
	{
		return;
	}
}

void GameEngineImageRenderer::SetIndex(const int _Index)
{
	if (nullptr == CurTexture_)
	{
		GameEngineDebug::MsgBoxError("텍스처가 존재하지 않는데 인덱스를 지정하려고 했습니다");
	}

	if (false == CurTexture_->IsCut())
	{
		GameEngineDebug::MsgBoxError("잘리지 않은 텍스처의 인덱스를 지정하려고 했습니다.");
	}

	CutData_ = CurTexture_->GetCutData(_Index);
}

void GameEngineImageRenderer::CreateAnimation(const std::string& _TextureName,
	const std::string& _Name, int _StartFrame,int _EndFrame, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->AnimationTexture_ = GameEngineTextureManager::GetInst().Find(_TextureName);

	if (nullptr == NewAnimation->AnimationTexture_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처로 애니메이션을 만들려고 했습니다.");
	}

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = nullptr;
	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer_ = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::
		value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _FolderTexName,
	const std::string& _Name, float _InterTime, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
	}

	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().Find(_FolderTexName);

	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 폴더 텍스처를 세팅하려고 했습니다..");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = FolderTexture;
	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer_ = this;
	
	AllAnimations_.insert(std::map<std::string, Animation2D*>::
		value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _FolderTexName, 
	const std::string& _Name, std::vector<float> _InterTimes, bool _Loop)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
	}

	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().Find(_FolderTexName);

	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 폴더 텍스처를 세팅하려고 했습니다..");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd_ = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTimes[0];
	NewAnimation->CurTime_ = _InterTimes[0];

	NewAnimation->FolderTextures_ = FolderTexture;
	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer_ = this;
	NewAnimation->InterTimes_ = _InterTimes;
	NewAnimation->IsSameInterTime_ = false;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::
		value_type(_Name, NewAnimation));
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _Name, 
	float _InterTime, bool _Loop)
{
	CreateAnimationFolder(_Name, _Name, _InterTime, _Loop);
}

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _Name, 
	std::vector<float> _InterTimes, bool _Loop)
{
	CreateAnimationFolder(_Name, _Name, _InterTimes, _Loop);
}

void GameEngineImageRenderer::SetChangeAnimation(const std::string& _Name,
	bool _IsForce)
{
	Animation2D* FindAni = FindAnimation(_Name);

	if (false == _IsForce && CurAnimation_ == FindAni)
	{
		return;	// Same Animation
	}

	CurAnimation_ = FindAni;

	if (nullptr == CurAnimation_->FolderTextures_)
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->AnimationTexture_);
	}
	else
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->FolderTextures_->GetTextureIndex(CurAnimation_->CurFrame_));
	}

	CurAnimation_->Reset();
	CurAnimation_->CallStart();
	AnimationPlay();
}

GameEngineImageRenderer::Animation2D* GameEngineImageRenderer::FindAnimation(const std::string& _Name)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* 가 nullptr 입니다");
	}

	return FindIter->second;
}

float4 GameEngineImageRenderer::GetAnimationTextureSize(const std::string& _Name, int _Index)
{
	return FindAnimation(_Name)->GetTextureSize(_Index);
}

void GameEngineImageRenderer::SetStartCallBack(const std::string& _Name,
	std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* 가 nullptr 입니다");
	}

	FindIter->second->StartCallBack_.push_back(_CallBack);
}

void GameEngineImageRenderer::SetEndCallBack(const std::string& _Name,
	std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* 가 nullptr 입니다");
	}

	FindIter->second->EndCallBack_.push_back(_CallBack);
}

void GameEngineImageRenderer::SetFrameCallBack(const std::string& _Name,
	int _Index, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("Animation2D* 가 nullptr 입니다");
	}

	FindIter->second->FrameCallBack_[_Index].push_back(_CallBack);
}

void GameEngineImageRenderer::Update(float _DeltaTime)
{
	GameEngineRenderer::Update(_DeltaTime);

	if (nullptr == CurAnimation_)
	{
		return;
	}

	CurAnimation_->Update(_DeltaTime);
}

void GameEngineImageRenderer::SetRenderingPipeLineSettingNext()
{
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData_);

	CorrectResultColor_.vMulColor = float4::ONE;
	CorrectResultColor_.vPlusColor = float4::ZERO;

	ShaderHelper.SettingConstantBufferLink("CorrectResultColor", CorrectResultColor_);
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
}

void GameEngineImageRenderer::Animation2D::Reset()
{
	IsEnd_ = false;
	CurTime_ = InterTime_;
	CurFrame_ = StartFrame_;
}

void GameEngineImageRenderer::Animation2D::CallStart()
{
	for (auto& CallBack : StartCallBack_)
	{
		CallBack();
	}
}

void GameEngineImageRenderer::Animation2D::CallEnd()
{
	for (auto& CallBack : EndCallBack_)
	{
		CallBack();
	}
}

void GameEngineImageRenderer::Animation2D::CallFrame()
{
	for (auto& CallBack : FrameCallBack_)
	{
		if (CallBack.first != CurFrame_)
		{
			continue;
		}

		if (CallBack.second.size() == 0)
		{
			continue;
		}

		for (size_t i = 0; i < CallBack.second.size(); i++)
		{
			CallBack.second[i]();
		}
	}
}

void GameEngineImageRenderer::Animation2D::Update(float _DeltaTime)
{
	if (true == Renderer_->IsPlay_)
	{
		CurTime_ -= _DeltaTime;
	}

	if (StartFrame_ < EndFrame_)
	{
		FrameUpdate();
	}
	else
	{
		ReverseFrameUpdate();
	}

	// CallFrame();

	if (nullptr == FolderTextures_)
	{
		Renderer_->ShaderHelper.SettingTexture("Tex", AnimationTexture_);
		Renderer_->CurTexture_ = AnimationTexture_;
		Renderer_->SetIndex(CurFrame_);
	}
	else
	{
		Renderer_->CutData_ = float4(0, 0, 1, 1);
		Renderer_->ShaderHelper.SettingTexture("Tex", 
			FolderTextures_->GetTextureIndex(CurFrame_));
		Renderer_->SetLocalScaling(FolderTextures_->GetTextureIndex(CurFrame_)->GetTextureSize());
		Renderer_->SetImageSize(Renderer_->GetLocalScaling());
	}
}

void GameEngineImageRenderer::Animation2D::FrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		++CurFrame_;
		CallFrame();

		if (true == Loop_ &&
			CurFrame_ > EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_ &&
			CurFrame_ > EndFrame_)
		{
			// CallEnd() 를 한번만 호출하기 위함
			if (false == IsEnd_)
			{
				CallEnd();
			}

			IsEnd_ = true;

			CurFrame_ = EndFrame_;
		}


		if (true == IsSameInterTime_)
		{
			CurTime_ = InterTime_;
		}
		else
		{
			CurTime_ = InterTimes_[CurFrame_];
		}
	}
}

void GameEngineImageRenderer::Animation2D::ReverseFrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		--CurFrame_;
		CallFrame();

		CurTime_ = InterTime_;
		if (true == Loop_
			&& CurFrame_ < EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_
			&& CurFrame_ < EndFrame_)
		{
			if (false == IsEnd_)
			{
				CallEnd();
			}

			IsEnd_ = true;

			CurFrame_ = EndFrame_;
		}
	}

}

float4 GameEngineImageRenderer::Animation2D::GetTextureSize(int _Index)
{
	if (EndFrame_ < _Index || 0 > _Index)
	{
		GameEngineDebug::MsgBoxError("잘못된 오프셋 프레임입니다.");
	}

	return FolderTextures_->GetTextureIndex(_Index)->GetTextureSize();
}