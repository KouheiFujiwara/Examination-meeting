//	グラフィックシェーダーをもったマネージャー

#pragma once
#include "DXUT.h"
#include <list>
#include <memory>

class Camera ;
class BaseObj ;

class CGraphicsManager
{
private :
	static CGraphicsManager *SharedInstance ;
	
	CGraphicsManager(){}
	~CGraphicsManager(){}
	CGraphicsManager( const CGraphicsManager &obj ) ;
	CGraphicsManager& operator = ( const CGraphicsManager &obj ) ;

public :
	//---------------------------------------------------------------------
	//
	// シェーダ関連
	//	( 追加ソース2013.07.12 )

	static LPD3DXEFFECT m_sdr ;					// シェーダ本体
	static D3DXHANDLE	m_sdr_technique ;		// テクニック
	static D3DXHANDLE	m_sdr_tex ;				// テクスチャ
	static D3DXHANDLE	m_sdr_color ;			// カラー
	static D3DXHANDLE	m_sdr_wvmp ;			// ワールド x ビュー x プロジェクション行列
	static D3DXHANDLE	m_sdr_light ;			//	平行光源の向き
	static D3DXHANDLE	m_sdr_rot ;				// 回転行列

	static std::list< BaseObj* > m_RenderList ;

	static void Erase( BaseObj* _obj ) ;

	static CGraphicsManager *Initialize() ;
	static void Destroy() ;

	static void SysRender( const Camera* _camera ) ;
} ;

