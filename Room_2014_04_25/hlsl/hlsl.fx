
// ワールド x ビュー x プロジェクション 行列
float4x4 WVP ;

// 回転行列
float4x4 RM ;

// 平行光源の向き
float4 dir_light ;

//　カラー
float4 Color ;

//　反射光
float4 l_a = { 0.3f, 0.3f, 0.3f, 1.0f } ;
float4 l_d = { 1.0f, 1.0f, 1.0f, 1.0f } ;

// 反射
float4 k_a = { 0.7f, 0.7f, 0.7f, 0.7f };
float4 k_d = { 0.7f, 0.7f, 0.7f, 0.7f };

// -------------------------------------------------------------
// テクスチャ
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
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float4 Diff			: COLOR0;
	float2 Tex			: TEXCOORD0;
};

// -------------------------------------------------------------
// 頂点シェーダプログラム
// -------------------------------------------------------------
VS_OUTPUT VS_pass1 (
      float4 Pos    : POSITION,          // モデルの頂点
	  float4 Normal	: NORMAL,
      float4 Tex    : TEXCOORD0	         // テクスチャ座標
){

    VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ
    
    // 位置座標d
    Out.Pos = mul( Pos, WVP ) ;
    Out.Tex = Tex ;
	float4 nml = mul( Normal, RM ) ;
	//float d = -dot( dir_light, nml ) ;
	
	float3 L =-dir_light ;
	float3 N = normalize(mul(Normal,(float3x3)RM)) ;
	
	// 環境光、拡散光
	Out.Diff = l_a * k_a + l_d * k_d * max( 0.5,dot(N,L)) ;
	Out.Diff.w = 1.0 ;
	Out.Diff *= Color ;


	//Out.Diff = float4(d,d,d,1) ;
	
    return Out;
}

// -------------------------------------------------------------
// ピクセルシェーダプログラム
// -------------------------------------------------------------
float4 PS_pass1( VS_OUTPUT In ) : COLOR
{   
    float4 Color;

	Color = tex2D( SrcSamp, In.Tex ) ;
	Color *= In.Diff ;
		
    return Color;
}

// -------------------------------------------------------------
// テクニック
// -------------------------------------------------------------
technique TShader
{
	// 通常合成
    pass Normal
    {
	AlphaBlendEnable = true ;
	SrcBlend = SRCALPHA ;
	DestBlend = INVSRCALPHA ;

        // シェーダ
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
	Sampler[0] = (SrcSamp);
    }

    pass Add
    {
	AlphaBlendEnable = true ;
	SrcBlend = ONE ;
	DestBlend = ONE ;

        // シェーダ
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
	Sampler[0] = (SrcSamp);
    }
}
