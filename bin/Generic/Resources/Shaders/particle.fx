//--------------------------------------------------------------------------------------------------
// Particle System (rev 2)
//--------------------------------------------------------------------------------------------------
#if SH_X360
#define COLOR_CENTER COLOR_center
#else
#define COLOR_CENTER COLOR
#endif


//--------------------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------------------
#include "lib\platform.fxh"
#include "lib\lighting.fxh"


//--------------------------------------------------------------------------------------------------
// Constants
//--------------------------------------------------------------------------------------------------
static const float      Shininess = 5.0f;


//--------------------------------------------------------------------------------------------------
// Parametters
//--------------------------------------------------------------------------------------------------
float4x4                mWorldView;
float4x4                mWorldViewProj;
float4                  LightVector;
float4                  LightColor;
float4                  AnimatedTextureBlendFactor;


//-----------------------------------------------------------------------------
// Texture samplers
//-----------------------------------------------------------------------------
#if SH_DX11
Texture2D DiffuseMap;
Texture2D NormalMap;
Texture2D Animated1Map;
Texture2D Animated2Map;
SamplerState SamplerParticle
{
	FILTER		= Min_Mag_Linear_Mip_Point;
	AddressU	= CLAMP;
	AddressV	= CLAMP;
};
#else // SH_DX11
texture DiffuseMap;
sampler2D DiffuseMapSampler = sampler_state
{
	Texture = <DiffuseMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};

texture NormalMap;
sampler2D NormalMapSampler = sampler_state
{
	Texture = <NormalMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};

texture Animated1Map;
sampler2D Animated1MapSampler = sampler_state
{
	Texture = <Animated1Map>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};

texture Animated2Map;
sampler2D Animated2MapSampler = sampler_state
{
	Texture = <Animated2Map>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = POINT;
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};
#endif // SH_DX11


//--------------------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------------------
struct VS_INPUT
{
    float3 position                 : POSITION;
    float2 texcoord                 : TEXCOORD0;
    float4 color                    : COLOR;
};

struct VS_OUTPUT
{
	float4	position                : POSITION;
	float2	texcoord				: TEXCOORD0;
	float4  color                   : COLOR;
};

struct PS_INPUT
{
	float4	position                : POSITION;
	float2	texcoord				: TEXCOORD0;
	float4  color                   : COLOR_CENTER;
};

struct VS_NORMALMAP_OUTPUT
{
	float4	position                : POSITION;
	float4  color                   : COLOR;
	float2	texcoord				: TEXCOORD0;
	float3  Ldir                    : TEXCOORD1;
	float3  Vdir                    : TEXCOORD2;

};

struct PS_NORMALMAP_INPUT
{
	float4	position				: POSITION;
	float4  color                   : COLOR_CENTER;
	float2	texcoord				: TEXCOORD0;
	float3  Ldir                    : TEXCOORD1;
	float3  Vdir                    : TEXCOORD2;
};


//--------------------------------------------------------------------------------------------------
// Vertex shader 
//--------------------------------------------------------------------------------------------------
VS_OUTPUT vs(VS_INPUT vIn)
{
	VS_OUTPUT vOut;
	
	float4 Pos = float4(vIn.position, 1.0);
	
	vOut.position = mul( Pos, mWorldViewProj);
	vOut.texcoord = vIn.texcoord;
	vOut.color = vIn.color;
	
        return vOut;
}
VS_NORMALMAP_OUTPUT vs_normalmap(VS_INPUT vIn)
{
	VS_NORMALMAP_OUTPUT vOut;
	
	float4 Pos = float4(vIn.position, 1.0);
	
	vOut.position = mul( Pos, mWorldViewProj);
	vOut.texcoord = vIn.texcoord;
	vOut.color = vIn.color;
	
    float3 WorldViewPos = mul(Pos, mWorldView).xyz;
    vOut.Ldir = normalize(mul(float4( LightVector.xyz, 0), mWorldView).xyz - WorldViewPos);
    vOut.Vdir = normalize(-WorldViewPos);
	
        return vOut;
}


//--------------------------------------------------------------------------------------------------
// Pixel shader 
//--------------------------------------------------------------------------------------------------
#if SH_DX11
float4 ps(PS_INPUT vIn, uniform bool bAnimMap) : SV_Target
#else // SH_DX11
float4 ps(PS_INPUT vIn, uniform bool bAnimMap) : COLOR
#endif // SH_DX11
{
        float4 texcolor = vIn.color;
		
		if (bAnimMap)
        {
#if SH_DX11
        	float4 texcolor1 = Animated1Map.Sample(SamplerParticle, vIn.texcoord);
	        float4 texcolor2 = Animated2Map.Sample(SamplerParticle, vIn.texcoord);
#else // SH_DX11
        	float4 texcolor1 = tex2D(Animated1MapSampler, vIn.texcoord);
	        float4 texcolor2 = tex2D(Animated2MapSampler, vIn.texcoord);
#endif // SH_DX11
        	texcolor *= lerp(texcolor1, texcolor2, AnimatedTextureBlendFactor.x);
        }
        else
        {
#if SH_DX11
	        texcolor *= DiffuseMap.Sample(SamplerParticle, vIn.texcoord);
#else // SH_DX11
	        texcolor *= tex2D(DiffuseMapSampler, vIn.texcoord);
#endif // SH_DX11
        }
	
	return texcolor;
	//return vIn.color;
}

float4 ps_normalmap(PS_NORMALMAP_INPUT vIn, uniform bool bAnimMap) : COLOR
{
        float4 texcolor = vIn.color;
        if (bAnimMap)
        {
#if SH_DX11
        	float4 texcolor1 = Animated1Map.Sample(SamplerParticle, vIn.texcoord);
	        float4 texcolor2 = Animated2Map.Sample(SamplerParticle, vIn.texcoord);
#else // SH_DX11
        	float4 texcolor1 = tex2D(Animated1MapSampler, vIn.texcoord);
	        float4 texcolor2 = tex2D(Animated2MapSampler, vIn.texcoord);
#endif // SH_DX11
        	texcolor *= lerp(texcolor1, texcolor2, AnimatedTextureBlendFactor.x);
        }
        else
        {
#if SH_DX11
	        texcolor *= DiffuseMap.Sample(SamplerParticle, vIn.texcoord);
#else // SH_DX11
	        texcolor *= tex2D(DiffuseMapSampler, vIn.texcoord);
#endif // SH_DX11
        }

#if SH_DX11
	float3 normal = UnpackNormalMap(NormalMap, SamplerParticle, vIn.texcoord);
#else // SH_DX11
	float3 normal = UnpackNormalMap(NormalMapSampler, vIn.texcoord);
#endif // SH_DX11
	float3 H = normalize(vIn.Ldir + vIn.Vdir);
	float4 lighting = lit(dot(vIn.Ldir, normal), dot(H, normal), Shininess);
	texcolor.rgb *= (lighting.y + lighting.z) * LightColor.rgb;
	
    return texcolor;
}

#if !SH_DX11
//--------------------------------------------------------------------------------------------------
// Techniques definition
//--------------------------------------------------------------------------------------------------
technique NoNormalNoAnim
{ 
	pass 
	{		
		VertexShader     = compile vs_3_0 vs();
		PixelShader      = compile ps_3_0 ps(false);
	}
}

technique NormalNoAnim
{ 
	pass 
	{		
		VertexShader     = compile vs_3_0 vs_normalmap();
		PixelShader      = compile ps_3_0 ps_normalmap(false);
	}
}

technique NoNormalAnim
{ 
	pass 
	{		
		VertexShader     = compile vs_3_0 vs();
		PixelShader      = compile ps_3_0 ps(true);
	}
}

technique NormalAnim
{ 
	pass 
	{		
		VertexShader     = compile vs_3_0 vs_normalmap();
		PixelShader      = compile ps_3_0 ps_normalmap(true);
	}
}
#else
//--------------------------------------------------------------------------------------------------
// Techniques definition
//--------------------------------------------------------------------------------------------------
technique11 NoNormalNoAnim
{ 
	pass 
	{		
		SetVertexShader( CompileShader( vs_4_0, vs() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, ps(false) ) );
	}
}

technique11 NormalNoAnim
{ 
	pass 
	{	
		SetVertexShader( CompileShader( vs_4_0, vs_normalmap() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, ps_normalmap(false) ) );	
	}
}

technique11 NoNormalAnim
{ 
	pass 
	{		
		SetVertexShader( CompileShader( vs_4_0, vs() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, ps(true) ) );
	}
}

technique11 NormalAnim
{ 
	pass 
	{		
		SetVertexShader( CompileShader( vs_4_0, vs_normalmap() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, ps_normalmap(true) ) );
	}
}
#endif
