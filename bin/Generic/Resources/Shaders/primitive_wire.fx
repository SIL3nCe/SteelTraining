//--------------------------------------------------------------------------------------------------
// Pick buffer
//--------------------------------------------------------------------------------------------------

#include "lib\platform.fxh"

//--------------------------------------------------------------------------------------------------
// Parameters
//--------------------------------------------------------------------------------------------------
float4x4 mWorldViewProjection : WORLDVIEWPROJECTION;
float4   DiffuseColor         : DiffuseColor;

//--------------------------------------------------------------------------------------------------
// Vertex shader input structure
//--------------------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4	position			: POSITION;				// Vertex position
	float2	texcoord			: TEXCOORD0;			// Texture coordinates

#if !SH_DX11
	float3	tangent				: TANGENT;				// Tangent (in local space)
	float3	binormal			: BINORMAL;				// Binormal (in local space)
	float3	normal				: NORMAL;				// Normal (in local space)
#endif
	float4	color				: COLOR;				// Vertex color
};

//--------------------------------------------------------------------------------------------------
// Vertex shader input structure
//--------------------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	position			: POSITION;				// Vertex position
	float4  color               : COLOR;				// Vertex color
};

//--------------------------------------------------------------------------------------------------
// Vertex shader code
//--------------------------------------------------------------------------------------------------
VS_OUTPUT vs(VS_INPUT vIn)
{
	VS_OUTPUT vOut;
	vOut.position = mul(vIn.position, mWorldViewProjection);
	vOut.color    = vIn.color;
	return(vOut);
}

//--------------------------------------------------------------------------------------------------
// Pixel shader code
//--------------------------------------------------------------------------------------------------
float4 ps(VS_OUTPUT vIn) : COLOR
{
#if !SH_DX11
	return(DiffuseColor * vIn.color);
#else
	return(DiffuseColor ); // The stream is not compliant with the input in DX11 and produce invalid IA.
#endif
}

#if !SH_DX11
//--------------------------------------------------------------------------------------------------
// Techniques definition
//--------------------------------------------------------------------------------------------------
technique DefaultTechnique
{
    Pass DefaultPass
    {
        MultiSampleAntialias = FALSE;

        VertexShader         = compile vs_3_0 vs();
        PixelShader          = compile ps_3_0 ps();
	}
}
#else

//--------------------------------------------------------------------------------------------------
// Techniques definition
//--------------------------------------------------------------------------------------------------
technique11 DefaultTechnique
{
    Pass DefaultPass
    {
		SetVertexShader( CompileShader( vs_4_0, vs() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, ps() ) );
	}
}
#endif
