#include "CBufferHeader.fx"

float4 Color_VS(float4 pos : POSITION) : SV_POSITION
{
    pos.w = 1.0f;

    pos = mul(pos, WVP);

    return pos;
}

cbuffer ResultColor : register(b0)
{
    float4 vColor;
}

float4 Color_PS(float4 pos : SV_POSITION) : SV_Target0
{
    return vColor;
}
