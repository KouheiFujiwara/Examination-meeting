//	�t�F�[�h�C���E�t�F�[�h�A�E�g�p�N���X

#pragma once
#include "DXUT.h"

//	�t�F�[�h�C���[�W�̃A���t�@�ɉ��Z���鐔��
#define BLENDER_NUM (5) 
//	�A���t�@��MAX�l
#define ALPHA_MAX (255)

class C2D ;

//	�V���O���g�[���p�^�[��

class Fade
{
private:
	Fade() ;
	Fade( const Fade& obj ) ;
	Fade& operator = ( const Fade& obj ) ;

	~Fade() ;

	static Fade* SharedInstance ;
	
	void FadeIn() ;
	void FadeOut() ;

	//	�t�F�[�h���
	enum
	{
		MODE_NONE = -1,	//	�������Ȃ�
		MODE_IN,		//	�t�F�[�h�C��
		MODE_OUT		//	�t�F�[�h�A�E�g
	};

	//	�t�F�[�h���[�h
	int m_Mode ;

	//	�t�F�[�h�C���[�W( �ꉞ�t�F�[�h�A�E�g��C�����L�C���[�W ) 
	C2D* m_OutAndInImage ;

	//	�t�F�[�h���Ă��邩�ǂ���	
	//	true	:	���݃t�F�[�h�A�E�g�E�C�����쒆
	//	false	:	�t�F�[�h��~��
	bool m_DoFlag ;

	//	�N���XNew�̍Œ��Ƀt�F�[�h�C�������Ȃ����߂̃t���O
	//	true	:	���ݐ�����J����
	//	false	:	������J������
	bool m_NewDeleteFlag ;

	//	�摜�̃A���t�@�����~�b�g�l�ɒB���Ă��邩�ǂ���
	//	true	:	�A���t�@���B���Ă���
	//	false	:	�A���t�@�ϓ���
	bool m_FadeOutLimitFlag ;

public:
	//	�Q�b�g�C���X�^���X
	inline static Fade* GetInstance()
	{
		if( SharedInstance == NULL )
			SharedInstance = new Fade() ;
		return SharedInstance ;
	}

	//	�f���[�g�C���X�^���X
	inline static void DeleteInstance()
	{
		SAFE_DELETE( SharedInstance ) ;
	}

	//	�t�F�[�h�𓮂����n�߂�֐�
	void Start() ;

	//	���W�b�N�֐�
	void DoFadeLogic() ;

	//	�`��֐�
	void DoFadeDraw() ;

	inline void GetNewDelete( bool const _NewDeleteFlag )
	{
		m_NewDeleteFlag = _NewDeleteFlag ;
	}

	//	�t�F�[�h�A�E�g�Ő^���Â��ǂ���
	inline bool AlphaComplate(){ return m_FadeOutLimitFlag; } ;
	
};