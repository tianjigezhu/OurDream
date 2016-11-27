#ifndef _MEND_CSCRIPT_H_
#define _MEND_CSCRIPT_H_

#include "MendIScript.h"

namespace Mend
{
	namespace MendScript
	{
		// 脚本管理器类
		class CScriptManager: public IScriptManager
		{
		public:
			CScriptManager() {}
			~CScriptManager() {};
			void init(void);
			void close(void);
			MendTypes::MendBool hasNextStageEle(void);
			MendDatabase::DBELE_TYPE getStageEleID(void);
			const char* getStageEleName(void);
			const char* getStageElePath(void);
			MendTypes::POSITION getStageElePos(void);
			MendTypes::MendBool hasNextStage(void);
			MendTypes::MendBool hasPrevStage(void);
		protected:
			void init(const char *scriptName);

		private:
			PSSCRIPTSTAGEELEMENT m_pScriptElementList;
			PSSCRIPTSTAGEELEMENT m_pScriptElement;
		};
	}
}

#endif