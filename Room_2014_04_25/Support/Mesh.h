#pragma once
#include "DXUT.h"
#include <string>
#include <map>

class Mesh
{
public:
	Mesh(){} ;
	~Mesh(){} ;

	static Mesh *m_pMesh ;

	//	�Ǘ��}�b�v
	static std::map< std::string, Mesh* > m_Mesh ;

	//	����
	static Mesh *Create( const std::string &m_Path ) ;

	//	�e�N�X�`���̉��( ���O���w�肵�ȂƑS����� )
	static void Destroy( std::string m_Name = "all" ) ;

	std::string		m_Name ;			// �e�N�X�`���̖��O
	DWORD			m_MaterialNum ;		// �}�e���A���̐�
	LPD3DXMESH		m_DirectxMesh ;		// DirectX ���b�V��
	LPD3DXBUFFER	m_MaterialBuff ;	// �}�e���A���o�b�t�@
};

