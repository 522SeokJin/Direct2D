#pragma once

class GameEngineMath 
{
public:
	static const float PI;
	static const float PI2;
	static const float DegreeToRadian;
	static const float RadianToDegree;

	static int IntLength(int _Num);
	static int PlaceValue(int _Num, int _Place);
};

class float4x4;
class float4 
{
public:
	static const float4 ZERO;
	static const float4 ONE;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	static const float4 RED;
	static const float4 BLUE;
	static const float4 GREEN;
	static const float4 WHITE;
	static const float4 BLACK;
	static const float4 NONE;

	static const float4 INVERT_X;
	static const float4 INVERT_Y;
	static const float4 INVERT_Z;

public:
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1

	static float4 Cross3D(float4 _Left, float4 _Right)
	{
		return DirectX::XMVector3Cross(_Left.DirectVector, _Right.DirectVector);
	}

	static float Dot3D(float4 _Left, float4 _Right)
	{
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// 정사영
	static float Dot3DToLen(float4 _Left, float4 _Right)
	{
		_Right.Normalize3D();
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	// 코사인
	static float Dot3DToCos(float4 _Left, float4 _Right)
	{
		_Left.Normalize3D();
		_Right.Normalize3D();
		return DirectX::XMVector3Dot(_Left.DirectVector, _Right.DirectVector).m128_f32[0];
	}

	static float Dot3DToCosAngle(float4 _Left, float4 _Right)
	{
		// (1 * 2) = 2
		//  / 2
		// 역함수
		// cost(1) = ???
		// ??? => 1

		return acos(Dot3DToLen(_Left, _Right));
	}

	static float4 Rotate3DDegree(const float4& _Vector, const float4& _Angle)
	{
		float4 ResultVector = _Vector;
		ResultVector.Rotate3DDegree(_Angle);
		return ResultVector;
	}

	static float4 RotateXDegree(const float4& _OriginVector, float _Degree)
	{
		return RotateXRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateXRadian(const float4& _OriginVector, float _Radian);

	static float4 RotateYDegree(const float4& _OriginVector, float _Degree)
	{
		return RotateYRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateYRadian(const float4& _OriginVector, float _Radian);

	static float4 RotateZDegree(const float4& _OriginVector, float _Degree)
	{
		return RotateZRadian(_OriginVector, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RotateZRadian(const float4& _OriginVector, float _Radian);

	static float4 DirZDegree(float _Degree)
	{
		return DirZRadian(_Degree * GameEngineMath::DegreeToRadian);
	}

	// 0도일때의 벡터를 회전시키는 공식
	static float4 DirZRadian(float _Radian);

public:
	// unnamed union을 선언하면 
	// 내부의 메모리를 구조를 union 방식으로 구성해준다.
	union 
	{
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float Arr1D[4];

		DirectX::XMFLOAT3 DxXmfloat3;
		DirectX::XMFLOAT4 DxXmfloat4;

		DirectX::XMVECTOR DirectVector;

		// 실수는 기본적으로 00000000 00000000 00000000 00000000
	};

	float4 operator+(const float4& _Value) const
	{
		return DirectX::XMVectorAdd(DirectVector, _Value.DirectVector);
	}

	float4 operator-() const
	{
		return DirectX::XMVectorNegate(DirectVector);
	}
	
	float4 operator-(const float4& _Value) const
	{
		return DirectX::XMVectorSubtract(DirectVector, _Value.DirectVector);
	}

	float4 operator*(const float _Value) const
	{
		float4 CalVector = { _Value, _Value, _Value, 1.0f };
		return DirectX::XMVectorMultiply(DirectVector, CalVector.DirectVector);
	}

	float4 operator*(const float4x4& _Value) const;

	float4 operator*(const float4& _Value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, _Value.DirectVector);	
	}

	float4 operator/(const float4& _Value) const
	{
		return DirectX::XMVectorDivide(DirectVector, _Value.DirectVector);	
	}

	float4& operator+=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorAdd(DirectVector, _Value.DirectVector);
		return *this;
	}

	float4& operator-=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorSubtract(DirectVector, _Value.DirectVector);
		return *this;
	}

	float4& operator*=(const float _Value)
	{
		float4 CalVector = { _Value, _Value, _Value, 1.0f };
		DirectVector = DirectX::XMVectorMultiply(DirectVector, CalVector.DirectVector);
		return *this;
	}

	float4& operator*=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorMultiply(DirectVector, _Value.DirectVector);
		return *this;
	}

	float4& operator*=(const float4x4& _Value);

	bool operator==(const float4& _Value) const
	{
		return x == _Value.x && y == _Value.y && z == _Value.z && w == _Value.w;
	}

	bool operator!=(const float4& _Value) const
	{
		return x != _Value.x || y != _Value.y || z != _Value.z || w != _Value.w;
	}

	float4& operator/=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorDivide(DirectVector, _Value.DirectVector);
		return *this;
	}

	// 대입연산자
	float4& operator=(const float4& _Value)
	{
		DirectVector = DirectX::XMVectorSet(_Value.x, _Value.y, _Value.z, _Value.w);
		return *this;
	}

	unsigned int ColorToUint() const
	{
		char Color255[4] = {};

		Color255[0] = static_cast<char>(x * 255.0f);
		Color255[1] = static_cast<char>(y * 255.0f);
		Color255[2] = static_cast<char>(z * 255.0f);
		Color255[3] = static_cast<char>(w * 255.0f);

		return *(reinterpret_cast<unsigned int*>(Color255));
	}

	std::string ToString()
	{
		return " x : " + std::to_string(x) + " y : " + std::to_string(y) + " z : " + std::to_string(z);
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}

	int uiz() const
	{
		return static_cast<unsigned int>(z);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float4 halffloat4() const
	{
		return {hx(), hy(), hz()};
	}

	int ihx() const
	{
		return static_cast<int>(hx());
	}

	int ihy() const
	{
		return static_cast<int>(hy());
	}

	int ihz() const
	{
		return static_cast<int>(hz());
	}

	float Len2D()
	{
		float4 Len = DirectX::XMVector2Length(DirectVector);
		return Len.x;
	}

	float Len3D()
	{
		float4 Len = DirectX::XMVector3Length(DirectVector);
		return Len.x;
	}

	float4 NormalizeReturn3D() const
	{
		return DirectX::XMVector3Normalize(DirectVector);
	}

	void Normalize3D()
	{
		DirectVector = DirectX::XMVector3Normalize(DirectVector);
	}

	float4 ToRadianAngle() const
	{
		return this->operator*(GameEngineMath::DegreeToRadian);
	}

	float4 ToDegreeQuaternion() const
	{
		return DirectX::XMQuaternionRotationRollPitchYawFromVector(ToRadianAngle().DirectVector);
	}

	POINT GetWindowPoint()
	{
		return { ix(), iy() };
	}

	void RotateXDegree(float _Deg)
	{
		*this = RotateXDegree(*this, _Deg);
		return;
	}

	void RotateYDegree(float _Deg)
	{
		*this = RotateYDegree(*this, _Deg);
		return;
	}

	void RotateZDegree(float _Deg)
	{
		*this = RotateZDegree(*this, _Deg);
		return;
	}

	float4& InvertX()
	{
		x = -x;
		return *this;
	}

	float4& InvertY()
	{
		y = -y;
		return *this;
	}

	float4& InvertZ()
	{
		z = -z;
		return *this;
	}

	float4& Rotate3DDegree(const float4& _Angle)
	{
		DirectVector = DirectX::XMVector3Rotate(DirectVector, 
			DirectX::XMQuaternionRotationRollPitchYawFromVector(_Angle.DirectVector));
		return *this;
	}

	

public:
	float4() 
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{
	}

	// 디폴트 파라미터
	// 가장 우측에 있는 인자에 상수값을 넣어서
	// 만약 인자를 넣어주지 않았을때는 
	float4(float _x, float _y, float _z, float _w = 1.0f)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	~float4()
	{
	}

public:
	float4(const float4& _Value)
		: x(_Value.x), y(_Value.y), z(_Value.z), w(_Value.w)
	{

	}

	float4(DirectX::XMVECTOR _Value)
		: DirectVector(_Value)
	{

	}

};

class int4 
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct 
		{
			__int64 HighValue;
			__int64 LowValue;
		};
	};
};


class Figure
{
public:
	float4 pos_;
	float4 size_;

public:
	float Left()
	{
		return pos_.x - size_.hx();
	}

	float Right()
	{
		return pos_.x + size_.hx();
	}

	float Top()
	{
		return pos_.y - size_.hy();
	}

	float Bot()
	{
		return pos_.y + size_.hx();
	}

	int iLeft() 
	{
		return pos_.ix() - size_.ihx();
	}

	int iRight()
	{
		return pos_.ix() + size_.ihx();
	}

	int iTop()
	{
		return pos_.iy() - size_.ihy();
	}

	int iBot()
	{
		return pos_.iy() + size_.ihy();
	}

	float4 LeftTopfloat4()
	{
		return { Left(), Top() };
	}

	float4 RightTopfloat4()
	{
		return { Right(), Top() };
	}

	float4 LeftBotfloat4()
	{
		return { Left(), Bot() };
	}

	float4 RightBotfloat4()
	{
		return { Right(), Bot() };
	}


public:
	Figure(float4 _Pos, float4 _Size) 
		: pos_(_Pos), size_(_Size)
	{

	}
};

class float4x4
{
public:
	union
	{
		float Arr2D[4][4];

		struct
		{
			float4 vx;
			float4 vy;
			float4 vz;
			float4 vw;
		};

		float Arr1D[4 * 4];

		// 실수는 기본적으로 00000000 00000000 00000000 00000000

		DirectX::XMFLOAT4X4 DxXmfloat4x4;
		DirectX::XMMATRIX DirectMatrix;
	};

public:
	float4x4()
		: DirectMatrix(DirectX::XMMatrixIdentity())
	{

	}

	float4x4(const float4x4& _Value)
		: DirectMatrix(_Value.DirectMatrix)
	{

	}

	float4x4(const DirectX::XMMATRIX& _Value)
		: DirectMatrix(_Value)
	{

	}

	~float4x4()
	{

	}
	
	float4x4 operator=(const float4x4& _Value)
	{
		DirectMatrix = _Value.DirectMatrix;

		return *this;
	}

	float4x4 operator*(const float4x4& _Value)
	{
		return DirectX::XMMatrixMultiply(DirectMatrix, _Value.DirectMatrix);
	}

	float4x4& operator*=(const float4x4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixMultiply(DirectMatrix, _Value.DirectMatrix);

		return *this;
	}

	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();
	}

	// X,Y Scaling
	void Scaling2D(const float _Value)
	{
		DirectMatrix = DirectX::XMMatrixScalingFromVector(float4(_Value, _Value, 1.0f).DirectVector);
	}
	void Scaling(const float _Value)
	{
		DirectMatrix = DirectX::XMMatrixScalingFromVector(float4(_Value, _Value, _Value).DirectVector);
	}
	void Scaling(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixScalingFromVector(_Value.DirectVector);
	}

	void Translation(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);
	}

	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(DirectMatrix);
	}

	void RotationDeg(const float4& _Value)
	{
		RotationRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationXDeg(const float& _Value)
	{
		RotationXRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationYDeg(const float& _Value)
	{
		RotationYRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationZDeg(const float& _Value)
	{
		RotationZRad(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationRad(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Value.DirectVector);
	}

	void RotationXRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationX(_Value);
	}
	void RotationYRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationY(_Value);
	}
	void RotationZRad(const float& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationZ(_Value);
	}


	// 뷰행렬

	void ViewPortCenter(float _ScreenX, float _ScreenY, float _StartX,
		float _StartY, float _MinZ, float _MaxZ)
	{
		Identity();

		Arr2D[0][0] = _ScreenX * 0.5f;
		Arr2D[1][1] = _ScreenY * 0.5f;
		Arr2D[2][2] = _MaxZ - _MinZ;
		Arr2D[3][0] = _StartX + Arr2D[0][0];
		Arr2D[3][1] = Arr2D[1][1] + _StartY;
		Arr2D[3][2] = _MinZ;
	}

	// LootAt은 내가 어떠한 물체를 바라보고있다
	void ViewAtLH(const float4& _EyePos, const float4& _EyeFocus, const float4& _EyeUp)
	{
		// _EyePos		: 어디서 보고있는가
		// _EyeFocus	: 어디를 보고있는가
		// _EyeUp		: 그 상태에서 내 머리위 방향은 어디인가?
	
		// 내부구조
		// float4 ZPivot = _EyeFocus - _EyePos;
		// ZPivot.Normalize3D();
		   
		// float4 EyeUp = _EyeUp.NormalizeReturn3D();
		   
		// float4 XPivot = float4::Cross3D(EyeUp, ZPivot);
		// XPivot.Normalize3D();
		   
		// float4 YPivot = float4::Cross3D(ZPivot, XPivot);
		// YPivot.Normalize3D();
		   
		   
		// 내가 원점으로 이동한만큼 물체는 반대로 이동해야한다.
		// float4 NegEyePosition = -_EyePos;
		   
		// float D0 = float4::Dot3D(XPivot, NegEyePosition);
		// float D1 = float4::Dot3D(YPivot, NegEyePosition);
		// float D2 = float4::Dot3D(ZPivot, NegEyePosition);
		   
		// float4x4 ViewMat;
		   
		// 이 행렬은 현재 정방향 회전, 내가 회전한만큼 물체가 더 회전하게됨
		// ViewMat.vx = float4(XPivot.x, XPivot.y, XPivot.z, D0);
		// ViewMat.vy = float4(YPivot.x, YPivot.y, YPivot.z, D1);
		// ViewMat.vz = float4(ZPivot.x, ZPivot.y, ZPivot.z, D2);
		// ViewMat.vw = { 0.0f, 0.0f, 0.0f, 1.0f };
		   
		// 전치를 하면 반대방향으로 회전하게 된다.
		// ViewMat.Transpose();
		   
		// ViewMat : 우리가 구하고자했던 뷰행렬이 된다.
		
		// return ViewMat;

		// cos -sin
		// sin	cos

		// 뷰행렬의 목적 : 바라보는 사람이 원점이 되게 모든 물체에 영향을 주는 행렬

		DirectMatrix = DirectX::XMMatrixLookAtLH(_EyePos.DirectVector, _EyeFocus.DirectVector, _EyeUp.DirectVector);
	}

	// LootTo는 내가 이 방향으로 바라보고있다
	void ViewToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePos.DirectVector, _EyeDir.DirectVector, _EyeUp.DirectVector);
	}

	// 투영행렬
	// 1. 원근감을 주는 투영행렬 원근투영
	// 2. 주지 않는 투영행렬 직교투영

	// -1~1로 들어가기 직전으로 바꾼다.

	void PerspectiveFovLH(
		float _FovAngleY,
		float _Width,
		float _Height,
		float _NearZ,
		float _FarZ
	)
	{
		PerspectiveFovLH(_FovAngleY * GameEngineMath::DegreeToRadian, _Width / _Height, _NearZ, _FarZ);
	}

	void PerspectiveFovLH(
		float _FovAngleY,
		float _AspectRatio,
		float _NearZ,
		float _FarZ
	)
	{

		/*float Height = cos(0.5f * _FovAngleY) / sin(0.5f * _FovAngleY);
		float Width = Height / _AspectRatio;
		float fRange = _FarZ / (_FarZ - _NearZ);*/

		/*float    SinFov;
		float    CosFov;
		XMScalarSinCos(&SinFov, &CosFov, 0.5f * FovAngleY);

		float Height = CosFov / SinFov;
		float Width = Height / AspectRatio;
		float fRange = FarZ / (FarZ - NearZ);

		XMMATRIX M;
		M.m[0][0] = Width;
		M.m[0][1] = 0.0f;
		M.m[0][2] = 0.0f;
		M.m[0][3] = 0.0f;

		M.m[1][0] = 0.0f;
		M.m[1][1] = Height;
		M.m[1][2] = 0.0f;
		M.m[1][3] = 0.0f;

		M.m[2][0] = 0.0f;
		M.m[2][1] = 0.0f;
		M.m[2][2] = fRange;
		M.m[2][3] = 1.0f;

		M.m[3][0] = 0.0f;
		M.m[3][1] = 0.0f;
		M.m[3][2] = -fRange * NearZ;
		M.m[3][3] = 0.0f;
		return M;*/

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngleY, _AspectRatio, _NearZ, _FarZ);
	}

	void OrthographicLH(
		float _Width,
		float _Height,
		float _NearZ,
		float _FarZ
	)
	{
		DirectMatrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _NearZ, _FarZ);
	}
};
