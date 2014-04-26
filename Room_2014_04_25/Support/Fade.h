//	フェードイン・フェードアウト用クラス

#pragma once
#include "DXUT.h"

//	フェードイメージのアルファに加算する数字
#define BLENDER_NUM (5) 
//	アルファのMAX値
#define ALPHA_MAX (255)

class C2D ;

//	シングルトーンパターン

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

	//	フェード種類
	enum
	{
		MODE_NONE = -1,	//	何もしない
		MODE_IN,		//	フェードイン
		MODE_OUT		//	フェードアウト
	};

	//	フェードモード
	int m_Mode ;

	//	フェードイメージ( 一応フェードアウト･イン共有イメージ ) 
	C2D* m_OutAndInImage ;

	//	フェードしているかどうか	
	//	true	:	現在フェードアウト・イン動作中
	//	false	:	フェード停止中
	bool m_DoFlag ;

	//	クラスNewの最中にフェードインをしないためのフラグ
	//	true	:	現在生成･開放中
	//	false	:	生成･開放完了
	bool m_NewDeleteFlag ;

	//	画像のアルファがリミット値に達しているかどうか
	//	true	:	アルファが達している
	//	false	:	アルファ変動中
	bool m_FadeOutLimitFlag ;

public:
	//	ゲットインスタンス
	inline static Fade* GetInstance()
	{
		if( SharedInstance == NULL )
			SharedInstance = new Fade() ;
		return SharedInstance ;
	}

	//	デリートインスタンス
	inline static void DeleteInstance()
	{
		SAFE_DELETE( SharedInstance ) ;
	}

	//	フェードを動かし始める関数
	void Start() ;

	//	ロジック関数
	void DoFadeLogic() ;

	//	描画関数
	void DoFadeDraw() ;

	inline void GetNewDelete( bool const _NewDeleteFlag )
	{
		m_NewDeleteFlag = _NewDeleteFlag ;
	}

	//	フェードアウトで真っ暗かどうか
	inline bool AlphaComplate(){ return m_FadeOutLimitFlag; } ;
	
};