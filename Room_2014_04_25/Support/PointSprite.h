#pragma once
#include "BaseObj.h"
#include <memory>
#include <string>

class Camera ;

typedef struct tag_POINTSPRITE 
{
	D3DXVECTOR3 vPos ;
	float		fSize ;
	DWORD		dwColor ;
}	POINTSPRITE ;

class PointSprite : public BaseObj 
{
private :
	LPDIRECT3DTEXTURE9		m_Texture ;		//	�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_VB ;			//	���_�o�b�t�@
	D3DXMATRIX				g_WorldMtx ;	// �G�~�b�^�[�̃��[���h�}�g���N�X

public:
	PointSprite(){} ;
	~PointSprite(){};

	static PointSprite* Create( const std::string _fileName ) ;
	void Load( const std::string _fileName ) ;
	void Render( const Camera *_camera ) ;
};

