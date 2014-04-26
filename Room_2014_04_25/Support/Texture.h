#pragma once
#include "DXUT.h"
#include <string>
#include <map>
#include "Info.h"

class Texture
{
public:
	D3DXIMAGE_INFO m_image_info ;		//	画像情報受け取り用
	Texture() {}
	~Texture(){ delete m_pObj ; }

	//	テクスチャの作成用関数
	LPDIRECT3DTEXTURE9 MakeTexture( const std::string& FileName );
	//	テクスチャのロード関数
	LPDIRECT3DTEXTURE9 Load( const std::string FileName ) ;
	//	テクスチャを多重ロードしないためmapで管理
	static std::map<std::string, LPDIRECT3DTEXTURE9> StringTexture ;
	Info* m_pObj ;
};

