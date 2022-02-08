#include "PreCompile.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShaderManager* GameEnginePixelShaderManager::Inst = new GameEnginePixelShaderManager();

GameEnginePixelShaderManager::GameEnginePixelShaderManager() // default constructer 디폴트 생성자
{

}

GameEnginePixelShaderManager::~GameEnginePixelShaderManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEnginePixelShader*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEnginePixelShaderManager::GameEnginePixelShaderManager(GameEnginePixelShaderManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



GameEnginePixelShader* GameEnginePixelShaderManager::Create(const std::string& _Name,
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh /*= 5*/,
	UINT _VersionLow /*= 0*/
)
{
	GameEnginePixelShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}


	GameEnginePixelShader* NewRes = new GameEnginePixelShader();
	NewRes->SetName(_Name);

	if (false == NewRes->Create(_ShaderCode, _EntryPoint, _VersionHigh, _VersionLow))
	{
		delete NewRes;
		return nullptr;
	}

	ResourcesMap.insert(std::map<std::string, GameEnginePixelShader*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEnginePixelShader* GameEnginePixelShaderManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEnginePixelShader* GameEnginePixelShaderManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEnginePixelShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEnginePixelShader* NewRes = new GameEnginePixelShader();
	NewRes->SetName(_Name);


	ResourcesMap.insert(std::map<std::string, GameEnginePixelShader*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEnginePixelShader* GameEnginePixelShaderManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEnginePixelShader*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}