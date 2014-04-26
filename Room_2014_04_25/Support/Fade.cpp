#include "DXUT.h"
#include "Fade.h"
#include "C2D.h"

Fade* Fade::SharedInstance ;

Fade::Fade()
{
	//	モードを何もしないに設定
	m_Mode = MODE_NONE ;

	m_OutAndInImage = new C2D("testFade.png") ;

	//	最初のアルファ値を0に設定
	m_OutAndInImage->m_alpha = 0 ;

	//	イメージを画面を覆うポジションへ
	m_OutAndInImage->m_pos = D3DXVECTOR3( 400,300,0 ) ;

	m_FadeOutLimitFlag	= false ;
	m_NewDeleteFlag		= false ;
}

Fade::~Fade()
{
	//	画像を解放
	SAFE_DELETE( m_OutAndInImage ) ;
}

void Fade::FadeIn() 
{	
	m_FadeOutLimitFlag = false ;
	if( m_OutAndInImage->m_alpha <= 0 && m_NewDeleteFlag )
	{
		//	アルファ値が0に達したらリミットをかける
		m_OutAndInImage->m_alpha = 0 ;
		//	フェードインへモード変更
		m_Mode = MODE_NONE ;
	}
	else
	{
		//	設定値ずつアルファに足していく
		m_OutAndInImage->m_alpha -= BLENDER_NUM ;
	}
}

void Fade::FadeOut()
{
	if( m_OutAndInImage->m_alpha >= ALPHA_MAX )
	{
		//	アルファ値が255に達したらリミットをかける
		m_OutAndInImage->m_alpha = ALPHA_MAX ;

		//	フェードアウトリミットフラグをtrueに
		m_FadeOutLimitFlag = true ;

		//	フェードNONEへモード変更
		m_Mode = MODE_IN ;
	}
	else
	{
		//	設定値ずつアルファを引いていく
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
