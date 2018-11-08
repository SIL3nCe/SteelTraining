
#include "lib/platform.fxh"

#if SH_DX11
Texture2D InputTextureColor;
SamplerState InputTextureColorSampler
{
	Filter = Min_Mag_Linear_Mip_Point;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};
#else
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
texture InputTextureColor;
sampler2D InputTextureColorSampler = sampler_state
{
	Texture = <InputTextureColor>;
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
float4 BlitPS( in VS_OUTPUT pIn) : SV_TARGET
#else
float4 BlitPS( in VS_OUTPUT pIn) : COLOR
#endif
{
	// return float4(0.5,0.2,0.8,1.0);
#if SH_DX11
	return InputTextureColor.Sample(InputTextureColorSampler, pIn.vTexcoord).rgba;
#else
	return tex2D(InputTextureColorSampler, pIn.vTexcoord);
#endif 
}

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
#if SH_DX11
technique11 Blit
{
    pass
    {
		SetVertexShader(CompileShader( vs_4_0, BlitVS()));
		SetGeometryShader( NULL );
        SetPixelShader(CompileShader( ps_4_0, BlitPS()));
    }
}
#else
technique Blit
{
    pass
    {
		VertexShader = compile vs_3_0 BlitVS();
        PixelShader  = compile ps_3_0 BlitPS();
    }
}
#endif