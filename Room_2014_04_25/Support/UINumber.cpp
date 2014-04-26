#include "DXUT.h"
#include "UINumber.h"
#include "C2D.h"


UINumber::UINumber( const std::string& _FileName,const D3DXVECTOR3& _BasePos, const float _Interval )
{
	m_Interval = _Interval ;
	m_Number = new C2D(_FileName,10) ;
	m_Number->m_pos = _BasePos ;
}

void UINumber::Draw( int _Num ) 
{
	char buf[Beam] = { 0 } ;
	int num	= 0 ;

	num = sprintf( buf,"%d", _Num ) ;

	for( int i = 0 ; i <= num; i++)
	{
		m_Number->m_pos.x = m_Number->m_pos.x + ( i * m_Interval ) ;
		m_Number->m_pos.y = m_Number->m_pos.y ;
		m_Number->Draw( true,buf[i] - '0') ;
	}
}