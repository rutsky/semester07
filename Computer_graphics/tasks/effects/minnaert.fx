// minnaert.fx
// Minnaert shading.
// Vladimir Rutsky, 4057/2
// 22.02.2010

// Based on Basic HLSL DirectX example.

float g_MinnaertExp;

float4 g_MaterialAmbientColor;
float4 g_MaterialDiffuseColor;

float3 g_LightDir;
float4 g_LightDiffuse;
float4 g_LightAmbient;

float3 g_EyePos;

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

//
// Diffuse
//
 
struct Diffuse_VS_OUTPUT
{
  float4 Position  : POSITION;
  float4 Diffuse   : COLOR0;
  float2 TextureUV : TEXCOORD0;
};


Diffuse_VS_OUTPUT DiffuseVS( float4 vPos       : POSITION, 
                             float3 vNormal    : NORMAL,
                             float2 vTexCoord0 : TEXCOORD0,
                             uniform bool bUseTexture )
{
  Diffuse_VS_OUTPUT output;
  float3 vNormalWorldSpace;
  
  output.Position = mul(vPos, g_mWorldViewProjection);
    
  vNormalWorldSpace = normalize(mul(vNormal, (float3x3)g_mWorld));
  
  float3 vTotalLightDiffuse = (float3)(g_LightDiffuse * max(0, dot(vNormalWorldSpace, normalize(g_LightDir))));
        
  output.Diffuse.rgb = (float3)g_MaterialDiffuseColor * vTotalLightDiffuse + 
                       (float3)g_MaterialAmbientColor * (float3)g_LightAmbient;
  output.Diffuse.a = 1.0f; 
    
  output.TextureUV = vTexCoord0; 

  return output;    
}

struct Diffuse_PS_OUTPUT
{
  float4 RGBColor : COLOR0;
};

Diffuse_PS_OUTPUT DiffusePS( Diffuse_VS_OUTPUT In,
                             uniform bool bUseTexture ) 
{ 
  Diffuse_PS_OUTPUT output;

  if (bUseTexture)
    output.RGBColor = tex2D(ColorTextureSampler, In.TextureUV) * In.Diffuse;
  else
    output.RGBColor = In.Diffuse;

  return output;
}

//
// Diffuse with bump
//
 
struct DiffuseBump_VS_OUTPUT
{
  float4 Position  : POSITION;
  float2 TextureUV : TEXCOORD0;
  
  float3 tangentWorld  : TEXCOORD1;
  float3 binormalWorld : TEXCOORD2;
  float3 normalWorld   : TEXCOORD3;
};

DiffuseBump_VS_OUTPUT DiffuseBumpVS( float4 vPos       : POSITION, 
                                     float3 vNormal    : NORMAL,
                                     float3 vTangent   : TANGENT,
                                     float3 vBinormal  : BINORMAL,
                                     float2 vTexCoord0 : TEXCOORD0,
                                     uniform bool bUseTexture )
{
  DiffuseBump_VS_OUTPUT output;

  output.Position = mul(vPos, g_mWorldViewProjection);

  output.TextureUV = vTexCoord0; 

  output.tangentWorld  = normalize(mul(vTangent,  (float3x3)g_mWorld));
  output.binormalWorld = normalize(mul(vBinormal, (float3x3)g_mWorld));
  output.normalWorld   = normalize(mul(vNormal,   (float3x3)g_mWorld));
    
  return output;    
}

struct DiffuseBump_PS_OUTPUT
{
  float4 RGBColor : COLOR0;
};

DiffuseBump_PS_OUTPUT DiffuseBumpPS( DiffuseBump_VS_OUTPUT In,
                                     uniform bool bUseTexture ) 
{ 
  DiffuseBump_PS_OUTPUT output;
  
  float3x3 normalBumpCSToWorldCS = float3x3(In.tangentWorld, In.binormalWorld, In.normalWorld);
  
  float3 normalInBump = normalize((float3)tex2D(NormalTextureSampler, In.TextureUV)) * 2.0 - 1.0;
  //float3 normalInBump = normalize(tex2D(NormalTextureSampler, In.TextureUV));
  float3 normalWorld = mul(normalInBump, normalBumpCSToWorldCS);
  
  float3 vTotalLightDiffuse = (float3)(g_LightDiffuse * max(0, dot(normalWorld, normalize(g_LightDir))));
        
  float4 color;
  color.rbg = (float3)g_MaterialDiffuseColor * vTotalLightDiffuse + 
              (float3)g_MaterialAmbientColor * (float3)g_LightAmbient;
  //color.rgb = normalInBump;
  color.a = 1.0f;

  if (bUseTexture)
    output.RGBColor = tex2D(ColorTextureSampler, In.TextureUV) * color;
  else
    output.RGBColor = color;

  return output;
}

//
// Minnaert
//
 
struct Minnaert_VS_OUTPUT
{
  float4 Position  : POSITION;
  float2 TextureUV : TEXCOORD0;
  
  float3 tangentWorld  : TEXCOORD1;
  float3 binormalWorld : TEXCOORD2;
  float3 normalWorld   : TEXCOORD3;
  
  float3 positionWorld : TEXCOORD4;
};

Minnaert_VS_OUTPUT MinnaertVS( float4 vPos       : POSITION, 
                               float3 vNormal    : NORMAL,
                               float3 vTangent   : TANGENT,
                               float3 vBinormal  : BINORMAL,
                               float2 vTexCoord0 : TEXCOORD0,
                               uniform bool bUseTexture )
{
  Minnaert_VS_OUTPUT output;

  output.Position = mul(vPos, g_mWorldViewProjection);

  output.TextureUV = vTexCoord0; 

  output.tangentWorld  = normalize(mul(vTangent,  (float3x3)g_mWorld));
  output.binormalWorld = normalize(mul(vBinormal, (float3x3)g_mWorld));
  output.normalWorld   = normalize(mul(vNormal,   (float3x3)g_mWorld));
  
  output.positionWorld = (float3)mul(vPos, g_mWorld); // TODO: Truncating division coefficient.
    
  return output;    
}

struct Minnaert_PS_OUTPUT
{
  float4 RGBColor : COLOR0;
};

Minnaert_PS_OUTPUT MinnaertPS( Minnaert_VS_OUTPUT In,
                               uniform bool bUseTexture ) 
{ 
  Minnaert_PS_OUTPUT output;
  
  float3x3 normalBumpCSToWorldCS = float3x3(In.tangentWorld, In.binormalWorld, In.normalWorld);
  
  float3 normalInBump = normalize((float3)tex2D(NormalTextureSampler, In.TextureUV)) * 2.0 - 1.0;
  //float3 normalInBump = normalize(tex2D(NormalTextureSampler, In.TextureUV));
  float3 normalWorld = mul(normalInBump, normalBumpCSToWorldCS);
  
  float3 eyeDir = normalize(g_EyePos - In.positionWorld);
  float3 diffuseCoef = 
    saturate(pow(max(0.00001f, dot(normalWorld, normalize(g_LightDir))), g_MinnaertExp)) *
    saturate(pow(max(0.00001f, dot(normalWorld, eyeDir)), 1.0 - g_MinnaertExp));
  float3 vTotalLightDiffuse = g_LightDiffuse * diffuseCoef;
        
  float4 color;
  color.rbg = (float3)(g_MaterialDiffuseColor * vTotalLightDiffuse + 
                       g_MaterialAmbientColor * g_LightAmbient);
  //color.rgb = normalInBump;
  color.a = 1.0f;

  if (bUseTexture)
    output.RGBColor = tex2D(ColorTextureSampler, In.TextureUV) * color;
  else
    output.RGBColor = color;

  return output;
}

//
// Techniques
//

technique RenderSceneDiffuseTextured
{
  pass P0
  {          
    VertexShader = compile vs_2_0 DiffuseVS(true);
    PixelShader  = compile ps_2_0 DiffusePS(true);
  }
}

technique RenderSceneDiffuseNotTextured
{
  pass P0
  {          
    VertexShader = compile vs_2_0 DiffuseVS(false);
    PixelShader  = compile ps_2_0 DiffusePS(false);
  }
}

technique RenderSceneDiffuseBumpTextured
{
  pass P0
  {          
    VertexShader = compile vs_2_0 DiffuseBumpVS(true);
    PixelShader  = compile ps_2_0 DiffuseBumpPS(true);
  }
}

technique RenderSceneDiffuseBumpNotTextured
{
  pass P0
  {          
    VertexShader = compile vs_2_0 DiffuseBumpVS(false);
    PixelShader  = compile ps_2_0 DiffuseBumpPS(false);
  }
}

technique RenderSceneMinnaertTextured
{
  pass P0
  {          
    VertexShader = compile vs_2_0 MinnaertVS(true);
    PixelShader  = compile ps_2_0 MinnaertPS(true);
  }
}

technique RenderSceneMinnaertNotTextured
{
  pass P0
  {          
    VertexShader = compile vs_2_0 MinnaertVS(false);
    PixelShader  = compile ps_2_0 MinnaertPS(false);
  }
}
