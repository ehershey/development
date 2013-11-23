/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/

// cNetError.cpp: implementation of the cNetError class.
//
//////////////////////////////////////////////////////////////////////

#include "cNetError.h"
#include <string.h>
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>  // OutputDebugString()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cNetError::cNetError()
{
  d_text[ 0 ] = NULL;
}


cNetError::~cNetError()
{
}


cNetError::cNetError( const char *pText )
{
  if( pText == NULL )
    strcpy( d_text, "Unspecified." );
  else
    strcpy( d_text, pText );

  OutputDebugString( "Network Error: " );
  OutputDebugString( d_text );
  OutputDebugString( "\n" );
}

