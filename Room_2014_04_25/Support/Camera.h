//	カメラの情報

#pragma once
#include "DXUT.h"
#include <string>

class Camera
{
private:
	
public :
	Camera() ;
	~Camera(){} ;

	//	座標(カメラがある位置)
	D3DXVECTOR3		m_vEyePt ;
	//	注視点(カメラが見ている位置)
	D3DXVECTOR3		m_vLookatPt ;
	//	カメラの向き(進行方向)
	D3DXVECTOR3		m_vDir ;
	//	アッパーベクトル
	D3DXVECTOR3		m_vUpVec ;

	//	アップデート用変数( ビュー行列(注視点の座標), プロジェクション行列	　) 
	D3DXMATRIX		m_view ;
	D3DXMATRIX		m_proj ;

	void UpData() ;

	//	注視点の周りをぐるぐる回りながら見る関数
	//	引数：カメラの座標, カメラの注視点, 回転軸Xの角度, 回転軸Yの角度
	//	戻り値：注視点の向き
	D3DXVECTOR3 SetMainCameraXY( const D3DXVECTOR3 _EyePos, const D3DXVECTOR3 _LookPos , const float _RotX, const float _RotY, const float _Distance ) ;
};

