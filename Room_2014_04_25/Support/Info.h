#pragma once
#include "DXUT.h"
#include <string>

class Info
{
private:
	std::string* m_pFileName ;
	IDirect3DDevice9* m_pd3dDevice ;	//	�摜�p�X�󂯎��p

	//	����(string)��WCHAR�^�ɕϊ�������֐�
	HRESULT static DXconvAnsiToWide( WCHAR* wstrDest, const CHAR* strSrc, int ct );

public:
	D3DXIMAGE_INFO m_image_info ;	//	�摜���󂯓n���p
	LPDIRECT3DTEXTURE9 m_texture ;	//	�e�N�X�`�����󂯓n���p

	Info( const std::string& FileName );
	~Info(){};

};

