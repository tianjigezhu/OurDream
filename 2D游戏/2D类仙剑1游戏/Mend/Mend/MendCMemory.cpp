#include "defines.h"
#include "MendCMemory.h"
#include "MendTypes.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

namespace Mend
{
namespace MendMemory
{

MendTypes::s32 CMemoryManager::m_objhandlesize = sizeof(CMemoryHandle);

// �����ڴ�
MendTypes::MendBool CMemoryManager::init()
{
	m_pmemory = NULL;
	m_pstart = NULL;
	m_pend = NULL;
	m_handleList = NULL;
	m_handleListSize = 0;
	m_tempHandle = NULL;
	m_memoryCount = MEMORYSIZE;
	m_memoryCount = m_memoryCount * 1024;
	m_memoryCount = m_memoryCount * 1024;
	m_pmemory = (MendTypes::pvoid)malloc(m_memoryCount);
	memset(m_pmemory, 0, m_memoryCount);
	m_pstart = m_pmemory;
	m_pend = (MendTypes::ps8)m_pmemory + m_memoryCount - 1;

	if (m_pmemory)
		return MendTypes::MendTrue;
	return MendTypes::MendFalse;
}

// �����ڴ�
void CMemoryManager::reclaime(CMemoryHandle* pObjHandle)
{
	// �����صľ��������ӵ����ж�����
	m_tempHandle = m_handleList;
	while (m_tempHandle) {
		if (m_tempHandle == pObjHandle) {
			m_tempHandle->used = MendTypes::MendFalse;
			break;
		}

		// �ж������Ƿ��ѵ���
		++m_tempHandle;
		if (m_tempHandle - m_handleList == m_handleListSize)
			break;
	}

	// �����ж��н����ڵ��ڴ�ϲ�
	// Ŀǰ��δ���ǵ�ַ����
	m_tempHandle = m_handleList;
	while (m_tempHandle) {
		CMemoryHandle* tempHandle = m_tempHandle + 1;
		MendTypes::pvoid ptr = (MendTypes::pc8)m_tempHandle->pobj + m_tempHandle->m_count;
		if (ptr == tempHandle->pobj) {
			tempHandle->m_count += m_tempHandle->m_count;
			m_tempHandle->used = MendTypes::MendFalse;
			m_tempHandle->m_count = 0;
			m_tempHandle->m_capacity = 0;
		}
		++m_tempHandle;
	}
}

// �����ڴ�
CMemoryHandle* CMemoryManager::allocate(MendTypes::s32 count)
{
	// Ŀǰ��δ�������ݶ���

	// ����ڴ治������ʾ��Ϣ����������Ϣ������־��
	if ((MendTypes::pc8)m_pstart + count >= m_pend) {
		
	}
	// ���������������Ƿ��������ڴ��СҪ��Ķ�����
	// ����оͽ��ö���������Ϊʹ�ã������ظö�����ָ��
	// �������ڴ���з����ڴ�
	m_tempHandle = m_handleList;
	while (m_tempHandle) {
		if (m_tempHandle->m_count >= count &&
			m_tempHandle->used == MendTypes::MendFalse) {
			m_tempHandle->used =  MendTypes::MendTrue;;
			memset(m_tempHandle->pobj, 0, m_tempHandle->m_count);
			return m_tempHandle;
		}
		++m_tempHandle;
		if (m_tempHandle - m_handleList >= m_handleListSize)
			break;
	}

	// ��������ڴ棬��С��count
	// ������Ҫ���Ƕ���
	changeEndPtr(count);

	// ���������
	// ��������ָ����ӵ�������������
	if (m_handleList) {
		// ���������������ڣ�����������һ������һ��δʹ�õ��ڴ�ת��Ϊ������
		++m_handleListSize;
	} else {
		// ��������ڣ�����ʼ��ַǿ��ת��Ϊ������
		m_handleList = static_cast<MemoryHandle*>(m_pstart);
	}
	m_tempHandle = m_handleList + m_handleListSize;
	m_tempHandle->m_count = count;
	m_tempHandle->m_capacity = count;
	m_tempHandle->pobj = m_pend;
	m_tempHandle->used = MendTypes::MendTrue;
	changeStartPtr(m_objhandlesize);
	m_tempHandle->next = NULL;

	return m_tempHandle;
}

// �ر��ڴ������
void CMemoryManager::shutdown()
{
	if (m_pmemory) {
		delete m_pmemory;
		m_memoryCount = 0;
		m_pstart = NULL;
		m_pend = NULL;
		m_handleList = NULL;
		m_tempHandle = NULL;
		m_handleListSize = 0;
		m_pmemory = NULL;
	}
}

// �����ڴ���Ƭ�����ݷ���ֵ�жϳɹ�����ʧ��
MendTypes::MendBool CMemoryManager::fragmentate()
{
	// Ŀǰ���ţ������е㸴�ӡ�
	return MendTypes::MendTrue;
}

}
}