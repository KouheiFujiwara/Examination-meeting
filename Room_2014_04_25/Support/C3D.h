//	3Dモデル情報
#pragma once
#include "DXUT.h"
#include "BaseObj.h"
#include <string>
#include <vector>

class Cmaera ;
class Mesh ;
class C3DTexture ;


class C3D : public BaseObj
{
private:
	//	ライトの向きを決める
	static D3DXVECTOR4 m_AllDirLight ;

	//	別のライトの向き
	D3DXVECTOR4 m_SubstanceDirLight ;

public :
	D3DXVECTOR3 m_Vec ;

	C3D( D3DXVECTOR3 _pos = D3DXVECTOR3(0,0,0), float _rad = 1.0f ) :
	   m_Mesh( NULL ) 
	{
		m_Pos = _pos ; 
		m_Rad = _rad ;
		m_Dir = D3DXVECTOR3(0,0,0) ;
		m_AllDirLight = D3DXVECTOR4( 0.0f, -1.0f, 0.0f, 0.0f ) ;
		m_SubstanceDirLight = D3DXVECTOR4( 0.0f, -1.0f, 0.0f, 0.0f ) ;
		m_Vec = D3DXVECTOR3(0,0,0) ;
		m_All_SubstanceFlg = false ;
	}
	~C3D() ;
	
	Mesh*						m_Mesh ;
	std::vector< C3DTexture* >	m_Texs ;

	static C3D* Create( const std::string &_path ) ;

	void Load( const std::string &_path ) ;
	void Render( const Camera* _camera ) ;

	//	ライトを全体か単体で動かす
	//	(false)全部		(true)単体
	bool m_All_SubstanceFlg ;

	//	ライトのオンオフフラグ
	static bool m_LightFlg ;

	D3DXMATRIX BillBord( D3DXVECTOR3 _Look, D3DXVECTOR3 _Up ) ;

	void GetSubstanceDirLight( D3DXVECTOR3 _pos )
	{
		m_SubstanceDirLight.x = _pos.x ;
		m_SubstanceDirLight.y = _pos.y ;
		m_SubstanceDirLight.z = _pos.z ;
		m_SubstanceDirLight.w = 0 ;
	};
	void GetAllDirLight( D3DXVECTOR3 _pos ) 
	{
		m_AllDirLight.x = _pos.x ;
		m_AllDirLight.y = _pos.y ;
		m_AllDirLight.z = _pos.z ;
		m_AllDirLight.w = 0 ;
	}
} ;