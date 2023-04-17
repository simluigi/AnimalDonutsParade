/*============================================
DirectX11 Shader Lesson : pixelLighting.hlsl
(set as pixel shader, %Filename.cso)
Author: Sim Luigi
Last Updated: 2020.09.09
*============================================*/

#include "common.hlsl"

Texture2D g_Texture : register(t0); // texture 0 (can use multiple for multiple textures)
SamplerState g_SamplerState : register(s0); // state 0

// calculates PER PIXEL; avoid using conditional statements or system processing speed plummets
// 1ピクセルごと処理：if分などを使うと処理速度がかなり低下！使わない方がいい

// Information the same as unlitTexture

void main(in PS_IN In, out float4 outDiffuse : SV_Target)           // SV_Target: final color output
{
    // 2020.09.15
    float4 normal = normalize(In.Normal);                           // MUST include. See diagram in 2020_09_15_PixelLighting
    
    // ランバート拡散照明
    // Lambert Diffuse Lighting
    //float light = -dot(normal.xyz, Light.Direction.xyz);
    //light = saturate(light);
    

    // 2020.09.11
    // ハーフランバート
    // Half-Lambert (Diffuse Wrap)
    float light = 0.5 - dot(normal.xyz, Light.Direction.xyz) * 0.5;
       
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord); // Texture Mapping
    outDiffuse.rgb *= In.Diffuse.rgb * light; // Can also use addition +, but multiplication * is more common 
    outDiffuse.a *= In.Diffuse.a;
    

    // 2020.09.15
    // スペキュラー（フォン）
    // specular(Phong)
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; // .xyz can be done in hlsl files
    eyev = normalize(eyev);
    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 60); // larger number = wider area, lower concentration (replace 60 with Material.Shininess)
    
    // adjust multiplication for roughness (higher =rougher
    //outDiffuse.rgb += specular * 0.5f;     // addition, not multiplication
    outDiffuse.rgb += specular;
     
       
    // Distance fog
    // this creates fog relative to player position (does not create a fog object)
    // align with floor color and background color shaders
    //float dist = distance(In.WorldPosition.xyz, CameraPosition.xyz); // further from camera, thicker fog
    //float fog = saturate(dist / 30.0f); // adjust value for fog density   
    //outDiffuse.rgb = outDiffuse.rgb * (1.0f - fog) + float3(0.6f, 0.8f, 0.9f) * fog; // RGB fog color (match with clear color)
    
    
    // 2020.09.18
    // リムライティング
    // Rim Lighting

    //float rim = 1.0 + dot(eyev, normal.xyz);
    //rim = pow(rim, 2) * 0.6;
    //outDiffuse.rgb += rim;

}
