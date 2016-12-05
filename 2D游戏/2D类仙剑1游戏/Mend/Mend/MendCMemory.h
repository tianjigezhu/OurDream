#ifndef _MEND_CMEMORY_H_
#define _MEND_CMEMORY_H_

#include <stdlib.h>
#include "MendTypes.h"

namespace Mend
{
	namespace MendMemory
	{
		class CMemoryHandle
		{
		public:
			MendTypes::s32 getCount() { return m_count; }
			MendTypes::s32 getCapacity() { return m_capacity; }
			MendTypes::pvoid getPObj() { return pobj; }
			void add(CMemoryHandle* pMemoryHandle) 
			{ 
				pMemoryHandle->next = this->next; 
				this->next = pMemoryHandle; 
			}
			void setCapacity(MendTypes::s32 capacity) { m_capacity = capacity; }
			CMemoryHandle* getNext() { return next; };
			friend class CMemoryManager;



		private:
			// 此块内存是否使用中
			
			MendTypes::MendBool used;
			CMemoryHandle(CMemoryHandle& obj);
			CMemoryHandle& operator=(CMemoryHandle&);
			// 外部请求分配的内存大小
			MendTypes::s32 m_count;
			// 进行内存对其后实际分配的内存大小
			MendTypes::s32 m_capacity;
			// 内存指针
			MendTypes::pvoid pobj;
			// 指向下一个内存句柄的指针
			// 内存管理模块不使用这个指针，由实际使用本块内存的其他模块使用
			// 其他模块用来串接每个对象。
			CMemoryHandle *next;
		};

		class CMemoryManager
		{
		public:
			CMemoryManager() {}
			virtual ~CMemoryManager() {}
			// 分配内存
			virtual CMemoryHandle* allocate(MendTypes::s32 count);
			// 初始化内存管理模块
			virtual MendTypes::MendBool init();
			// 回收内存
			virtual void reclaime(CMemoryHandle*);
			// 整列内存碎片，根据返回值判断成功或者失败
			virtual MendTypes::MendBool fragmentate();
			// 关闭内存管理器
			virtual void shutdown();

		private:
			void changeStartPtr(MendTypes::s32 count)
			{
				m_pstart = (MendTypes::ps8)m_pstart + count;
				//m_pstart = m_pstart + count;
			}
			void changeEndPtr(MendTypes::s32 count)
			{
				m_pend;
				m_pend = (MendTypes::ps8)m_pend - count;
				//m_pend = m_pend - count;
			}

			typedef CMemoryHandle MemoryHandle;
			MendTypes::pvoid m_pmemory;
			MendTypes::u32 m_memoryCount;
			MendTypes::pvoid m_pstart;
			MendTypes::pvoid m_pend;
			MemoryHandle *m_handleList;
			MendTypes::s32 m_handleListSize;
			MemoryHandle* m_tempHandle;
			static MendTypes::s32 m_objhandlesize;
		};
	}
}

#endif