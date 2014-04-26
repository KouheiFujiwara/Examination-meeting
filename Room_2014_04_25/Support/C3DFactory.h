#pragma once
#include "Vertex.h"

#define VTX_MAX (3)
#define IDX_MAX (3)

class C3DFactory
{
protected:
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer ;
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer ;

public:
	C3DFactory( int PorigonNum = 1 );
	~C3DFactory();

	D3DXVECTOR3 m_Pos ;		//	�`����W
	D3DXVECTOR3 m_Rot ;		//	��]�p�x
	D3DXVECTOR3 m_Scl ;		//	�T�C�Y

	int m_IndexNum ;
	int m_VertexNum ;
};

