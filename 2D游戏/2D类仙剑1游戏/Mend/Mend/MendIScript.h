#ifndef _MEND_ISCRIPT_H_
#define _MEND_ISCRIPT_H_

#include "defines.h"

#include "MendTypes.h"
#include "MendDB.h"

namespace Mend
{
	namespace MendScript
	{
		typedef struct SScriptStageElement SScriptStageElement;
		typedef struct SScriptStageElement* PSSCRIPTSTAGEELEMENT;

		// 脚本文件元素结构
		struct SScriptStageElement 
		{
			MendDatabase::DBELE_TYPE id;
			union
			{
				MendTypes::POSITION pos;
				wchar_t name[SCRIPTSTAGEELENAME];
				wchar_t path[SCRIPTSTAGEELEPATH];

				/*MendTypes::c8 name[SCRIPTSTAGEELENAME];
				MendTypes::c8 path[SCRIPTSTAGEELEPATH];*/
			};
			union
			{
				wchar_t prevstage[SCRIPTSTAGEPATH];
				wchar_t nextstage[SCRIPTSTAGEPATH];

				/*MendTypes::c8 prevStage[SCRIPTSTAGEPATH];
				MendTypes::c8 nextStage[SCRIPTSTAGEPATH];*/
			};
			PSSCRIPTSTAGEELEMENT pNext;
		};

		// 脚本管理器接口
		class IScriptManager
		{
		public:
			virtual ~IScriptManager()=0;
			virtual void init(void)=0;
			virtual void close(void)=0;
			virtual MendTypes::MendBool hasNextStageEle(void)=0;
			virtual MendDatabase::DBELE_TYPE getStageEleID(void)=0;
			virtual const wchar_t* getStageEleName(void)=0;
			virtual const wchar_t* getStageElePath(void)=0;
			/*virtual MendTypes::pc8 getStageEleName(void)=0;
			virtual const wchar_t* getStageElePath(void)=0;*/
			virtual MendTypes::POSITION getStageElePos(void)=0;
			virtual MendTypes::MendBool hasNextStage(void)=0;
			virtual MendTypes::MendBool hasPrevStage(void)=0;
		protected:
			virtual void init(const wchar_t *scriptName)=0;
		};
	}
}

#endif