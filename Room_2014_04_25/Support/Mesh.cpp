#include "DXUT.h"
#include "Mesh.h"
#include "GlobalD3DDevice.h"
#include "DXconvAnsiToWide.h"

//	管理マップ
Mesh* Mesh::m_pMesh ;
std::map< std::string, Mesh* > Mesh::m_Mesh ;

//	生成
Mesh* Mesh::Create( const std::string &_path ) 
{
	Mesh *pMesh = NULL ;

	//	管理マップからすでにメモリ上に存在しないか重複チェック
	std::map< std::string, Mesh* >::iterator it = m_Mesh.find( _path ) ;

	//	存在しなければ新しくロード
	if( it == m_Mesh.end() ){
		pMesh = new Mesh() ;
		pMesh->m_Name = _path ;
		WCHAR wcBuff[ 255 ] = { 0 } ;
		
		DXconvAnsiToWide::Change( wcBuff, _path.c_str(),255 ) ;
		D3DXLoadMeshFromX( wcBuff, 
			D3DXMESH_MANAGED, 
			GlobalD3DDevice::m_pd3dDevice,
			NULL, &pMesh->m_MaterialBuff, 
			NULL, &pMesh->m_MaterialNum, 
			&pMesh->m_DirectxMesh ) ;
		
		//	管理マップに登録
		m_Mesh.insert( std::make_pair( _path, pMesh ) ) ;

	//	すでに存在するテクスチャを返す
	}else{
		pMesh = it->second ;
	}

	return pMesh ;
}

//	メッシュの解放
void Mesh::Destroy( std::string m_Name ) 
{
	std::map< std::string, Mesh* >::iterator it = m_Mesh.begin() ;

	//	全部解放
	if( m_Name == "all" ){
		while( it != m_Mesh.end() ){
			SAFE_RELEASE( (it->second)->m_DirectxMesh ) ;
			SAFE_RELEASE( (it->second)->m_MaterialBuff ) ;
			SAFE_DELETE( (it->second) ) ;
			m_Mesh.erase( it++ ) ;
		}
	//	テクスチャを1つだけ解放
	}else{
		it = m_Mesh.find( m_Name ) ;
		if( it != m_Mesh.end() ){
			SAFE_RELEASE( (it->second)->m_DirectxMesh ) ;
			SAFE_RELEASE( (it->second)->m_MaterialBuff ) ;
			SAFE_DELETE( (it->second) ) ;
		}
	}
}
