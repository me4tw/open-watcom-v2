/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  None Default Windowing support
*
****************************************************************************/

#include "_defwin.h"
#include <stddef.h>


#pragma aux __init_default_win "*";
char __init_default_win;

LPWDATA (*_WindowsIsWindowedHandle)( int h ) = { NULL };
void (*_WindowsRemoveWindowedHandle)( int h ) = { NULL };
unsigned (*_WindowsNewWindow)( const char *s, ... ) = { NULL };
int (*_WindowsCloseWindow)( LPWDATA lp ) = { NULL };
int (*_WindowsSetAbout)( const char *p1, const char *p2 ) = { NULL };
int (*_WindowsSetAppTitle)( const char *p ) = { NULL };
int (*_WindowsSetConTitle)( LPWDATA lp, const char *s ) = { NULL };
int (*_WindowsDestroyOnClose)( LPWDATA lp ) = { NULL };
int (*_WindowsYieldControl)( void ) = { NULL };
int (*_WindowsShutDown)( void ) = { NULL };
unsigned (*_WindowsStdin)( LPWDATA lp, void *p, unsigned u ) = { NULL };
unsigned (*_WindowsStdout)( LPWDATA lp, const void *p, unsigned u ) = { NULL };
unsigned (*_WindowsKbhit)( LPWDATA lp ) = { NULL };
unsigned (*_WindowsGetch)( LPWDATA lp ) = { NULL };
unsigned (*_WindowsGetche)( LPWDATA lp ) = { NULL };
void (*_WindowsPutch)( LPWDATA lp, unsigned u ) = { NULL };
void (*_WindowsExitRtn)( void ) = { NULL };

#if ( defined(__OS2__) && (defined(__386__)||defined(__PPC__)) ) || defined(__NT__) || \
    defined(__WINDOWS_386__) || defined(__WINDOWS__)

#define __SW_BW
#include "variety.h"
#include <wdefwin.h>

_WCRTLINK int   _dwDeleteOnClose( int handle ) {
    handle = handle;
    return( 0 );
}

_WCRTLINK int   _dwSetAboutDlg( const char *title, const char *text ) {
    text = text;
    title = title;
    return( 0 );
}

_WCRTLINK int   _dwSetAppTitle( const char *title ) {
    title = title;
    return( 0 );
}

_WCRTLINK int   _dwSetConTitle( int handle, const char *title ) {
    handle = handle;
    title = title;
    return( 0 );
}

_WCRTLINK int   _dwYield( void ) {
    return( 0 );
}

_WCRTLINK int   _dwShutDown( void ) {
    return( 0 );
}

#endif
