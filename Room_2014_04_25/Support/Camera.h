//	�J�����̏��

#pragma once
#include "DXUT.h"
#include <string>

class Camera
{
private:
	
public :
	Camera() ;
	~Camera(){} ;

	//	���W(�J����������ʒu)
	D3DXVECTOR3		m_vEyePt ;
	//	�����_(�J���������Ă���ʒu)
	D3DXVECTOR3		m_vLookatPt ;
	//	�J�����̌���(�i�s����)
	D3DXVECTOR3		m_vDir ;
	//	�A�b�p�[�x�N�g��
	D3DXVECTOR3		m_vUpVec ;

	//	�A�b�v�f�[�g�p�ϐ�( �r���[�s��(�����_�̍��W), �v���W�F�N�V�����s��	�@) 
	D3DXMATRIX		m_view ;
	D3DXMATRIX		m_proj ;

	void UpData() ;

	//	�����_�̎�������邮����Ȃ��猩��֐�
	//	�����F�J�����̍��W, �J�����̒����_, ��]��X�̊p�x, ��]��Y�̊p�x
	//	�߂�l�F�����_�̌���
	D3DXVECTOR3 SetMainCameraXY( const D3DXVECTOR3 _EyePos, const D3DXVECTOR3 _LookPos , const float _RotX, const float _RotY, const float _Distance ) ;
};

