#pragma once
#include "BaseObj.h"
#include <memory>
#include <string>

class Camera ;

typedef struct tag_POINTSPRITE 
{
	D3DXVECTOR3 vPos ;
	float		fSize ;
	DWORD		dwColor ;
}	POINTSPRITE ;

class PointSprite : public BaseObj 
{
private :
	LPDIRECT3DTEXTURE9		m_Texture ;		//	テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_VB ;			//	頂点バッファ
	D3DXMATRIX				g_WorldMtx ;	// エミッターのワールドマトリクス

public:
	PointSprite(){} ;
	~PointSprite(){};

	static PointSprite* Create( const std::string _fileName ) ;
	void Load( const std::string _fileName ) ;
	void Render( const Camera *_camera ) ;
};

