// minnaert.fx
// Minnaert shading.
// Vladimir Rutsky, 4057/2
// 22.02.2010

// Based on Basic HLSL DirectX example.

float g_MinnaertK;

float4 g_MaterialAmbientColor;
float4 g_MaterialDiffuseColor;

float3 g_LightDir;
float4 g_LightDiffuse;
float4 g_LightAmbient;

texture g_ColorTexture;
texture g_NormalTexture;

float4x4 g_mWorld;
float4x4 g_mWorldViewProjection;

sampler ColorTextureSampler = 
sampler_state
{
  Texture = <g_ColorTexture>;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

sampler NormalTextureSampler = 
sampler_state
{
  Texture = <g_NormalTexture>;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

struct VS_OUTPUT
{
  float4 Position  : POSITION;
  float4 Diffuse   : COLOR0;
  float2 TextureUV : TEXCOORD0;
};


VS_OUTPUT DiffuseVS( float4 vPos       : POSITION, 
                     float3 vNormal    : NORMAL,
                     float2 vTexCoord0 : TEXCOORD0,
                     uniform bool bUseTexture )
{
  VS_OUTPUT Output;
  float3 vNormalWorldSpace;
  
  Output.Position = mul(vPos, g_mWorldViewProjection);
    
  vNormalWorldSpace = normalize(mul(vNormal, (float3x3)g_mWorld));
  
  float3 vTotalLightDiffuse = g_LightDiffuse * max(0, dot(vNormalWorldSpace, normalize(g_LightDir)));
        
  Output.Diffuse.rgb = g_MaterialDiffuseColor * vTotalLightDiffuse + 
                       g_MaterialAmbientColor * g_LightAmbient;   
  Output.Diffuse.a = 1.0f; 
    
  if (bUseTexture) 
    Output.TextureUV = vTexCoord0; 
  else
    Output.TextureUV = 0; 
    
  return Output;    
}


struct PS_OUTPUT
{
  float4 RGBColor : COLOR0;
};


PS_OUTPUT DiffusePS( VS_OUTPUT In,
                     uniform bool bUseTexture ) 
{ 
  PS_OUTPUT Output;

  if (bUseTexture)
    Output.RGBColor = tex2D(ColorTextureSampler, In.TextureUV) * In.Diffuse;
  else
    Output.RGBColor = In.Diffuse;

  return Output;
}


technique RenderSceneWithTexturedDiffuse
{
  pass P0
  {          
    VertexShader = compile vs_2_0 DiffuseVS(true);
    PixelShader  = compile ps_2_0 DiffusePS(true);
  }
}

technique RenderSceneWithNotTexturedDiffuse
{
  pass P0
  {          
    VertexShader = compile vs_2_0 DiffuseVS(false);
    PixelShader  = compile ps_2_0 DiffusePS(false);
  }
}

