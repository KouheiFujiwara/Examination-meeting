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
	//	ジンバルロック式
	
	D3DXMATRIX MtxRotX, MtxRotY, MtxRotZ, MtxRot ;

	//	X軸(縦移動)に角度をかけて操作する
	D3DXMatrixRotationX( &MtxRotX, _RotX ) ;
	//	Y軸(横移動)に角度をかけて操作する
	D3DXMatrixRotationY( &MtxRotY, _RotY ) ;
	
	//	相対的な回転行列にする
	D3DXMatrixMultiply( &MtxRot, &MtxRotX, &MtxRotY ) ;
	
	D3DXVECTOR3 local;
	//	ローカル変数にカメラの注視点と距離を算出
	local = ( m_vLookatPt - m_vEyePt ) * _Distance;
	//	カメラ座標と注視点の相対的なポジションを計算
	D3DXVec3TransformCoord( &local, &local, &MtxRot ) ;

	//	カメラが注視点を軸にしてその周りを回る
	m_vEyePt = local + m_vLookatPt;

	return -local ;
}
