#ifndef _MEND_CSCRIPT_H_
#define _MEND_CSCRIPT_H_

#include "defines.h"

#include "MendIScript.h"
#include "MendTypes.h"
#include "MendCMemory.h"

namespace Mend
{
	namespace MendScript
	{
		// �﷨��
		struct SScriptGramaEle
		{
#ifdef _UNICODE
			wchar_t name[SCRIPTGRAMANAME];
#else
			MendTypes::c8 name[SCRIPTGRAMANAME];
#endif
			MendTypes::s32 id;
		};

		// �﷨��������
		class CGramaHandle
		{
		public:
			CGramaHandle();
			void add(MendMemory::CMemoryHandle * pObjHandle);
			MendTypes::MendBool hasNext();
#ifdef _UNICODE
			const wchar_t* getNextName() const;
#else
			MendTypes::cpc8 getNextName() const;
#endif
			MendTypes::s32 getNextID() const;
#ifdef _UNICODE
			void setName(const wchar_t* name);
#else
			void setName(MendTypes::cpc8 name);
#endif
			void setID(MendTypes::s32 id);


#ifdef _MEND_DEBUG_
#ifdef _UNICODE
			const wchar_t* getName() const;
#else
			MendTypes::cpc8 getName() const;
#endif
			MendTypes::s32 getID() const;
#endif

		//private:
			// �﷨�ڴ�������
			MendMemory::CMemoryHandle* cObjHandleList;
		private:
			// ��ǰ�﷨�ڴ���ָ��
			MendMemory::CMemoryHandle* currentCObjHandle;
			// �﷨����ָ��
			struct SScriptGramaEle* currentGramaEle;
			// �﷨�ڴ��������βָ��
			MendMemory::CMemoryHandle* lastCObjHandle;
		};

		// �﷨������
		class CScriptGrama
		{
		public:
			CScriptGrama();
			MendTypes::MendBool hasNext();
#ifdef _UNICODE
			const wchar_t* getNextName() const;
#else
			MendTypes::cpc8 getNextName() const;
#endif
			MendTypes::s32 getNextID() const;		
		private:	
			// �﷨���
			CGramaHandle m_pScriptGramaEleList;
		};

		// �ű���������
		class CScriptManager//: public IScriptManager
		{
		public:
			CScriptManager() {}
			~CScriptManager() {};
			void init(void);
			void close(void);
			//MendTypes::MendBool hasNextStageEle(void);
			//MendDatabase::DBELE_TYPE getStageEleID(void);
			//const wchar_t* getStageEleName(void);
			//const wchar_t* getStageElePath(void);
			///*MendTypes::cpc8 getStageEleName(void);
			//MendTypes::cpc8 getStageElePath(void);*/
			//MendTypes::POSITION getStageElePos(void);
			//MendTypes::MendBool hasNextStage(void);
			//MendTypes::MendBool hasPrevStage(void);
		protected:
#ifdef _UNICODE
			void init(const wchar_t *scriptName);
#else
			void init(MendTypes::cpc8 scriptName);
#endif // _UNICODE

		private:
			CScriptGrama m_scriptGrama;
			//PSSCRIPTSTAGEELEMENT m_pScriptElementList;
			//PSSCRIPTSTAGEELEMENT m_pScriptElement;
		};
	}
}

#endif