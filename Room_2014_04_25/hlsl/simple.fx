//	カラー
float4 Color ;

// ワールド x ビュー x プロジェクション 行列
float4x4 WVP ;

// 回転行列
float4x4 RM ;

// 平行光源の向き
float4 dir_light ;

//	光の強さ
flaot4 l_ambient = { 0.3f, 0.3f, 0.3f, 0.0f } ;
float4 l_diffuse = { 0.7f, 0.7f, 0.7f, 0.0f } ;

//	反射の光
float4 k_ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
float4 k_diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };

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

	/*
	//	着色点
	float3 L = -dir_light ;
	float3 N = normalize( mul(Normal,(float3x3)m
	*/

	//	環境光の強さ
	float amb = -dir_light ;
	//　ライトベクトル
	float3 L =-dir_light ;

	float4 nml = mul( Normal, RM ) ;
	float d = -dot( dir_light, nml ) ;

	Out.Color = COLOR * max( amd, dot(Normal,0 )) ;

	Out.Diff = float4( d, d, d, 1 ) ;
   
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
	//	通常合成
    pass Normal
    {
		AlphaBlendEnanle = true ;
		SrcBlend = SRCALPHA ;
		DestBlend = INVSRCALPHA ;

        // シェーダ
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
    }

	//	加算合成
	pass Add
	{
		AlphaBlendEnanle = true ;
		SrcBlend = ONE ;
		DestBlend = ONE ;

        // シェーダ
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS_pass1();
		Sampler[0] = (SrcSamp);
	}

}
