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
			// �˿��ڴ��Ƿ�ʹ����
			
			MendTypes::MendBool used;
			CMemoryHandle(CMemoryHandle& obj);
			CMemoryHandle& operator=(CMemoryHandle&);
			// �ⲿ���������ڴ��С
			MendTypes::s32 m_count;
			// �����ڴ�����ʵ�ʷ�����ڴ��С
			MendTypes::s32 m_capacity;
			// �ڴ�ָ��
			MendTypes::pvoid pobj;
			// ָ����һ���ڴ�����ָ��
			// �ڴ����ģ�鲻ʹ�����ָ�룬��ʵ��ʹ�ñ����ڴ������ģ��ʹ��
			// ����ģ����������ÿ������
			CMemoryHandle *next;
		};

		class CMemoryManager
		{
		public:
			CMemoryManager() {}
			virtual ~CMemoryManager() {}
			// �����ڴ�
			virtual CMemoryHandle* allocate(MendTypes::s32 count);
			// ��ʼ���ڴ����ģ��
			virtual MendTypes::MendBool init();
			// �����ڴ�
			virtual void reclaime(CMemoryHandle*);
			// �����ڴ���Ƭ�����ݷ���ֵ�жϳɹ�����ʧ��
			virtual MendTypes::MendBool fragmentate();
			// �ر��ڴ������
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