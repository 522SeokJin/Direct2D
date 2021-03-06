#pragma once

#include <GameEngineBase/GameEngineSoundManager.h>

#include "GameEngineConstantBufferManager.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineTextureManager.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineSamplerManager.h"
#include "GameEngineBlendManager.h"
#include "GameEngineDepthStencilManager.h"
#include "GameEngineDepthBufferManager.h"
#include "GameEngineFontManager.h" 

#include "GameEngineRenderingPipeLineManager.h"

#include "GameEngineConstantBuffer.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineDepthBuffer.h"
#include "GameEngineFont.h"

#include "GameEngineRenderingPipeLine.h"


class GameEngineManagerHelper
{
public:
	static void ManagerRelease()
	{
		GameEngineSoundManager::Destroy();

		GameEngineRenderingPipeLineManager::Destroy();

		GameEngineFontManager::Destroy();
		GameEngineConstantBufferManager::Destroy();
		GameEngineFolderTextureManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineIndexBufferManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEngineRenderTargetManager::Destroy();
		GameEnginePixelShaderManager::Destroy();
		GameEngineSamplerManager::Destroy();
		GameEngineTextureManager::Destroy();
		GameEngineBlendManager::Destroy();
		GameEngineDepthStencilManager::Destroy();
		GameEngineDepthBufferManager::Destroy();
	}
};