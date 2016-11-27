#include "MendCScript.h"

namespace Mend
{
namespace MendScript
{

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void CScriptManager::init(void)
{
	// ĿǰĬ�ϳ�ʼ��������Ϊ��
	init(SCRIPTFILEPATH);
}

void CScriptManager::init(const char *scriptName)
{
	// Ŀǰ���ű��ļ�����ʼ��������Ϊ��
}

void CScriptManager::close(void)
{
	if (NULL != m_pScriptElementList) {
		// ��ÿ���ű�Ԫ�ط��ص��ڴ��������
	}

	m_pScriptElement = NULL;
	m_pScriptElementList = NULL;
}

MendTypes::MendBool CScriptManager::hasNextStageEle(void)
{
	if (NULL != m_pScriptElement->pNext) {
		m_pScriptElement = m_pScriptElement->pNext;
		return MendTypes::MendTrue;
	} else {
		return MendTypes::MendFalse;
	}
}

MendDatabase::DBELE_TYPE CScriptManager::getStageEleID(void)
{
	return m_pScriptElement->id;
}

const char* CScriptManager::getStageEleName(void)
{
	return m_pScriptElement->name;
}

const char* CScriptManager::getStageElePath(void)
{
	return m_pScriptElement->path;
}

MendTypes::POSITION CScriptManager::getStageElePos(void)
{
	return m_pScriptElement->pos;
}

MendTypes::MendBool CScriptManager::hasNextStage(void)
{
	MendTypes::u32 len;
	if ((len = strlen(m_pScriptElement->nextStage))) {
		char nextStagePath[SCRIPTSTAGEPATH];
		strncpy(nextStagePath, m_pScriptElement->nextStage, len);
		nextStagePath[len] = '\0';
		this->init(nextStagePath);
		return MendTypes::MendTrue;
	}

	return MendTypes::MendFalse;
}

MendTypes::MendBool CScriptManager::hasPrevStage(void)
{
	MendTypes::u32 len;
	if ((len = strlen(m_pScriptElement->prevStage))) {
		char prevStagePath[SCRIPTSTAGEPATH];
		strncpy(prevStagePath, m_pScriptElement->prevStage, len);
		prevStagePath[len] = '\0';
		this->init(prevStagePath);
		return MendTypes::MendTrue;
	}

	return MendTypes::MendFalse;
}

}
}
