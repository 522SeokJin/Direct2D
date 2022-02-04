#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer() // default constructer 디폴트 생성자
	: Buffer_(nullptr)
	, BufferData_()
	, ResData_()
	, Format_(DXGI_FORMAT::DXGI_FORMAT_R32_UINT)
	, Offset_(0)
{
	memset(&BufferData_, 0, sizeof(BufferData_));
	memset(&ResData_, 0, sizeof(ResData_));
}

GameEngineIndexBuffer::~GameEngineIndexBuffer() // default destructer 디폴트 소멸자
{
	if (nullptr != Buffer_)
	{
		Buffer_->Release();
		Buffer_ = nullptr;
	}
}

GameEngineIndexBuffer::GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: Buffer_(_other.Buffer_)
	, BufferData_(_other.BufferData_)
	, ResData_(_other.ResData_)
	, Format_(_other.Format_)
	, Offset_(_other.Offset_)
{

}

void GameEngineIndexBuffer::Create(const std::vector<UINT>& _Datas, D3D11_USAGE _Usage)
{
	Create(reinterpret_cast<const void*>(&_Datas[0]), sizeof(UINT), _Datas.size(), _Usage);
}

void GameEngineIndexBuffer::Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage)
{
	ResData_.pSysMem = _Data;

	BufferData_.ByteWidth = static_cast<UINT>(_Size) * static_cast<UINT>(_Count);
	BufferData_.Usage = _Usage;
	BufferData_.CPUAccessFlags = 0;
	if (BufferData_.Usage == D3D11_USAGE_DYNAMIC)
	{
		BufferData_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	}

	BufferData_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	BufferData_.StructureByteStride = 0;
	BufferData_.MiscFlags = 0;

	Offset_ = 0;
	Format_ = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferData_, &ResData_, &Buffer_))
	{
		GameEngineDebug::MsgBoxError("IndexBuffer Create Error");
		return;
	}
}

void GameEngineIndexBuffer::Setting()
{
	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer_, Format_, Offset_);
}
