#pragma once
#include "DXUT.h"
#include <string>

class Info
{
private:
	std::string* m_pFileName ;
	IDirect3DDevice9* m_pd3dDevice ;	//	画像パス受け取り用

	//	文字(string)をWCHAR型に変換をする関数
	HRESULT static DXconvAnsiToWide( WCHAR* wstrDest, const CHAR* strSrc, int ct );

public:
	D3DXIMAGE_INFO m_image_info ;	//	画像情報受け渡し用
	LPDIRECT3DTEXTURE9 m_texture ;	//	テクスチャ情報受け渡し用

	Info( const std::string& FileName );
	~Info(){};

};

