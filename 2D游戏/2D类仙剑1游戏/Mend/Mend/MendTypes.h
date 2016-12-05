#ifndef _MEND_TYPES_H_
#define _MEND_TYPES_H_

namespace Mend
{
namespace MendTypes
{

	//! 8 bit unsigned variable.
	/** This is a typedef for unsigned char, it ensures portability of the engine. */
	typedef unsigned char u8;
	typedef unsigned char* pu8;

	//! 8 bit signed variable.
	/** This is a typedef for signed char, it ensures portability of the engine. */
	typedef signed char			s8; 
	typedef signed char*		ps8;

	//! 8 bit character variable.
	/** This is a typedef for char, it ensures portability of the engine. */
	typedef char				c8;
	typedef char*			    pc8;
	typedef const char*          cpc8;

	//! 16 bit unsigned variable.
	/** This is a typedef for unsigned short, it ensures portability of the engine. */
	typedef unsigned short		u16;
	typedef unsigned short*		pu16;

	//! 16 bit signed variable.
	/** This is a typedef for signed short, it ensures portability of the engine. */
	typedef signed short		s16; 
	typedef signed short*		ps16;

	//! 32 bit unsigned variable.
	/** This is a typedef for unsigned int, it ensures portability of the engine. */
	typedef unsigned int		u32;
	typedef unsigned int*		pu32;

	//! 32 bit signed variable.
	/** This is a typedef for signed int, it ensures portability of the engine. */
	typedef signed int			s32; 
	typedef signed int*			ps32;

	//! 64 bit signed variable.
	/** This is a typedef for __int64, it ensures portability of the engine. */
	typedef long long				s64; 
	typedef long long*				ps64;

	//! 32 bit floating point variable.
	/** This is a typedef for float, it ensures portability of the engine. */
	typedef float				f32;
	typedef float*				pf32;

	//! 64 bit floating point variable.
	/** This is a typedef for double, it ensures portability of the engine. */
	typedef double				f64;
	typedef f64*				pf64;
	typedef void*				pvoid;
	
	struct POSITION
	{
		s32 x;
		s32 y;
	};

	enum MendBool
	{
		MendFalse=0,
		MendTrue=1
	};
}	
}

#ifndef _WCHAR_T_DEFINED
//! A 16 bit wide character type.
/**
	Defines the wchar_t-type.
	In VS6, its not possible to tell
	the standard compiler to treat wchar_t as a built-in type, and 
	sometimes we just don't want to include the huge stdlib.h or wchar.h,
	so we'll use this.
*/
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#endif