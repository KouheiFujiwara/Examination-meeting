
// ���[���h x �r���[ x �v���W�F�N�V���� �s��
float4x4 WVP ;

// ��]�s��
float4x4 RM ;

// ���s�����̌���
float4 dir_light ;

//�@�J���[
float4 Color ;

//�@���ˌ�
float4 l_a = { 0.3f, 0.3f, 0.3f, 1.0f } ;
float4 l_d = { 1.0f, 1.0f, 1.0f, 1.0f } ;

// ����
float4 k_a = { 0.7f, 0.7f, 0.7f, 0.7f };
float4 k_d = { 0.7f, 0.7f, 0.7f, 0.7f };

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
	float4 nml = mul( Normal, RM ) ;
	//float d = -dot( dir_light, nml ) ;
	
	float3 L =-dir_light ;
	float3 N = normalize(mul(Normal,(float3x3)RM)) ;
	
	// �����A�g�U��
	Out.Diff = l_a * k_a + l_d * k_d * max( 0.5,dot(N,L)) ;
	Out.Diff.w = 1.0 ;
	Out.Diff *= Color ;


	//Out.Diff = float4(d,d,d,1) ;
	
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
	// �ʏ퍇��
    pass Normal
    {
	AlphaBlendEnable = true ;
	SrcBlend = SRCALPHA ;
	DestBlend = INVSRCALPHA ;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
	Sampler[0] = (SrcSamp);
    }

    pass Add
    {
	AlphaBlendEnable = true ;
	SrcBlend = ONE ;
	DestBlend = ONE ;

        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
	Sampler[0] = (SrcSamp);
    }
}
