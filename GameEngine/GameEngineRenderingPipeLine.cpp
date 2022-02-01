#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"

#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer 디폴트 생성자
	: VertexBuffer_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
	, Rasterizer_(nullptr)
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept 
	// default RValue Copy constructer 디폴트 RValue 복사생성자
	: VertexBuffer_(_other.VertexBuffer_)
	, VertexShader_(_other.VertexShader_)
	, IndexBuffer_(_other.IndexBuffer_)
	, Rasterizer_(_other.Rasterizer_)
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스버퍼를 세팅하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 인덱스버퍼를 세팅하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);

	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 레스터라이저 세팅을 하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetMesh()
{
	//SetInputAssembler1();
	//SetInputAssembler2();
}

void GameEngineRenderingPipeLine::SetMaterial()
{

}

void GameEngineRenderingPipeLine::Rendering()
{
	// input어셈블러 단계

}
