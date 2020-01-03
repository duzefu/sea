/*
**  mainfun.h
**  application main functions header.
**
**  Jack, 2002.3.25.
*/
#ifndef _MAINFUN_H_
#define _MAINFUN_H_

#include "rays.h"
#include "winmain.h"
#include "xmodule.h"
#include "xsystem.h"
#include "xkiss.h"
#include "xdraw.h"
#include "xsound.h"
#include "xinput.h"
#include "xplay.h"
#include "xmedia.h"
#include "xcdrom.h"
#include "xfont.h"
#include "xcak.h"
#include "xgrafx.h"
#include "xpoly.h"
#include "xrle.h"
#include "xrla.h"
#include "xtimer.h"
#include "vbmp.h"
#include "vpcx.h"
#include "vpsd.h"
#include "vtga.h"
#include "function.h"
#include "menutree.h"
#include "menuwin.h"
#include "readinfo.h"
#include "ripple.h"
#include "topo.h"
#include "undo.h"
#include "str2num.h"
#include "packfile.h"
#include "mp3.h"
#include "jpeg.h"



#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600


#ifdef  DEBUG
#pragma comment(lib, "2denginedbg.lib")
#pragma comment(lib, "jpegdbg.lib")
#else//!DEBUG
#pragma comment(lib, "2dengine.lib")
#pragma comment(lib, "jpeg.lib")
#endif//DEBUG




#endif//_MAINFUN_H_
