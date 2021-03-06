#include "CbufferHeader.fx"


cbuffer TextureCutData : register(b1)
{
    // UV값으로 float4를 수신하며 x,y에 위치값, z,w에 크기값을 받아옴
    float2 TextureCutDataPos;
    float2 TextureCutDataSize;
};

struct VertexIn
{
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};


VertexOut ProgressBar_VS(VertexIn _in)
{
    VertexOut Out;

    Out.Position = _in.Position;

    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);

    Out.Texcoord.x = (_in.Texcoord.x * TextureCutDataSize.x) + TextureCutDataPos.x;
    Out.Texcoord.y = (_in.Texcoord.y * TextureCutDataSize.y) + TextureCutDataPos.y;

    return Out;
}

cbuffer CorrectResultColor : register(b0)
{
    float4 vMulColor;
    float4 vPlusColor;
};

cbuffer ProgressBarCBuffer : register(b1)
{
    float Percent;
    int ProgressDirection;
    float Empty1;
    float Empty2;
};


Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

// UI ProgressBar Shader Function(Pixel Shader)
float4 ProgressBar_PS(VertexOut _in) : SV_Target0
{
    if (ProgressDirection == 0 && Percent < _in.Texcoord.y)
    {
        clip(-1); // Up
    }
    else if (ProgressDirection == 1 && 1.0f - Percent > _in.Texcoord.y)
    {
        clip(-1); // Down
    }
    else if (ProgressDirection == 2 && Percent < _in.Texcoord.x)
    {
        clip(-1); // Left
    }
    else if (ProgressDirection == 3 && 1.0f - Percent > _in.Texcoord.x)
    {
        clip(-1); // Right
    }
    
    float4 Color = (Tex.Sample(Smp, _in.Texcoord.xy) * vMulColor);
    
    Color += vPlusColor;
    
    return Color;
}
