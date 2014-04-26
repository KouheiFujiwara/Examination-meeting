#pragma once
#include "DXUT.h"
#include <string>
#include <map>
#include "Info.h"

class Texture
{
public:
	D3DXIMAGE_INFO m_image_info ;		//	�摜���󂯎��p
	Texture() {}
	~Texture(){ delete m_pObj ; }

	//	�e�N�X�`���̍쐬�p�֐�
	LPDIRECT3DTEXTURE9 MakeTexture( const std::string& FileName );
	//	�e�N�X�`���̃��[�h�֐�
	LPDIRECT3DTEXTURE9 Load( const std::string FileName ) ;
	//	�e�N�X�`���𑽏d���[�h���Ȃ�����map�ŊǗ�
	static std::map<std::string, LPDIRECT3DTEXTURE9> StringTexture ;
	Info* m_pObj ;
};

