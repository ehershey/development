/********************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0			*
 ********************************************************************
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez				*
 * See license.txt for modification and distribution information	*
 ********************************************************************/

#include "stdafx.h"
#include "Texture.h"
#include "GraphicsLayer.h"
#include "DxHelper.h"

using std::vector;

bool cTexture::m_bSupportsMipmaps;


int GetNumberOfBits( int mask )
{
    for( int nBits = 0; mask; nBits++ )
        mask = mask & ( mask - 1 );  

    return nBits;
}



HRESULT WINAPI EnumTextureFormats( DDPIXELFORMAT* pddpf, VOID* pVoid )
{

	vector<DDPIXELFORMAT>* pVec = (vector<DDPIXELFORMAT>*)pVoid;

	pVec->push_back( *pddpf );

    return DDENUMRET_OK;
}



cTexture::cTexture( const char* filename, DWORD stage )
{

	LPDIRECT3DTEXTURE9 pTempTex = 0;

	m_pTexture = 0;

	m_name = string( filename );
	m_stage = stage;

	ReadDDSTexture( pTempTex );

	BltToTextureSurface( pTempTex );

	SafeRelease( pTempTex );
}



cTexture::~cTexture()
{
	SafeRelease( m_pTexture );
}



void cTexture::ReadDDSTexture( LPDIRECT3DTEXTURE9& pTexture )
{
	HRESULT r = 0;
	
	r = D3DXCreateTextureFromFile(
		Graphics()->GetDevice(),
		m_name.c_str(),
		&pTexture );

	if( FAILED( r ) )
	{
		throw cGameError( "Bad DDS file\n");
	}
}


LPDIRECT3DTEXTURE9 cTexture::GetTexture()
{
	return m_pTexture;
}

void cTexture::BltToTextureSurface(LPDIRECT3DTEXTURE9 pTempTex )
{

	SafeRelease( m_pTexture );

	D3DSURFACE_DESC TexDesc;

	pTempTex->GetLevelDesc( 0, &TexDesc );
	DWORD NumLevels = pTempTex->GetLevelCount();
	
	D3DXCreateTexture( 
		Graphics()->GetDevice(),
		TexDesc.Width,
		TexDesc.Height,
		NumLevels,
		0,
		TexDesc.Format,
		D3DPOOL_MANAGED,
		&m_pTexture );

	LPDIRECT3DSURFACE9 pSrcSurf = 0;
	LPDIRECT3DSURFACE9 pDestSurf = 0;

	for( int i = 0 ; i < NumLevels ; i++ )
	{
		m_pTexture->GetSurfaceLevel( i, &pDestSurf );
		pTempTex->GetSurfaceLevel( i, &pSrcSurf );

		D3DXLoadSurfaceFromSurface( 
			pDestSurf,
			0,
			0,
			pSrcSurf,
			0,
			0,
			D3DX_FILTER_NONE,
			0 );

		pDestSurf->Release();
		pSrcSurf->Release();
	}

}

