#include "DXUT.h"
#include "C3DTexture.h"
#include "DXconvAnsiToWide.h"
#include "GlobalD3DDevice.h"

C3DTexture* C3DTexture::m_pC3DTexture ;
std::map< std::string, C3DTexture* > C3DTexture::m_Textures ;

//	生成
C3DTexture* C3DTexture::Create( std::string& _path ) 
{
	C3DTexture *pTex = NULL ;

	//	管理マップからすでにメモリ上に
	std::map< std::string, C3DTexture* >::iterator it = m_Textures.find( _path ) ;

	//	存在しなければ新しくロード
	if( it == m_Textures.end() ){
		pTex = new C3DTexture() ;
		pTex->m_Name = _path ;
		WCHAR wcBuff[ 255 ] = { 0 } ;
		DXconvAnsiToWide::Change( wcBuff, _path.c_str(), 255 ) ;
		D3DXCreateTextureFromFile( 
			GlobalD3DDevice::m_pd3dDevice,
			wcBuff, 
			&pTex->m_DirecxTex ) ;
		
		//	管理マップに登録
		m_Textures.insert( std::make_pair( _path, pTex ) ) ;

	//	既に存在するテクスチャを返す
	}else{
		pTex = it->second ;
	}	
	return pTex ;
}

void C3DTexture::Destroy( std::string m_Name ) 
{
	std::map< std::string, C3DTexture* >::iterator it = m_Textures.begin() ;

	//	全部解放
	if( m_Name == "all" ) {
		while( it != m_Textures.end() ){
			SAFE_RELEASE( (it->second)->m_DirecxTex ) ;
			SAFE_DELETE( (it->second) ) ;
			m_Textures.erase( it++ ) ;
		}
	//	テクスチャを1つだけ解放
	}else{
		it = m_Textures.find( m_Name ) ;
		if( it != m_Textures.end() ) {
			SAFE_RELEASE( (it->second)->m_DirecxTex ) ;
			SAFE_DELETE( (it->second) ) ;
			m_Textures.erase( it ) ;
		}
	}
	SAFE_DELETE( m_pC3DTexture ) ;
}