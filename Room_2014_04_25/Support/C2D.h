#pragma once
#include "DXUT.h"
#include <string>
#include <windows.h>
#include <list>

class C2D 
{
private :
	std::string m_pFileName ;			// �摜�̃p�X
	RECT m_rect ;						// �摜�̂ǂ͈̔͂�`�悷�邩
	D3DXIMAGE_INFO m_image_info ;		// �摜���( ���⍂���Ȃ� )�̎擾�p
	LPDIRECT3DTEXTURE9 m_texture ;		// �摜�f�[�^( �e�N�X�`�� )
	LPD3DXSPRITE m_sprite ;				// �X�v���C�g( DirectX ��2D�������N���X ) 
	D3DXVECTOR3 m_img_size ;			// �摜�̃T�C�Y
	D3DXVECTOR3 m_suf_size ;			// �T�[�t�F�C�X�̃T�C�Y
	D3DXVECTOR3 m_center ;				// �摜�̒��S
	D3DXVECTOR3 m_scale_ofs ;			// �I�t�Z�b�g�X�P�[��
	bool m_is_add_alpha ;				// ���Z�������̃t���O
	bool m_scl_flg ;					// �g�k�̃��Z�b�g����񂾂��s��
	IDirect3DDevice9* m_pd3dDevice ;	//	�摜�p�X���󂯎��p�X
	float m_Left ;						// �摜�̕`��͈�
	float m_Top ;						// �摜�̕`��͈�
	float m_Right ;						// �摜�̕`��͈�
	float m_Bottom ;					// �摜�̕`��͈�

public :
	D3DXVECTOR3 m_scl ;					// �X�P�[��
	D3DXVECTOR3 m_pos ;					// �`����W
	float m_sclFloat ;
	float m_rot ;						// ��]�p�x
	float m_alpha ;						// �����x
	C2D( const std::string& FileName,int num = 1 ) ;
	~C2D() ;

	void Logic();
	//	���W�A�傫���A�A�j���[�V�������邩�ǂ����H(true�Ȃ炷��)�A�A�j���[�V�����ԍ�
	void Draw( bool AnimeFlg = false, int num = 0 );

	int m_num ;
} ;