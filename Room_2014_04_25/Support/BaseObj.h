#pragma once
#include <memory>

class Camera ;

class BaseObj
{
public:
	//	加算フラグ
	bool m_IsAddBlend ;

	//	物体の半径
	float		m_Rad ;

	D3DXVECTOR3 m_Pos ;		//	座標
	D3DXVECTOR3 m_Scl ;		//	拡大縮小
	D3DXVECTOR3 m_Rot ;		//	XYZ指定
	D3DXQUATERNION m_Qtn ;	//	姿勢
	D3DXVECTOR4 m_Col ;

	D3DXMATRIX m_RotMtx ;	//	ビルボードにのみ使う

	//	あるやつはある移動方向
	D3DXVECTOR3 m_Dir ;

	friend class CGraphicsManager ;

	//	ソートの基準となる値(カメラの距離)
	float m_CameraDistance ;

	//	ビルボード
	bool m_BillFlg ;

	BaseObj() :
		m_IsAddBlend( false ),
		m_Pos( 0, 0, 0 ),
		m_Scl( 1, 1, 1 ),
		m_Col( 1, 1, 1, 1 ),
		m_BillFlg(false),
		m_Rot( 0, 0, 0 ) 
	{
		D3DXQuaternionIdentity( &m_Qtn ) ;
	}

	// 継承するので virtual
	virtual ~BaseObj(){};

	// 純粋仮想関数
	virtual void Render( const Camera* _camera ) = 0 ;

	// std::list のソートで使用する
	static bool comp(const BaseObj* riLeft, const BaseObj* riRight){
		return ( riLeft->m_CameraDistance > riRight->m_CameraDistance ) ;
    }
};