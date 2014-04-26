#pragma once
#include "DXUT.h"
#include <string>
#include <map>

class Mesh
{
public:
	Mesh(){} ;
	~Mesh(){} ;

	static Mesh *m_pMesh ;

	//	管理マップ
	static std::map< std::string, Mesh* > m_Mesh ;

	//	生成
	static Mesh *Create( const std::string &m_Path ) ;

	//	テクスチャの解放( 名前を指定しなと全部解放 )
	static void Destroy( std::string m_Name = "all" ) ;

	std::string		m_Name ;			// テクスチャの名前
	DWORD			m_MaterialNum ;		// マテリアルの数
	LPD3DXMESH		m_DirectxMesh ;		// DirectX メッシュ
	LPD3DXBUFFER	m_MaterialBuff ;	// マテリアルバッファ
};

