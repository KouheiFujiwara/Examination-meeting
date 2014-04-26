//	頂点座標

#pragma once

class CVertex 
{
public:
	CVertex(){} ;
	~CVertex();
	//-------------------------------------------------------------
	//	宣言の順番はこのとおり(座標、法線、UV座標、カラー) 
	//
	D3DXVECTOR3	m_Pos ;			//	座標
	D3DXVECTOR3 m_NormalLine ;	//	法線
	D3DXVECTOR2 m_UV ;			//	UV座標(一色のみでのテクスチャ)
	D3DXVECTOR4 m_Color ;		//	カラー		

	static CVertex* m_pCVertex ;
};

