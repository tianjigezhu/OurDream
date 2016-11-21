//********************************************
//********************************************

#include <ddraw.h>
#if _MSC_VER==1300
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION         0x0800
#endif
#endif
#include <dinput.h>

#include "..\gamelib\ddutil.h"
#include "..\gamelib\gp_init.h"
#include "..\gamelib\gp_draw.h"
#include "..\gamelib\gp_alpha.h"
#include "..\gamelib\gp_ani.h"
#include "..\gamelib\gp_text.h"
#include "..\gamelib\gp_input.h"
#include "..\gamelib\gp_sound.h"
#include "..\gamelib\gp_music.h"
#include "..\gamelib\gp_other.h"
#include "..\gamelib\gp_iniset.h"
#include "..\gamelib\gp_avi.h"