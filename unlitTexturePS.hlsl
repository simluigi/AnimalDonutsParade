/*============================================
DirectX11 Shader Lesson : unlitTexturePS.hlsl
Unlit Texture Pixel Shader
Author: Sim Luigi
Last Updated: 2020.09.04
*============================================*/

// Set as Pixel Shader
// Right click - Properties: Shader Type: /ps�@�i�s�N�Z���V�F�[�_�[�j
// Remove $(OutDir) from Output File - Object File Name (only %(Filename).cso should remain)

#include "common.hlsl"

// global variables
// �O���[�o���ϐ�
Texture2D g_Texture : register(t0); // texture 0 (can use multiple for multiple textures)
SamplerState g_SamplerState : register(s0); // state 0

// calculates PER PIXEL; avoid using conditional statements or system processing speed plummets
// 1�s�N�Z�����Ə����Fif���Ȃǂ��g���Ə������x�����Ȃ�ቺ�I�g��Ȃ���������

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{    
    // texture mapping
    //�@�e�N�X�`���[�}�b�s���O
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse *= In.Diffuse;
    
}
