#include "DXUT.h"
#include "C3DFactory.h"


C3DFactory::C3DFactory( int PorigonNum )
{
	m_IndexNum	= PorigonNum * 3  ;
	m_VertexNum	= PorigonNum  ;

	//---------------------------------------------------------------------
	//
	//	インデックスデータ作成
	//
	WORD*	pIndexs = new WORD[ m_IndexNum ] ;
	int cont = 0 ;
	for( int i = 0; i < m_IndexNum; i++ )
	{
		cont++ ;
	}

	//---------------------------------------------------------------------
	//	
	//	頂点データ作成
	//
	WORD*	pVertex	= new WORD[ m_VertexNum ] ;

}


C3DFactory::~C3DFactory()
{
}
