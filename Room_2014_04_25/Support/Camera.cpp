#include "DXUT.h"
#include "Camera.h"

Camera::Camera() : 
	m_vLookatPt( 0,0,0 ),
	m_vUpVec(0,1,0 )
{
	m_vEyePt.x	= 0;
	m_vEyePt.y	= 0;
	m_vEyePt.z	= 0;
} ;

void Camera::UpData()
{
	D3DXMatrixLookAtLH( &m_view, &m_vEyePt, &m_vLookatPt, &m_vUpVec ) ;
	D3DXMatrixPerspectiveFovLH( &m_proj, D3DX_PI / 4.0f, 1.0f, 1.0f, 1000.0f ) ;
}

D3DXVECTOR3 Camera::SetMainCameraXY( D3DXVECTOR3 _EyePos, D3DXVECTOR3 _LookPos , float _RotX, float _RotY, float _Distance  )
{
	m_vEyePt		= _EyePos  ;
	m_vLookatPt		= _LookPos ;

	//-------------------------------------------------------------------------
	//	�W���o�����b�N��
	
	D3DXMATRIX MtxRotX, MtxRotY, MtxRotZ, MtxRot ;

	//	X��(�c�ړ�)�Ɋp�x�������đ��삷��
	D3DXMatrixRotationX( &MtxRotX, _RotX ) ;
	//	Y��(���ړ�)�Ɋp�x�������đ��삷��
	D3DXMatrixRotationY( &MtxRotY, _RotY ) ;
	
	//	���ΓI�ȉ�]�s��ɂ���
	D3DXMatrixMultiply( &MtxRot, &MtxRotX, &MtxRotY ) ;
	
	D3DXVECTOR3 local;
	//	���[�J���ϐ��ɃJ�����̒����_�Ƌ������Z�o
	local = ( m_vLookatPt - m_vEyePt ) * _Distance;
	//	�J�������W�ƒ����_�̑��ΓI�ȃ|�W�V�������v�Z
	D3DXVec3TransformCoord( &local, &local, &MtxRot ) ;

	//	�J�����������_�����ɂ��Ă��̎�������
	m_vEyePt = local + m_vLookatPt;

	return -local ;
}
