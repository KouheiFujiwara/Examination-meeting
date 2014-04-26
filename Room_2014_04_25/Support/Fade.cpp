#include "DXUT.h"
#include "Fade.h"
#include "C2D.h"

Fade* Fade::SharedInstance ;

Fade::Fade()
{
	//	���[�h���������Ȃ��ɐݒ�
	m_Mode = MODE_NONE ;

	m_OutAndInImage = new C2D("testFade.png") ;

	//	�ŏ��̃A���t�@�l��0�ɐݒ�
	m_OutAndInImage->m_alpha = 0 ;

	//	�C���[�W����ʂ𕢂��|�W�V������
	m_OutAndInImage->m_pos = D3DXVECTOR3( 400,300,0 ) ;

	m_FadeOutLimitFlag	= false ;
	m_NewDeleteFlag		= false ;
}

Fade::~Fade()
{
	//	�摜�����
	SAFE_DELETE( m_OutAndInImage ) ;
}

void Fade::FadeIn() 
{	
	m_FadeOutLimitFlag = false ;
	if( m_OutAndInImage->m_alpha <= 0 && m_NewDeleteFlag )
	{
		//	�A���t�@�l��0�ɒB�����烊�~�b�g��������
		m_OutAndInImage->m_alpha = 0 ;
		//	�t�F�[�h�C���փ��[�h�ύX
		m_Mode = MODE_NONE ;
	}
	else
	{
		//	�ݒ�l���A���t�@�ɑ����Ă���
		m_OutAndInImage->m_alpha -= BLENDER_NUM ;
	}
}

void Fade::FadeOut()
{
	if( m_OutAndInImage->m_alpha >= ALPHA_MAX )
	{
		//	�A���t�@�l��255�ɒB�����烊�~�b�g��������
		m_OutAndInImage->m_alpha = ALPHA_MAX ;

		//	�t�F�[�h�A�E�g���~�b�g�t���O��true��
		m_FadeOutLimitFlag = true ;

		//	�t�F�[�hNONE�փ��[�h�ύX
		m_Mode = MODE_IN ;
	}
	else
	{
		//	�ݒ�l���A���t�@�������Ă���
		m_OutAndInImage->m_alpha += BLENDER_NUM ;
	}
}

void Fade::DoFadeLogic()
{
	switch( m_Mode )
	{
	case MODE_NONE:
		m_DoFlag		= false ;
		m_NewDeleteFlag = false ;
		break ;
	case MODE_OUT:
		FadeOut() ;
		break ;
	case MODE_IN:
		FadeIn() ;
		break ;
	default :
		break ;
	}
}

void Fade::Start()
{
	if( !m_DoFlag )
	{
		m_Mode = MODE_OUT ;
		m_DoFlag = true ;
	}
}

void Fade::DoFadeDraw()
{
	m_OutAndInImage->Draw() ;
}
