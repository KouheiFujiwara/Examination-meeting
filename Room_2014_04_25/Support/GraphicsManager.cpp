#include "DXUT.h"
#include "GraphicsManager.h"
#include "Mesh.h"
#include "C3DTexture.h"
#include "BaseObj.h"
#include "Camera.h"
#include "GlobalD3DDevice.h"

CGraphicsManager *CGraphicsManager::SharedInstance ;
LPD3DXEFFECT CGraphicsManager::m_sdr		= NULL ;
D3DXHANDLE CGraphicsManager::m_sdr_technique ;
D3DXHANDLE CGraphicsManager::m_sdr_tex ;
D3DXHANDLE CGraphicsManager::m_sdr_color ;
D3DXHANDLE CGraphicsManager::m_sdr_wvmp ;
D3DXHANDLE CGraphicsManager::m_sdr_rot ;
D3DXHANDLE CGraphicsManager::m_sdr_light ;

std::list< BaseObj* > CGraphicsManager::m_RenderList ;

CGraphicsManager* CGraphicsManager::Initialize()
{
	//-------------------------------------------------------------------------
	// シェーダ ファイルのロード
	D3DXCreateEffectFromFile( GlobalD3DDevice::m_pd3dDevice , L"hlsl/hlsl.fx", NULL, NULL, D3DXSHADER_DEBUG , NULL, &m_sdr, NULL ) ;
	m_sdr_technique = m_sdr->GetTechniqueByName( "TShader" ) ;  
	m_sdr_tex		= m_sdr->GetParameterByName( NULL, "SrcTex" ) ;
	m_sdr_color		= m_sdr->GetParameterByName( NULL, "Color" ) ;
	m_sdr_wvmp		= m_sdr->GetParameterByName( NULL, "WVP" ) ;
	m_sdr_light		= m_sdr->GetParameterByName( NULL, "dir_light" ) ;
	m_sdr_rot		= m_sdr->GetParameterByName( NULL, "RM" ) ;

	Mesh::m_pMesh = new Mesh() ;
	C3DTexture::m_pC3DTexture = new C3DTexture() ;

	return SharedInstance ;
}

void CGraphicsManager::Destroy()
{
	SAFE_RELEASE( m_sdr ) ;
	//SAFE_DELETE( SharedInstance ) ;
	SAFE_DELETE( Mesh::m_pMesh ) ;

	Mesh::m_pMesh->Destroy() ;
	C3DTexture::m_pC3DTexture->Destroy() ;
}

void CGraphicsManager::SysRender( const Camera* _camera )
{
	std::list< BaseObj* >::iterator it = m_RenderList.begin() ;

	//	カメラとオブジェクトの距離を計算
	while( it != m_RenderList.end() ){
		
		//	距離計算continue
		(*it)->m_CameraDistance = D3DXVec3Length( &( (*it)->m_Pos - _camera->m_vEyePt ) ) ;

		//	遠いものから順に描画させるので半透明か加算のものは近くに強制する
		if( 1.0f > (*it)->m_Col.w || (*it)->m_IsAddBlend ) (*it)->m_CameraDistance -= 1000.0f ;

		it++ ;
	}

	//	レンダリングリストの中身をソート
	m_RenderList.sort( BaseObj::comp ) ;

	//	レンダリングリストの中身を描画
	it = m_RenderList.begin() ;
	while( it != m_RenderList.end() ){
		(*it)->Render( _camera ) ;
		it++ ;
	}
}

void CGraphicsManager::Erase( BaseObj* _obj )
{
	std::list< BaseObj* >::iterator it = m_RenderList.begin() ;
	while( it != m_RenderList.end() )
	{
		if( (*it) == _obj ){
			m_RenderList.erase( it ) ;
			return ;
		}
		it++ ;
	}
}