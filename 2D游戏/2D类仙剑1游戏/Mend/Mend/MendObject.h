#ifndef _MEND_OBJECT_H_
#define _MEND_OBJECT_H_

#include "MendCScript.h"
#include "MendCMemory.h"

namespace Mend
{
	namespace MendObject
	{
		template < typename T >
		class CObjHandle
		{
		public:

		private:
			CMemoryHandle* m_pMemoryHandle;
		};
	}
}

#endif