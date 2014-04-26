//	�J���[
float4 Color ;

// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP ;

// ��]�s��
float4x4 RM ;

// ���s�����̌���
float4 dir_light ;

//	���̋���
flaot4 l_ambient = { 0.3f, 0.3f, 0.3f, 0.0f } ;
float4 l_diffuse = { 0.7f, 0.7f, 0.7f, 0.0f } ;

//	���˂̌�
float4 k_ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
float4 k_diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture SrcTex ;

sampler SrcSamp = sampler_state
{
    Texture = <SrcTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};

// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float4 Diff			: COLOR0;
	float2 Tex			: TEXCOORD0;
};

// -------------------------------------------------------------
// ���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass1 (
      float4 Pos    : POSITION,          // ���f���̒��_
	  float4 Normal	: NORMAL,
      float4 Tex    : TEXCOORD0	         // �e�N�X�`�����W
){

    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
    
    // �ʒu���Wd
    Out.Pos = mul( Pos, WVP ) ;
    Out.Tex = Tex ;

	/*
	//	���F�_
	float3 L = -dir_light ;
	float3 N = normalize( mul(Normal,(float3x3)m
	*/

	//	�����̋���
	float amb = -dir_light ;
	//�@���C�g�x�N�g��
	float3 L =-dir_light ;

	float4 nml = mul( Normal, RM ) ;
	float d = -dot( dir_light, nml ) ;

	Out.Color = COLOR * max( amd, dot(Normal,0 )) ;

	Out.Diff = float4( d, d, d, 1 ) ;
   
    return Out;
}

// -------------------------------------------------------------
// �s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
float4 PS_pass1( VS_OUTPUT In ) : COLOR
{   
    float4 Color;

	Color = tex2D( SrcSamp, In.Tex ) ;
	Color *= In.Diff ;
		
    return Color;
}

// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
	//	�ʏ퍇��
    pass Normal
    {
		AlphaBlendEnanle = true ;
		SrcBlend = SRCALPHA ;
		DestBlend = INVSRCALPHA ;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
    }

	//	���Z����
	pass Add
	{
		AlphaBlendEnanle = true ;
		SrcBlend = ONE ;
		DestBlend = ONE ;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
	}

}
