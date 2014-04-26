#pragma once
#include "DXUT.h"
#include <string>
#include <map>

class C3DTexture
{
public:
	C3DTexture(){}
	~C3DTexture(){}

	static C3DTexture* m_pC3DTexture ;

	//	管理マップ
	static std::map< std::string, C3DTexture* > m_Textures ;

	//	生成
	static C3DTexture* Create( std::string &m_Path ) ;

	//	テクスチャの解放( 名前を指定しないと全部解放 )
	static void Destroy( std::string m_Name = "all" ) ;

	std::string			m_Name ;		//	テクスチャの名前
	LPDIRECT3DTEXTURE9	m_DirecxTex ;	//	DirectX テクスチャ
};

