#include "PreCompile.h"
#include "CameraComponent.h"
#include "GameEngineWindow.h"
#include "GameEngineTransform.h"
#include "GameEngineRenderer.h"

CameraComponent::CameraComponent()
	: ProjectionMode_(ProjectionMode::PERSPECTIVE)
	, FovAngleY_(90.0f)
	, NearZ_(0.1f)
	, FarZ_(1000.0f)
	, CamSize_(GameEngineWindow::GetInst().GetSize())
{

}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Start()
{
}

void CameraComponent::Update()
{
}

void CameraComponent::CameraTransformUpdate()
{
	GetTransform()->GetTransformData().View_.ViewToLH(
		GetTransform()->GetWorldPosition(),
		GetTransform()->GetWorldForwardVector(),
		GetTransform()->GetWorldUpVector()
	);

	switch (ProjectionMode_)
	{
	case ProjectionMode::PERSPECTIVE:
		GetTransform()->GetTransformData().Projection_.PerspectiveFovLH(FovAngleY_, CamSize_.x,
			CamSize_.y, NearZ_, FarZ_);
		break;
	case ProjectionMode::ORTHOGRAPHIC:
		GetTransform()->GetTransformData().Projection_.OrthographicLH(CamSize_.x,
			CamSize_.y, NearZ_, FarZ_);
		break;
	default:
		break;
	}
}

void CameraComponent::Render()
{
	float4x4 View = GetTransform()->GetTransformData().View_;
	float4x4 Projection = GetTransform()->GetTransformData().Projection_;

	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->GetTransform()->GetTransformData().View_ = View;
			Renderer->GetTransform()->GetTransformData().Projection_ = Projection;

			Renderer->Render();
		}
	}
}

void CameraComponent::ReleaseRenderer()
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator RenderMapBeginIter = RendererList_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator RenderMapEndIter = RendererList_.end();

	for (; RenderMapBeginIter != RenderMapEndIter; ++RenderMapBeginIter)
	{
		std::list<GameEngineRenderer*>& Renderers = RenderMapBeginIter->second;

		std::list<GameEngineRenderer*>::iterator BeginIter = Renderers.begin();
		std::list<GameEngineRenderer*>::iterator EndIter = Renderers.end();

		for (; BeginIter != EndIter; )
		{
			GameEngineRenderer* ReleaseRenderer = *BeginIter;

			if (nullptr == ReleaseRenderer)
			{
				GameEngineDebug::MsgBoxError("Release Actor Is Nullptr!!!!");
			}

			if (true == ReleaseRenderer->IsDeath())
			{
				BeginIter = Renderers.erase(BeginIter);

				continue;
			}

			++BeginIter;
		}
	}
}

void CameraComponent::PushRenderer(int _Order, GameEngineRenderer* _Renderer)
{
	RendererList_[_Order].push_back(_Renderer);
}