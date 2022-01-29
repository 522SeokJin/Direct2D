#pragma once

// ���� : 
class GameEngineRasterizer;
class GameEngineRasterizerManager
{
private:
	static GameEngineRasterizerManager* Inst;

public:
	static GameEngineRasterizerManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineRasterizer*> ResourcesMap;

public:
	// ���� ����� �ִ�.
	GameEngineRasterizer* Create(const std::string& _Name);
	// ���Ͽ��� �ε�
	GameEngineRasterizer* Load(const std::string& _Path);
	// �̸� ���� ����
	GameEngineRasterizer* Load(const std::string& _Name, const std::string& _Path);
	// ��Ͽ��� ã�´�.
	GameEngineRasterizer* Find(const std::string& _Name);

private:
	GameEngineRasterizerManager(); // default constructer ����Ʈ ������
	~GameEngineRasterizerManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizerManager(const GameEngineRasterizerManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizerManager(GameEngineRasterizerManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRasterizerManager& operator=(const GameEngineRasterizerManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizerManager& operator=(const GameEngineRasterizerManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
};



