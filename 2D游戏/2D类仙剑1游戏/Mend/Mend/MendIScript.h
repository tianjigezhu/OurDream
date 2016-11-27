#ifndef _MEND_ISCRIPT_H_
#define _MEND_ISCRIPT_H_

#include "engine.h"

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
				char name[SCRIPTSTAGEELENAME];
				char path[SCRIPTSTAGEELEPATH];
			};
			union
			{
				char prevStage[SCRIPTSTAGEPATH];
				char nextStage[SCRIPTSTAGEPATH];
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
			virtual const char* getStageEleName(void)=0;
			virtual const char* getStageElePath(void)=0;
			virtual MendTypes::POSITION getStageElePos(void)=0;
			virtual MendTypes::MendBool hasNextStage(void)=0;
			virtual MendTypes::MendBool hasPrevStage(void)=0;
		protected:
			virtual void init(const char *scriptName)=0;
		};
	}
}

#endif