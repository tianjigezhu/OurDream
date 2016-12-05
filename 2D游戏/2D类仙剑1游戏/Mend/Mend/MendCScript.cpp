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

// �﷨��������
// ���캯��
CGramaHandle::CGramaHandle()
{
	cObjHandleList = NULL;
	currentCObjHandle = NULL;
	currentGramaEle = NULL;
	lastCObjHandle = NULL;
}

// ����ڴ���
void CGramaHandle::add(MendMemory::CMemoryHandle * pObjHandle)
{
	// ����ӵ��ڴ�����Զ���ڵ�һ��
	// �﷨����д������ڴ����������
	// ����������һ������ڴ�������˽��ڴ���ָ�븳ֵ���ڴ�������
	if (cObjHandleList) {
		cObjHandleList->add(pObjHandle);
	} else {
		cObjHandleList = pObjHandle;
	}	
	lastCObjHandle = pObjHandle;
}

// ���ʱ������һ���﷨
MendTypes::MendBool CGramaHandle::hasNext()
{
	// ����false��������ѭ������
	// ����ǿյ��﷨�������
	if (NULL == cObjHandleList)
		return MendTypes::MendFalse;

	// �����������һ�ε��ã���ʱcurrentCObjHandle=NULL
	// ��ʱ���ڴ�������ָ�븳ֵ��currentCObjHandle�������Ӵ˴���ʼ���
	//�����Ϊ�գ������˺����Ѿ�ִ�й��ˣ����ǽ�currentCObjHandleָ����ڴ�������һ���������currentCObjHandle
	// �������ִ����ȥ��
	if (NULL == currentCObjHandle) {
		currentCObjHandle = cObjHandleList;
		currentGramaEle = static_cast< struct SScriptGramaEle* >(currentCObjHandle->getPObj());
		return MendTypes::MendTrue;
	} else {
		// ����Ѿ�ִ�е����ڴ��������ĩβ�򷵻�false
		// ����ָ����һ���ڴ���
		if (currentCObjHandle->getNext() == NULL) {
			// ����currentCObjHandleָ�뵽��ʼλ�ã��Ա���һ��ѭ��
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

// ��ȡ��һ���﷨������
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

// ��ȡ��һ���﷨��ID
MendTypes::s32 CGramaHandle::getNextID() const
{
	return currentGramaEle->id;
}

// ��������﷨������
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

// ��������﷨��ID
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

// �ű��﷨���������캯��
CScriptGrama::CScriptGrama()
{
	MendTypes::s32 size = sizeof(struct SScriptGramaEle);
	// �����﷨�ļ�������ÿ���﷨���ڴ�����������ڴ���
	// ���ڴ�����ӵ��﷨�����
	// ������Ҫ�޸Ĵ���
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

// ����Ƿ�����һ���﷨Ԫ��
MendTypes::MendBool CScriptGrama::hasNext()
{
	return m_pScriptGramaEleList.hasNext();
}

// ��ȡ��һ���﷨Ԫ�ص�����
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

// ��ȡ��һ���﷨Ԫ�ص�ID
MendTypes::s32 CScriptGrama::getNextID() const
{
	return m_pScriptGramaEleList.getNextID();
}

void CScriptManager::init(void)
{
	// ĿǰĬ�ϳ�ʼ��������Ϊ��
	init(SCRIPTFILEPATH);
}

#ifdef _UNICODE
void CScriptManager::init(const wchar_t *scriptName)
{
	// Ŀǰ���ű��ļ�����ʼ��������Ϊ��
}
#else
void CScriptManager::init(MendTypes::cpc8 scriptName)
{

}
#endif

void CScriptManager::close(void)
{
	//if (NULL != m_pScriptElementList) {
	//	// ��ÿ���ű�Ԫ�ط��ص��ڴ��������
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