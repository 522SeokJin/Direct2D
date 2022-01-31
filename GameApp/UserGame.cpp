#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h> //_getch();

#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/GameEngineRenderingPipeLine.h"

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void UserGame::Initialize()
{
	return;
}

float RotAngle = 0.0f;
float4 BoxPos = { 0.0f, 0.0f, 0.0f };

void UserGame::ResourceLoad()
{
	{
		GameEngineDirectroy SoundDir;
		SoundDir.MoveParent("Direct2D");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}

	{
		// 각자 물체가 각자의 크기와 회전값을 가진 세상
		// 로컬스페이스

		// 로컬세상에 있는 물체를 우리가 원하는 대로 변형하고
		// 위치시키고 인식합니다.
		// 월드스페이스

		std::vector<float4> RectVertex = std::vector<float4>(4 * 6);

		// 0 1
		// 3 2

		{
			RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
			RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
			RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
			RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

			RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
			RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
			RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
			RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);
		}

		{
			RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
			RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
			RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
			RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

			RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
			RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
			RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
			RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);
		}

		{
			RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
			RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
			RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
			RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

			RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
			RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
			RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
			RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);
		}

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);
	}

	{
		std::vector<int> RectIndex;

		for (int i = 0; i < 6; i++)
		{
			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 1);
			RectIndex.push_back(i * 4 + 2);

			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 2);
			RectIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);
	}

	{
		// 이 스택에서 곧바로 넣어주고 싶은건
		// [] -> 람다함수
		// 이름없는 함수를 즉석에서 만들어낼수있다.

		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				// 1 0 0 0
				// 0 1 0 0
				// 0 0 1 0
				// 0 0 0 1

				float4x4 ScaleMat;
				ScaleMat.Scaling({ 20.0f, 20.0f, 20.0f });

				float4x4 RotMat;
				RotMat.RotationDeg({ 0.0f, 0.0f, 0.0f });

				float4x4 PosMat;
				//PosMat.Translation({ 0.0f, 0.0f, 0.0f });
				PosMat.Translation(BoxPos);

				// 보는 사람이 없으면 안됨
				float4x4 ViewMat;

				ViewMat.ViewToLH({ 0.0f, 0.0f, -200.0f }, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});

				// 세계의 크기를 -1 1사이의 값으로 줄인다.
				// X = -1~1;
				// Y = -1~1;
				// Z = 0~1;

				// 보통 2가지 투영행렬이 있는데.
				// 1. 원근감을 주는 투영행렬 원근투영
				// 2. 주지 않는 투영행렬 직교투영

				// -1~1로 들어가기 직전으로 바꾼다.

				float4x4 PerspectiveMat;
				PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);

				float4x4 OrthographicMat;
				OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);

				// float4x4 ProjectionMat;

				// 벡터란?
				// 원점에서부터 시작하는 x y

				// 행렬은 교환법칙이 성립하지 않는다.
				
				// 순서를 지켜서 곱해야한다.
				// 크자이공부
				// 크기 자전 이동 공전 부모
				// 뷰행렬 -> 공전행렬
	
				float4x4 WorldMat = ScaleMat * RotMat * PosMat;
				float4x4 WolrdView = WorldMat * ViewMat;

				float4x4 WorldViewProjectionMat = WolrdView * PerspectiveMat;

				float4x4 WorldViewOrthographicMat = WolrdView * OrthographicMat;

				float4 PersPos = _Value;
				PersPos *= WorldViewProjectionMat;
				float4 OrthPos = _Value;
				OrthPos *= WorldViewOrthographicMat;

				return PersPos;
			}
		);
	}

	{
		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("TestRasterizer");

		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void UserGame::Release()
{
	
}

void UserGame::GameLoop()
{
	GameEngineDirectXDevice::RenderStart();

	/*GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");
	Pipe.SetRasterizer("TestRasterizer");

	RotAngle += 180.0f * GameEngineTime::GetInst().GetDeltaTime();
	BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();*/

	GameEngineDirectXDevice::RenderEnd();
}



