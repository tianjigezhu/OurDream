//#include "engine.h"

#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include "engine.h"

Mend::MendScript::CScriptGrama* scriptGrama;

//class Hello
//{
//public:
//	Hello() {}
//	//Mend::MendTypes::pc8 getName() { return name; }
//	wchar_t* getName() { return name; }
//	//void setName(Mend::MendTypes::pc8 name, Mend::MendTypes::s32 len);
//	void setName(wchar_t* name, Mend::MendTypes::s32 len);
//	Mend::MendTypes::s32 getID() { return id; }
//	void setID(Mend::MendTypes::s32 id) { this->id = id; }
//
//private:
//	//Mend::MendTypes::c8 name[20];
//	wchar_t name[20];
//	Mend::MendTypes::s32 id;
//};
//
//class Object
//{
//public:
//	Object() { id = 20; }
//	const wchar_t* getName() const { return name; }
//	void setName(const wchar_t* name) 
//	{
//		wcscpy(this->name, name);
//	}
//private:
//	wchar_t name[20];
//	int id;
//};
//
//class CObjectHandle1
//{
//public:
//	Object* operator->();
//	friend class World;
//private:
//	Mend::MendMemory::CObjHandle* cObjHandle;
//};
//
//Object* CObjectHandle1::operator->()
//{
//	return (static_cast<Object*> (cObjHandle->getPObj()));
//}
//
//class World
//{
//public:
//	static void getObjectHand(int count, CObjectHandle1& handle);
//};
//
//void World::getObjectHand(int count, CObjectHandle1& handle)
//{
//	handle.cObjHandle = g_memoryManager.allocate(sizeof(Object));
//}
//
////void Hello::setName(Mend::MendTypes::pc8 name, Mend::MendTypes::s32 len)
////{
////	strncpy(this->name, name, len);
////}
//
//void Hello::setName(wchar_t* name, Mend::MendTypes::s32 len)
//{
//	wcscpy(this->name, name);
//}
//
//class A
//{
//public:
//	virtual void a() {}
//};
//
//class B
//{
//public:
//	void setName(wchar_t *name);
//	wchar_t name[20];
//	int id;
//};
//
//void B::setName(wchar_t* name)
//{
//	wcscpy(this->name, name);
//}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//{
//	//MessageBox(NULL, TEXT("Hello Mend"), TEXT("���ǵ���Ϸ����"), MB_OK);
//	g_memoryManager.init();
//	scriptGrama = new Mend::MendScript::CScriptGrama();
//	/*CObjectHandle1 handle;
//	World::getObjectHand(sizeof(Object), handle);
//	wchar_t a[10] = L"0";
//	wsprintf(a, L"%d", sizeof(Object));
//	void *ptr = (void *)malloc(100);
//	B* b = static_cast<B*>(ptr);
//	wsprintf(a, L"%s", L"����С��");
//	b->setName(a);
//	handle->setName(L"����С��");*/
//	/*Object* pObjecta = new Object[10];
//	Mend::MendMemory::CObjHandle* pObjHandle = memoryManager.allocate(sizeof(Hello));
//	Hello* pHello = static_cast<Hello*>(pObjHandle->getPObj());
//	wchar_t* name = L"��ѿ�";
//	pHello->setName(name, wcslen(name));
//	pHello->setID(10);
//	MessageBox(NULL, pHello->getName(), TEXT("�ҵ�����"), MB_OK);*/
//	//MessageBox(NULL, b->name, TEXT("�ҵ�����"), MB_OK);
//	//MessageBox(NULL, handle->getName(), TEXT("��С���ʲô"), MB_OK);
//	return 0;
//}

int main()
{
	g_memoryManager.init();
	scriptGrama = new Mend::MendScript::CScriptGrama();
}