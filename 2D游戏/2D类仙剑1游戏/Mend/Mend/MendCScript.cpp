#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <windows.h>
#include "engine.h"

using std::fstream;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

namespace Mend
{
namespace MendScript
{

// 语法对象句柄类
// 构造函数
CGramaHandle::CGramaHandle()
{
	cObjHandleList = NULL;
	currentCObjHandle = NULL;
	currentGramaEle = NULL;
	lastCObjHandle = NULL;
}

// 添加内存句柄
void CGramaHandle::add(MendMemory::CMemoryHandle * pObjHandle)
{
	// 新添加的内存句柄永远放在第一个
	// 语法句柄中存在了内存句柄，则添加
	// 否则表明这第一次添加内存句柄，因此将内存句柄指针赋值给内存句柄数组
	if (cObjHandleList) {
		cObjHandleList->add(pObjHandle);
	} else {
		cObjHandleList = pObjHandle;
	}	
	lastCObjHandle = pObjHandle;
}

// 检查时候还有下一个语法
MendTypes::MendBool CGramaHandle::hasNext()
{
	// 返回false表明本次循环结束
	// 如果是空的语法句柄链表
	if (NULL == cObjHandleList)
		return MendTypes::MendFalse;

	// 如果本函数第一次调用，此时currentCObjHandle=NULL
	// 这时将内存句柄数组指针赋值给currentCObjHandle，表明从此处开始检测
	//如果不为空，表明此函数已经执行过了，这是将currentCObjHandle指向的内存句柄的下一个句柄传给currentCObjHandle
	// 检测就如此执行下去。
	if (NULL == currentCObjHandle) {
		currentCObjHandle = cObjHandleList;
		currentGramaEle = static_cast< struct SScriptGramaEle* >(currentCObjHandle->getPObj());
		return MendTypes::MendTrue;
	} else {
		// 如果已经执行到了内存句柄链表的末尾则返回false
		// 否则指向下一个内存句柄
		if (currentCObjHandle->getNext() == NULL) {
			// 调整currentCObjHandle指针到初始位置，以便下一次循环
			currentCObjHandle = cObjHandleList;
			return MendTypes::MendFalse;
		}
		else {
			currentCObjHandle = currentCObjHandle->getNext();
			currentGramaEle = static_cast< struct SScriptGramaEle* >(currentCObjHandle->getPObj());
			return MendTypes::MendTrue;
		}
	}
}

// 获取下一个语法的名字
#ifdef _UNICODE
const wchar_t* CGramaHandle::getNextName() const
{
	return currentGramaEle->name;
}
#else
MendTypes::cpc8 CGramaHandle::getNextName() const
{
	return currentGramaEle->name;
}
#endif

// 获取下一个语法的ID
MendTypes::s32 CGramaHandle::getNextID() const
{
	return currentGramaEle->id;
}

// 设置最后语法的名字
#ifdef _UNICODE
void CGramaHandle::setName(const wchar_t* name)
{
	struct SScriptGramaEle* pGramaEle = static_cast< struct SScriptGramaEle* >(lastCObjHandle->getPObj());
	wcscpy(pGramaEle->name, name);
}
#else
void CGramaHandle::setName(MendTypes::cpc8 name)
{
	struct SScriptGramaEle* pGramaEle = static_cast< struct SScriptGramaEle* >(lastCObjHandle->getPObj());
	strcpy(pGramaEle->name, name);
}
#endif

// 设置最后语法的ID
void CGramaHandle::setID(MendTypes::s32 id)
{
	struct SScriptGramaEle* pGramaEle = static_cast< struct SScriptGramaEle* >(lastCObjHandle->getPObj());
	pGramaEle->id = id;
}

#ifdef _MEND_DEBUG_
#ifdef _UNICODE
const wchar_t* CGramaHandle::getName() const
{
	if (CObjHandle != NULL) {
		struct SScriptGramaEle* pGramaEle = static_cast< struct SScriptGramaEle* >(cObjHandleList->getPObj());
		return pGramaEle->name;
	}
	return NULL;
}
#else
MendTypes::cpc8 CGramaHandle::getName() const
{
	if (cObjHandleList != NULL) {
		struct SScriptGramaEle* pGramaEle = static_cast< struct SScriptGramaEle* >(cObjHandleList->getPObj());
		return pGramaEle->name;
	}
	return NULL;
}
#endif
MendTypes::s32 CGramaHandle::getID() const
{
	if (cObjHandleList != NULL) {
		struct SScriptGramaEle* pGramaEle = static_cast< struct SScriptGramaEle* >(cObjHandleList->getPObj());
		return pGramaEle->id;
	}
	return -1;
}
#endif

// 脚本语法解析器构造函数
CScriptGrama::CScriptGrama()
{
	MendTypes::s32 size = sizeof(struct SScriptGramaEle);
	// 解析语法文件，根据每个语法向内存管理器申请内存句柄
	// 将内存句柄添加到语法句柄中
	// 后面需要修改代码
	//if (MendTypes::MendTrue) {
	//	//.....
	//	m_pScriptGramaEleList.add(g_memoryManager.allocate(size));
	//}

	fstream gramaFile(SCRIPTGRAMEFILE);
	string line, grama, id;
	while (getline(gramaFile, line)) {
		if (line.c_str()[0] == ';') {
			continue;
		}
		stringstream stream(line);
		stream >> grama >> id;
		MendTypes::s32 i = atoi(id.c_str());
		m_pScriptGramaEleList.add(g_memoryManager.allocate(size));
		m_pScriptGramaEleList.setName(grama.c_str());
		m_pScriptGramaEleList.setID(i);
	}

	/*while (m_pScriptGramaEleList.hasNext()) {
		cout << m_pScriptGramaEleList.getNextName() << " " << m_pScriptGramaEleList.getNextID() << endl;
	}*/
}

// 检查是否还有下一个语法元素
MendTypes::MendBool CScriptGrama::hasNext()
{
	return m_pScriptGramaEleList.hasNext();
}

// 获取下一个语法元素的名字
#ifdef _UNICODE
const wchar_t* CScriptGrama::getNextName() const
{
	return m_pScriptGramaEleList.getNextName();
}
#else
MendTypes::cpc8 CScriptGrama::getNextName() const
{
	return m_pScriptGramaEleList.getNextName();
}
#endif

// 获取下一个语法元素的ID
MendTypes::s32 CScriptGrama::getNextID() const
{
	return m_pScriptGramaEleList.getNextID();
}

void CScriptManager::init(void)
{
	// 目前默认初始化函数体为空
	init(SCRIPTFILEPATH);
}

#ifdef _UNICODE
void CScriptManager::init(const wchar_t *scriptName)
{
	// 目前带脚本文件名初始化函数体为空
}
#else
void CScriptManager::init(MendTypes::cpc8 scriptName)
{

}
#endif

void CScriptManager::close(void)
{
	//if (NULL != m_pScriptElementList) {
	//	// 将每个脚本元素返回到内存管理器中
	//}

	//m_pScriptElement = NULL;
	//m_pScriptElementList = NULL;
}

//MendTypes::MendBool CScriptManager::hasNextStageEle(void)
//{
//	if (NULL != m_pScriptElement->pNext) {
//		m_pScriptElement = m_pScriptElement->pNext;
//		return MendTypes::MendTrue;
//	} else {
//		return MendTypes::MendFalse;
//	}
//}
//
//MendDatabase::DBELE_TYPE CScriptManager::getStageEleID(void)
//{
//	return m_pScriptElement->id;
//}
//
//const wchar_t* CScriptManager::getStageEleName(void)
//{
//	return m_pScriptElement->name;
//}
//
//const wchar_t* CScriptManager::getStageElePath(void)
//{
//	return m_pScriptElement->path;
//}
//
//MendTypes::POSITION CScriptManager::getStageElePos(void)
//{
//	return m_pScriptElement->pos;
//}
//
//MendTypes::MendBool CScriptManager::hasNextStage(void)
//{
//	MendTypes::u32 len;
//	if ((len = wcslen(m_pScriptElement->nextstage))) {
//		wchar_t nextStagePath[SCRIPTSTAGEPATH];
//		wcscpy(nextStagePath, m_pScriptElement->nextstage);
//		nextStagePath[len] = '\0';
//		this->init(nextStagePath);
//		return MendTypes::MendTrue;
//	}
//
//	return MendTypes::MendFalse;
//}
//
//MendTypes::MendBool CScriptManager::hasPrevStage(void)
//{
//	MendTypes::u32 len;
//	if ((len = wcslen(m_pScriptElement->prevStage))) {
//		wchar_t prevStagePath[SCRIPTSTAGEPATH];
//		wcsncpy(prevStagePath, m_pScriptElement->prevStage, len);
//		prevStagePath[len] = '\0';
//		this->init(prevStagePath);
//		return MendTypes::MendTrue;
//	}
//
//	return MendTypes::MendFalse;
//}

}
}