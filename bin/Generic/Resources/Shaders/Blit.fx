
#include "lib/platform.fxh"

#if SH_DX11
Texture2D SourceTexture;
SamplerState SourceTextureSampler
{
	Filter = Min_Mag_Linear_Mip_Point;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};
#else
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
texture SourceTexture;
sampler2D SourceTextureSampler = sampler_state
{
	Texture = <SourceTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};
#endif

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
struct VS_INPUT
{
#if SH_DX11
	float4 vPosition : SV_POSITION;
#else
	float4 vPosition : POSITION;
#endif
	float2 vTexcoord : TEXCOORD;
};

struct VS_OUTPUT
{
#if SH_DX11
	float4 vPosition : SV_POSITION;
#else
	float4 vPosition : POSITION;
#endif
	float2 vTexcoord : TEXCOORD;
};

uniform float fMultiplier;

VS_OUTPUT BlitVS(VS_INPUT vIn)
{
	VS_OUTPUT vOut;
	vOut.vTexcoord = vIn.vTexcoord;
	vOut.vPosition = vIn.vPosition;

	return(vOut);
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
#if SH_DX11
float4 ps_4_channel( in VS_OUTPUT pIn) : SV_TARGET
#else
float4 ps_4_channel( in VS_OUTPUT pIn) : COLOR
#endif
{
#if SH_DX11
	float4 texel_color = SourceTexture.Sample(SourceTextureSampler, pIn.vTexcoord);
#else
	float4 texel_color = tex2D(SourceTextureSampler, pIn.vTexcoord);
#endif

	return float4(texel_color.r * fMultiplier, texel_color.g * fMultiplier, texel_color.b * fMultiplier, texel_color.a);
}

#if SH_DX11
float4 ps_3_channel( in VS_OUTPUT pIn) : SV_TARGET
#else
float4 ps_3_channel( in VS_OUTPUT pIn) : COLOR
#endif
{
#if SH_DX11
	float3 texel_color = SourceTexture.Sample(SourceTextureSampler, pIn.vTexcoord).rgb;
#else
	float3 texel_color = tex2D(SourceTextureSampler, pIn.vTexcoord).rgb;
#endif 

	return float4(texel_color.r * fMultiplier, texel_color.g * fMultiplier, texel_color.b * fMultiplier, 1.0);
}

#if SH_DX11
float4 ps_2_channel( in VS_OUTPUT pIn) : SV_TARGET
#else
float4 ps_2_channel( in VS_OUTPUT pIn) : COLOR
#endif
{
#if SH_DX11
	float2 texel_color = SourceTexture.Sample(SourceTextureSampler, pIn.vTexcoord).rg;
#else
	float2 texel_color = tex2D(SourceTextureSampler, pIn.vTexcoord).rg;
#endif 

	return float4(texel_color.r * fMultiplier, texel_color.g * fMultiplier, 0.0, 1.0);
}

#if SH_DX11
float4 ps_1_channel( in VS_OUTPUT pIn) : SV_TARGET
#else
float4 ps_1_channel( in VS_OUTPUT pIn) : COLOR
#endif
{
#if SH_DX11
	float texel_color = SourceTexture.Sample(SourceTextureSampler, pIn.vTexcoord).r * fMultiplier;
#else
	float texel_color = tex2D(SourceTextureSampler, pIn.vTexcoord).r * fMultiplier;
#endif 
	return float4(texel_color, texel_color, texel_color, 1.0);
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
#if SH_DX11
technique11 Blit4Channel
{
    pass
    {
		SetVertexShader(CompileShader( vs_4_0, BlitVS()));
		SetGeometryShader( NULL );
        SetPixelShader(CompileShader( ps_4_0, ps_4_channel()));
    }
}
technique11 Blit3Channel
{
    pass
    {
		SetVertexShader(CompileShader( vs_4_0, BlitVS()));
		SetGeometryShader( NULL );
        SetPixelShader(CompileShader( ps_4_0, ps_3_channel()));
    }
}
technique11 Blit2Channel
{
    pass
    {
		SetVertexShader(CompileShader( vs_4_0, BlitVS()));
		SetGeometryShader( NULL );
        SetPixelShader(CompileShader( ps_4_0, ps_2_channel()));
    }
}
technique11 Blit1Channel
{
    pass
    {
		SetVertexShader(CompileShader( vs_4_0, BlitVS()));
		SetGeometryShader( NULL );
        SetPixelShader(CompileShader( ps_4_0, ps_1_channel()));
    }
}
#else
technique Blit4Channel
{
    pass
    {
		VertexShader = compile vs_3_0 BlitVS();
        PixelShader  = compile ps_3_0 ps_4_channel();
    }
}

technique Blit3Channel
{
    pass
    {
		VertexShader = compile vs_3_0 BlitVS();
        PixelShader  = compile ps_3_0 ps_3_channel();
    }
}

technique Blit2Channel
{
    pass
    {
		VertexShader = compile vs_3_0 BlitVS();
        PixelShader  = compile ps_3_0 ps_2_channel();
    }
}

technique Blit1Channel
{
    pass
    {
		VertexShader = compile vs_3_0 BlitVS();
        PixelShader  = compile ps_3_0 ps_1_channel();
    }
}
#endif