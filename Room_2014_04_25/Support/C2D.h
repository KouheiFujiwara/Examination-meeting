#pragma once
#include "DXUT.h"
#include <string>
#include <windows.h>
#include <list>

class C2D 
{
private :
	std::string m_pFileName ;			// 画像のパス
	RECT m_rect ;						// 画像のどの範囲を描画するか
	D3DXIMAGE_INFO m_image_info ;		// 画像情報( 幅や高さなど )の取得用
	LPDIRECT3DTEXTURE9 m_texture ;		// 画像データ( テクスチャ )
	LPD3DXSPRITE m_sprite ;				// スプライト( DirectX の2Dを扱うクラス ) 
	D3DXVECTOR3 m_img_size ;			// 画像のサイズ
	D3DXVECTOR3 m_suf_size ;			// サーフェイスのサイズ
	D3DXVECTOR3 m_center ;				// 画像の中心
	D3DXVECTOR3 m_scale_ofs ;			// オフセットスケール
	bool m_is_add_alpha ;				// 加算半透明のフラグ
	bool m_scl_flg ;					// 拡縮のリセットを一回だけ行う
	IDirect3DDevice9* m_pd3dDevice ;	//	画像パスを受け取るパス
	float m_Left ;						// 画像の描画範囲
	float m_Top ;						// 画像の描画範囲
	float m_Right ;						// 画像の描画範囲
	float m_Bottom ;					// 画像の描画範囲

public :
	D3DXVECTOR3 m_scl ;					// スケール
	D3DXVECTOR3 m_pos ;					// 描画座標
	float m_sclFloat ;
	float m_rot ;						// 回転角度
	float m_alpha ;						// 透明度
	C2D( const std::string& FileName,int num = 1 ) ;
	~C2D() ;

	void Logic();
	//	座標、大きさ、アニメーションするかどうか？(trueならする)、アニメーション番号
	void Draw( bool AnimeFlg = false, int num = 0 );

	int m_num ;
} ;