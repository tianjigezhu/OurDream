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

// 分配内存
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

// 回收内存
void CMemoryManager::reclaime(CMemoryHandle* pObjHandle)
{
	// 将返回的句柄对象添加到空闲队列中
	m_tempHandle = m_handleList;
	while (m_tempHandle) {
		if (m_tempHandle == pObjHandle) {
			m_tempHandle->used = MendTypes::MendFalse;
			break;
		}

		// 判断数组是否已到底
		++m_tempHandle;
		if (m_tempHandle - m_handleList == m_handleListSize)
			break;
	}

	// 检查空闲队列将相邻的内存合并
	// 目前并未考虑地址对其
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

// 分配内存
CMemoryHandle* CMemoryManager::allocate(MendTypes::s32 count)
{
	// 目前并未考虑内容对齐

	// 如果内存不足则显示信息，将错误消息输入日志中
	if ((MendTypes::pc8)m_pstart + count >= m_pend) {
		
	}
	// 检查对象句柄链表中是否有满足内存大小要求的对象句柄
	// 如果有就将该对象句柄设置为使用，并返回该对象句柄指针
	// 否则在内存块中分配内存
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

	// 分配对象内存，大小是count
	// 这里需要考虑对齐
	changeEndPtr(count);

	// 分配对象句柄
	// 将对象句柄指针添加到对象句柄数组中
	if (m_handleList) {
		// 如果对象句柄链表存在，则将数组增加一，将下一个未使用的内存转换为对象句柄
		++m_handleListSize;
	} else {
		// 如果不存在，则将起始地址强制转换为对象句柄
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

// 关闭内存管理器
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

// 整列内存碎片，根据返回值判断成功或者失败
MendTypes::MendBool CMemoryManager::fragmentate()
{
	// 目前空着，代码有点复杂。
	return MendTypes::MendTrue;
}

}
}