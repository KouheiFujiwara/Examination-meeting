#pragma once
#include <string>
#include <vector>
#include <memory>

class CFont{
private:
	

	// �t�H���g
	LPD3DXFONT m_font ;

	// �t�H���g���( ���̏������Ƀt�H���g����� )
	D3DXFONT_DESC m_font_info ;
	
	RECT m_rect;

	D3DCOLOR m_color ;

	//�R���X�g���N�^
	CFont( int _x_size, int _y_size, const LPCWSTR _fontname ) ;
	

public:

	//�f�X�g���N�^
	~CFont(){SAFE_RELEASE(m_font) ;}

	void Destroy(){
		SAFE_RELEASE(m_font) ;
	}

	//�����T�C�Y�c���A�t�H���g��
	static std::shared_ptr<CFont> Create( int _x_size, int _y_size, const LPCWSTR _fontname ) ;

	//�`����W�A�J��p�[
	void setPosCol( int x, int y, D3DCOLOR col ) ;
	
	//�`��
	void Draw( std::string _string );

	////�e�L�X�g�`��
	//void DrawFontText(int x, int y, D3DCOLOR col,
	//	const wchar_t* pFormat, ...);	
};
