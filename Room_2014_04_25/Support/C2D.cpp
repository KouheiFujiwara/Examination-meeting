#include "DXUT.h"
#include "C2D.h"
#include "Texture.h"
#include "GlobalD3DDevice.h"

using namespace std;

C2D::C2D( const string& FileName,int num ) 
{
	//	座標
	m_pos = D3DXVECTOR3( 0,0,0 ) ;

	m_sclFloat = 1.0f ;
	m_pd3dDevice = GlobalD3DDevice::m_pd3dDevice ;

	Texture* pObj ;
	pObj = new Texture() ;
	m_texture = pObj->Load( FileName ) ;

	// テクスチャからサーフェイスを取得
	IDirect3DSurface9 *pSurface;
	m_texture->GetSurfaceLevel( 0, &pSurface );

	// サーフェイス情報から画像サイズを取得
	D3DSURFACE_DESC SurfaceInfo;
	pSurface->GetDesc( &SurfaceInfo );

	// 画像のどの範囲を描画するかを指定( 画像全体を指定 )
	m_rect.left = 0 ;
	m_rect.top = 0 ;
	m_rect.right = SurfaceInfo.Width / num ;
	m_rect.bottom = SurfaceInfo.Height ;

	// サーフェイスのサイズ( 2 の累乗サイズ )
	m_suf_size = D3DXVECTOR3( (float)SurfaceInfo.Width / num , (float)SurfaceInfo.Height, 0.0f ) ;

	// 画像本来のサイズ
	m_img_size = D3DXVECTOR3( (float)pObj->m_image_info.Width / num , (float)pObj->m_image_info.Height, 0.0f ) ;

	// 2D の中心
	m_center = D3DXVECTOR3( ( m_suf_size.x * 0.5f ), ( m_suf_size.y * 0.5f ), 0.0f ) ;
	//m_center = D3DXVECTOR3(  m_suf_size.x * 0.5f, m_suf_size.y, 0.0f ) ;
	// 2 の累乗サイズから 本来の画像サイズにするのに必要な倍率
	m_scale_ofs = D3DXVECTOR3( ( m_img_size.x / m_suf_size.x), ( m_img_size.y / m_suf_size.y), 1.0f ) ;

	// スケール
	m_scl = D3DXVECTOR3( 1 * m_sclFloat, 1 * m_sclFloat, 1 * m_sclFloat ) ;

	// 回転角度( デグリー )
	m_rot = 0.0f ;

	// 透明度
	m_alpha = 255.0f ;

	// 加算半透明フラグ
	m_is_add_alpha = false ;

	// 拡縮フラグ
	m_scl_flg = true ;

	// 使い終わったのでサーフェイス情報は開放
	SAFE_RELEASE( pSurface ) ;

	// スプライトの生成
	D3DXCreateSprite( m_pd3dDevice, &m_sprite ) ;
	delete pObj ;
}

C2D::~C2D()
{
	//	スプライトの解放
	SAFE_RELEASE( m_sprite ) ;
	//	テクスチャの解放
	SAFE_RELEASE( m_texture ) ;
}

void C2D::Draw( bool AnimeFlg , int num )
{

	m_scl = D3DXVECTOR3( 1 * m_sclFloat, 1 * m_sclFloat, 1 * m_sclFloat ) ;

	//	一回中継させる
	RECT m_masu;

	//	numをいじってアニメーションさせる
	if( AnimeFlg ) {
		m_masu.top = m_rect.top ;
		m_masu.bottom = m_rect.bottom ;
		m_masu.left = m_rect.right * num ;
		m_masu.right = m_rect.right * ( num + 1 ) ;
	}

	//---------------------------------------------------------------------------------
	//
	// ワールド行列に関する作業
	//
	D3DXMATRIX wm, tm, sm, rm ;

	// トランスレーション( 平行移動 ) 行列の作成
	D3DXMatrixTranslation( &tm, m_pos.x, m_pos.y, m_pos.z ) ;

	// スケール( 拡縮 ) 行列の作成
	D3DXMatrixScaling( &sm, ( m_scl.x * m_scale_ofs.x ), ( m_scl.y * m_scale_ofs.y ), 1.0f ) ;

	// ローテーション( 回転 ) 行列の作成 
	// ※ 今回は 2Dなので Z回転のみ
	D3DXMatrixRotationZ( &rm, D3DXToRadian( m_rot ) ) ;

	//【 !重要! 】ワールド行列の算出 
	// DirectX では ワールド行列の算出は
	// スケール * ローテーション * トランスレーション の順で行う
	wm = sm * rm * tm ;

	// スプライトにワールド行列を設定
	m_sprite->SetTransform( &wm ) ;

	//----------------------------------------------------------------------------------
	//
	// 加算ブレンドの設定
	//
	if( m_is_add_alpha ){
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE ) ;
		m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 ) ;
		m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ;
		m_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD ) ;
		m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
		m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE ) ;
	}
	//----------------------------------------------------------------------------------
	//
	// 最終的な描画
	//

	// デバイスの描画準備
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
		// スプライトの描画準備
		m_sprite->Begin( D3DXSPRITE_ALPHABLEND ) ;
		if( AnimeFlg ){
			// スプライトの描画命令
			m_sprite->Draw(	m_texture,	// 描画に使用するテクスチャ
							&m_masu,		// 画像の描画範囲
							&m_center,	// サーフェイスの中心
							&D3DXVECTOR3(0,0,0),	// 描画座標( 行列で制御するので 0,0,0 でＯＫ )
							D3DCOLOR_ARGB( (int)( m_alpha ), 255, 255, 255 )	// 色
						)  ;
		}else{
			m_sprite->Draw(	m_texture,	// 描画に使用するテクスチャ
							&m_rect,		// 画像の描画範囲
							&m_center,	// サーフェイスの中心
							&D3DXVECTOR3(0,0,0),	// 描画座標( 行列で制御するので 0,0,0 でＯＫ )
							D3DCOLOR_ARGB( (int)( m_alpha ), 255, 255, 255 )	// 色
						)  ;
		}

		// 加算切り替え
		if( m_is_add_alpha ){
			m_sprite->Flush() ;
		}else{
			m_sprite->End() ;
		}

		// 描画終了
        ( m_pd3dDevice->EndScene() );
	}
}