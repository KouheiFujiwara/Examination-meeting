#pragma once

//	光線用
struct Ray
{
	D3DXVECTOR3 p ;	// 直線上に存在する点
	D3DXVECTOR3 v ; // 直線の向き
} ;

class HitJudgments
{
private:
	HitJudgments(){};
	~HitJudgments(){};

	HitJudgments( const HitJudgments& obj ) ;
	HitJudgments& operator = ( const HitJudgments& obj ) ;

	static HitJudgments* SharedInstance ;

public:
	static inline HitJudgments* GetInstance()
	{
		if( SharedInstance == NULL )
			SharedInstance = new HitJudgments() ;
		return SharedInstance ;
	}

	static inline void DeleteInstance(){ SAFE_DELETE(SharedInstance) ; }

	//---------------------------------------------------------------------------------------------------------
	//										円と線の衝突判定
	//	戻り値: bool型 
	//	<引数>
	//	_center		球の中央の座標
	//	_rad		球の半径
	//	_Spos		線のスタートライン
	//	_Epos		線のエンドライン
	//static bool CircleLineCollide( const D3DXVECTOR3 _center, const float _rad, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos ) ;

	//---------------------------------------------------------------------------------------------------------
	//										線分と点の最近接点
	//	戻り値: 
	static D3DXVECTOR3 ClosestPtPointSegment( const D3DXVECTOR3 _center, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos ) ;

	//---------------------------------------------------------------------------------------------------------
	//										円と線の衝突判定と補正
	//	戻り値: bool型 
	//	<引数>
	//	_center		球の中央の座標
	//	_rad		球の半径
	//	_Spos		線のスタートライン
	//	_Epos		線のエンドライン
	static D3DXVECTOR3 CircleLineCollideCompensation( const D3DXVECTOR3 _center, const float _rad, const D3DXVECTOR3 _Spos, const D3DXVECTOR3 _Epos ) ;

	//===========================================================================================
	// 球と無限レイの衝突判定
	// arg1... 球の半径
	// arg2... 球の中心座標
	// arg3... レイ上に存在する座標
	// arg4... レイの方向ベクトル
	// ret.... [ 衝突している : true ] [ 衝突していない: true ]
	//===========================================================================================
	bool IntersectSphereRay( float _sr, D3DXVECTOR3 _sp, D3DXVECTOR3 _rp, D3DXVECTOR3 _rv ) ;


	//===========================================================================================
	// name... ScreenToRay
	// work... スクリーン座標の指定でレイを作成する
	// arg1... スクリーン上の座標 X
	// arg2... スクリーン上の座標 Y
	// arg5... カメラのビュー行列
	// arg6... カメラのプロジェクション行列
	// arg7... DirectX へのデバイス
	// ret.... 演算結果
	// note... none
	//===========================================================================================
	Ray ScreenToRay( int _sx, int _sy, D3DXMATRIX _view, D3DXMATRIX _proj, IDirect3DDevice9* _p_deviece ) ;
};

