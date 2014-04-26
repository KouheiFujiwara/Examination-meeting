#include "DXUT.h"
#include "C3D.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "C3DTexture.h"
#include "Mesh.h"
#include "../Support/GlobalD3DDevice.h"

#include <sstream>

D3DXVECTOR4 C3D::m_AllDirLight ;
bool C3D::m_LightFlg = true ;

C3D::~C3D()
{
	CGraphicsManager::Erase( this ) ;
}

C3D* C3D::Create( const std::string& _path )
{
	C3D* p =  new C3D() ;
	p->Load( _path ) ;

	//	レンダリングリストへの登録
	CGraphicsManager::m_RenderList.push_back( p ) ;
	return p ;
}

void C3D::Load( const std::string &_path ) 
{
	//-------------------------------------------------------------------------
	// X ファイル とテクスチャのロード
	m_Mesh = Mesh::m_pMesh->Create( _path ) ;

	C3DTexture *Tex = NULL ;

	// マテリアル情報の取得
	D3DXMATERIAL *pMaterials = ( D3DXMATERIAL* )( m_Mesh->m_MaterialBuff->GetBufferPointer() ) ;

	//	独自テクスチャクラスとして生成
	std::stringstream ss ;
	WCHAR wcBuff[ 255 ] = { 0 } ;

	for( int i =0; i < (int)m_Mesh->m_MaterialNum ; i++ ) {
		memset( wcBuff, 0, sizeof(WCHAR) * 255 ) ;
		ss.str("") ;
		if( NULL == pMaterials[ i ].pTextureFilename ) {
			Tex = NULL ;
			m_Texs.push_back( NULL ) ;
			continue ;
		}
		ss << "mesh/" << pMaterials[ i ].pTextureFilename ;

		//	独自テクスチャクラスとして生成
		std::string str = ss.str().c_str() ;
		Tex = C3DTexture::m_pC3DTexture->Create( str ) ;

		m_Texs.push_back(Tex) ;
	}
}

D3DXMATRIX C3D::BillBord( D3DXVECTOR3 _Look, D3DXVECTOR3 _Up )
{
	D3DXMATRIX Inv;
    D3DXMatrixIdentity(&Inv);
	//ローカルで0,0,0の位置から見ているビュー行列を作成
    D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0,0,0), &_Look, &_Up);
	//逆行列作成
    D3DXMatrixInverse(&Inv, NULL, &Inv);

    return Inv;
}
/*
void C3D::Render( const Camera *_camear )
{
	HRESULT hr ;

	//-------------------------------------------------------------------------
	//
	// ワールドマトリクス設定
	//
	D3DXMATRIX SclMtx, RotMtx, PosMtx, WldMtx ;
	D3DXMatrixScaling( &SclMtx, m_Scl.x, m_Scl.y, m_Scl.z ) ;

	if( m_BillFlg ){
		RotMtx = m_RotMtx ;
	}else{
		//	(Y,X,Zの順番)
		D3DXMatrixRotationYawPitchRoll( &RotMtx, m_Rot.y, m_Rot.x, m_Rot.z ) ;
	}

	D3DXMatrixTranslation( &PosMtx, m_Pos.x, m_Pos.y, m_Pos.z ) ;

	WldMtx = ( SclMtx * RotMtx * PosMtx ) * _camear->m_view * _camear->m_proj ;

	//	シェーダ設定
	CGraphicsManager::m_sdr->SetTechnique( CGraphicsManager::m_sdr_technique ) ;

	//	シェーダにワールド行列をわたす
	CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_wvmp, &WldMtx ) ;

	//	ライト計算用回転行列をわたす
	CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_rot, &RotMtx ) ;
	
	//	ライト設定( 平行光源 )
	CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_light, &m_DirLight ) ;

	//	シェーダにカラーをわたす
	CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &m_Col ) ;

	//-------------------------------------------------------------------------
	//
    // 描画処理
	//
	// 3D モデルのパーツ分ループして描画
	for( int i = 0; i < m_Mesh->m_MaterialNum; i++ ) {
		//	各パーツに対応するテクスチャを設定
		//	シェーダにテクスチャをわたす
		if( NULL != m_Texs[ i ] ) {
			CGraphicsManager::m_sdr->SetTexture( CGraphicsManager::m_sdr_tex, m_Texs[ i ]->m_DirecxTex ) ;
		}else{
			CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &D3DXVECTOR4( 0,0,0,0 ) ) ;
		}

		//	シェーダの使用開始
		CGraphicsManager::m_sdr->Begin( NULL, 0 ) ;

		//	シェーダのパス設定
		if( !m_IsAddBlend ){
			CGraphicsManager::m_sdr->BeginPass( 0 ) ;
		}else{
			CGraphicsManager::m_sdr->BeginPass( 1 ) ;
		}

		if( SUCCEEDED( GlobalD3DDevice::m_pd3dDevice->BeginScene() ) )
		{
			//	パーツの描画
			m_Mesh->m_DirectxMesh->DrawSubset( i ) ;
			V( GlobalD3DDevice::m_pd3dDevice->EndScene() ) ;
		}

		//	パス終了
		CGraphicsManager::m_sdr->EndPass() ;

		//	シェーダ終了
		CGraphicsManager::m_sdr->End() ;
	}
}
*/

void C3D::Render( const Camera *_camear )
{
	HRESULT hr ;

	//-------------------------------------------------------------------------
	//
	// ワールドマトリクス設定
	//
	D3DXMATRIX SclMtx, RotMtx, PosMtx, WldMtx ;

	D3DXMatrixScaling( &SclMtx, m_Scl.x, m_Scl.y, m_Scl.z ) ;

	if( m_BillFlg )
	{
		//	ビルボード
		RotMtx = m_RotMtx ;
	}
	else
	{
		//	XYZ指定
		D3DXMatrixRotationYawPitchRoll( &RotMtx, m_Rot.y, m_Rot.x, m_Rot.z ) ;
	}

	D3DXMatrixTranslation( &PosMtx, m_Pos.x, m_Pos.y, m_Pos.z ) ;

	WldMtx = ( SclMtx * RotMtx * PosMtx ) * _camear->m_view * _camear->m_proj ;

	//	シェーダ設定
	CGraphicsManager::m_sdr->SetTechnique( CGraphicsManager::m_sdr_technique ) ;

	//	シェーダにワールド行列をわたす
	CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_wvmp, &WldMtx ) ;

	//	ライト計算用回転行列をわたす
	if( m_LightFlg )
		CGraphicsManager::m_sdr->SetMatrix( CGraphicsManager::m_sdr_rot, &RotMtx ) ;

	if( m_All_SubstanceFlg )
	{
		//	ライト設定( 平行光源 )
		CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_light, &m_SubstanceDirLight ) ;
	}
	else
	{
		//	ライト設定( 平行光源 )
		CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_light, &m_AllDirLight ) ;
	}

	//	シェーダにカラーをわたす
	CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &m_Col ) ;

	//-------------------------------------------------------------------------
	//
    // 描画処理
	//
	// 3D モデルのパーツ分ループして描画
	for( int i = 0; i < (int)m_Mesh->m_MaterialNum; i++ ) {
		//	各パーツに対応するテクスチャを設定
		//	シェーダにテクスチャをわたす
		if( NULL != m_Texs[ i ] ) {
			CGraphicsManager::m_sdr->SetTexture( CGraphicsManager::m_sdr_tex, m_Texs[ i ]->m_DirecxTex ) ;
		}else{
			CGraphicsManager::m_sdr->SetVector( CGraphicsManager::m_sdr_color, &D3DXVECTOR4( 0,0,0,0 ) ) ;
		}

		//	シェーダの使用開始
		CGraphicsManager::m_sdr->Begin( NULL, 0 ) ;

		//	シェーダのパス設定
		if( !m_IsAddBlend ){
			CGraphicsManager::m_sdr->BeginPass( 0 ) ;
		}else{
			CGraphicsManager::m_sdr->BeginPass( 1 ) ;
		}

		if( SUCCEEDED( GlobalD3DDevice::m_pd3dDevice->BeginScene() ) )
		{
			//	パーツの描画
			m_Mesh->m_DirectxMesh->DrawSubset( i ) ;
			V( GlobalD3DDevice::m_pd3dDevice->EndScene() ) ;
		}

		//	パス終了
		CGraphicsManager::m_sdr->EndPass() ;

		//	シェーダ終了
		CGraphicsManager::m_sdr->End() ;
	}
}