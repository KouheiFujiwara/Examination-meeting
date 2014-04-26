#include "DXUT.h"
#include "PointSprite.h"
#include "GlobalD3DDevice.h"
#include "GraphicsManager.h"
#include "DXconvAnsiToWide.h"
#include "Camera.h"

PointSprite* PointSprite::Create( const std::string _fileName )
{
	PointSprite* p = new PointSprite() ;
	p->Load( _fileName ) ;

	CGraphicsManager::m_RenderList.push_back( p ) ;
	return p ;
}

void PointSprite::Load( const std::string _fileName )
{
	HRESULT hr ;

	hr = GlobalD3DDevice::m_pd3dDevice->CreateVertexBuffer( sizeof(POINTSPRITE),
		D3DUSAGE_NPATCHES | D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC,
		D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT, &m_VB, NULL ) ;

	if( !FAILED( hr ) ) 
	{
		POINTSPRITE *pV ;
		hr = m_VB->Lock( sizeof( POINTSPRITE ), sizeof(POINTSPRITE),(void**)&pV,D3DLOCK_DISCARD ) ;
		if( !FAILED( hr ) )
		{
			pV->vPos = D3DXVECTOR3(2.0f,2.0f,1.0f) ;
			pV->fSize = 1.0f ;
			pV->dwColor = 0xffffffff ;
		}
		m_VB->Unlock() ;
	}

	WCHAR wcBuff[ 255 ] = { 0 } ;
	DXconvAnsiToWide::Change( wcBuff, _fileName.c_str(), 255 ) ;

	D3DXCreateTextureFromFile( GlobalD3DDevice::m_pd3dDevice, wcBuff, &m_Texture ) ;

}

void PointSprite::Render( const Camera* _camera )
{
	HRESULT hr ;

	//-------------------------------------------------------------------------
	//
	// ワールドマトリクス設定
	//
	D3DXMATRIX SclMtx, RotMtx, PosMtx, WldMtx ;

	D3DXMatrixScaling( &SclMtx, m_Scl.x, m_Scl.y, m_Scl.z ) ;

	//	XYZ指定
	D3DXMatrixRotationYawPitchRoll( &RotMtx, m_Rot.y, m_Rot.x, m_Rot.z ) ;

	D3DXMatrixTranslation( &PosMtx, m_Pos.x, m_Pos.y, m_Pos.z ) ;

	WldMtx = ( SclMtx * RotMtx * PosMtx ) * _camera->m_view * _camera->m_proj ;

	// ワールドマトリクス設定
	GlobalD3DDevice::m_pd3dDevice->SetTransform( D3DTS_WORLD, &WldMtx ) ;

	//パーティクルの使用を有効にする
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE ) ;	
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_POINTSCALEENABLE, TRUE ) ;	

	//ポイントの最小サイズ
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_POINTSIZE_MIN, 0 ) ;

	//	Zバッファ
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE ) ;

	//ライティングOFF
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	GlobalD3DDevice::m_pd3dDevice->LightEnable( 0, FALSE ) ;

	// 加算合成で表示
	GlobalD3DDevice::m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE ) ;
	GlobalD3DDevice::m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 ) ;
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ) ;
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD ) ;
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ) ;
	GlobalD3DDevice::m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE ) ;
	GlobalD3DDevice::m_pd3dDevice->SetTexture( 0, m_Texture ) ;
	GlobalD3DDevice::m_pd3dDevice->SetStreamSource( 0, m_VB, 0, sizeof(POINTSPRITE) ) ;
	GlobalD3DDevice::m_pd3dDevice->SetFVF( D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE ) ;

	// Render the scene
    if( SUCCEEDED( GlobalD3DDevice::m_pd3dDevice->BeginScene() ) )
    {
		GlobalD3DDevice::m_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, 0) ;

        V( GlobalD3DDevice::m_pd3dDevice->EndScene() );
    }
}