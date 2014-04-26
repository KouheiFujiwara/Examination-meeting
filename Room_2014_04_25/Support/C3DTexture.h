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

	//	�Ǘ��}�b�v
	static std::map< std::string, C3DTexture* > m_Textures ;

	//	����
	static C3DTexture* Create( std::string &m_Path ) ;

	//	�e�N�X�`���̉��( ���O���w�肵�Ȃ��ƑS����� )
	static void Destroy( std::string m_Name = "all" ) ;

	std::string			m_Name ;		//	�e�N�X�`���̖��O
	LPDIRECT3DTEXTURE9	m_DirecxTex ;	//	DirectX �e�N�X�`��
};

