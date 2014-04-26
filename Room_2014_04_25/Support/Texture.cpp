#include "DXUT.h"
#include "Texture.h"
using namespace std;


std::map<std::string, LPDIRECT3DTEXTURE9> Texture::StringTexture ;

LPDIRECT3DTEXTURE9 Texture::MakeTexture( const string& pFileName )
{
	m_pObj = new Info( pFileName ) ;
	m_image_info = m_pObj->m_image_info ;
	return m_pObj->m_texture ;
}

LPDIRECT3DTEXTURE9 Texture::Load( const string FileName )
{
	map< string, LPDIRECT3DTEXTURE9 >::iterator it ;
	//	�t�@�C�����Ō���
	it = StringTexture.find( FileName ) ;
	//	�t�@�C�����̃e�N�X�`�����������Ȃ��Ȃ�e�N�X�`����ǉ�
	if( it == StringTexture.end() ){
		LPDIRECT3DTEXTURE9 texture  = MakeTexture( FileName ) ;
		return texture ;
	}
	return (*it).second ;
}