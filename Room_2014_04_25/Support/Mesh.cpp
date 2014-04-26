#include "DXUT.h"
#include "Mesh.h"
#include "GlobalD3DDevice.h"
#include "DXconvAnsiToWide.h"

//	�Ǘ��}�b�v
Mesh* Mesh::m_pMesh ;
std::map< std::string, Mesh* > Mesh::m_Mesh ;

//	����
Mesh* Mesh::Create( const std::string &_path ) 
{
	Mesh *pMesh = NULL ;

	//	�Ǘ��}�b�v���炷�łɃ�������ɑ��݂��Ȃ����d���`�F�b�N
	std::map< std::string, Mesh* >::iterator it = m_Mesh.find( _path ) ;

	//	���݂��Ȃ���ΐV�������[�h
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
		
		//	�Ǘ��}�b�v�ɓo�^
		m_Mesh.insert( std::make_pair( _path, pMesh ) ) ;

	//	���łɑ��݂���e�N�X�`����Ԃ�
	}else{
		pMesh = it->second ;
	}

	return pMesh ;
}

//	���b�V���̉��
void Mesh::Destroy( std::string m_Name ) 
{
	std::map< std::string, Mesh* >::iterator it = m_Mesh.begin() ;

	//	�S�����
	if( m_Name == "all" ){
		while( it != m_Mesh.end() ){
			SAFE_RELEASE( (it->second)->m_DirectxMesh ) ;
			SAFE_RELEASE( (it->second)->m_MaterialBuff ) ;
			SAFE_DELETE( (it->second) ) ;
			m_Mesh.erase( it++ ) ;
		}
	//	�e�N�X�`����1�������
	}else{
		it = m_Mesh.find( m_Name ) ;
		if( it != m_Mesh.end() ){
			SAFE_RELEASE( (it->second)->m_DirectxMesh ) ;
			SAFE_RELEASE( (it->second)->m_MaterialBuff ) ;
			SAFE_DELETE( (it->second) ) ;
		}
	}
}
