//	�O���t�B�b�N�V�F�[�_�[���������}�l�[�W���[

#pragma once
#include "DXUT.h"
#include <list>
#include <memory>

class Camera ;
class BaseObj ;

class CGraphicsManager
{
private :
	static CGraphicsManager *SharedInstance ;
	
	CGraphicsManager(){}
	~CGraphicsManager(){}
	CGraphicsManager( const CGraphicsManager &obj ) ;
	CGraphicsManager& operator = ( const CGraphicsManager &obj ) ;

public :
	//---------------------------------------------------------------------
	//
	// �V�F�[�_�֘A
	//	( �ǉ��\�[�X2013.07.12 )

	static LPD3DXEFFECT m_sdr ;					// �V�F�[�_�{��
	static D3DXHANDLE	m_sdr_technique ;		// �e�N�j�b�N
	static D3DXHANDLE	m_sdr_tex ;				// �e�N�X�`��
	static D3DXHANDLE	m_sdr_color ;			// �J���[
	static D3DXHANDLE	m_sdr_wvmp ;			// ���[���h x �r���[ x �v���W�F�N�V�����s��
	static D3DXHANDLE	m_sdr_light ;			//	���s�����̌���
	static D3DXHANDLE	m_sdr_rot ;				// ��]�s��

	static std::list< BaseObj* > m_RenderList ;

	static void Erase( BaseObj* _obj ) ;

	static CGraphicsManager *Initialize() ;
	static void Destroy() ;

	static void SysRender( const Camera* _camera ) ;
} ;

