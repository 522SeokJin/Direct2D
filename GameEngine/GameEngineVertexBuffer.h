#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>

// �з� : ������ ����������
// �뵵 : ���ؽ�����
// ���� : ������ġ������ ����
class GameEngineVertexBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	std::vector<float4> Vertexs_;

public:
	const std::vector<float4>& GetVertexs();

public:
	GameEngineVertexBuffer(); // default constructer ����Ʈ ������
	~GameEngineVertexBuffer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Create(const std::vector<float4>& _Vertexs);
};
