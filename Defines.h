#pragma once

#define GNERATE_SINGLE(classname)											\
private:																	\
	classname() {};															\
public:																		\
	static classname* GetInstance()											\
	{																		\
		if (s_instance == nullptr) s_instance = new classname();			\
		return s_instance;													\
	}																		\
private:																	\
	static classname* s_instance;											\


#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}							

#define GS(classname) GET_SINGLE(classname)


#define DIR_UP Dir::DIR_TYPE_UP
#define DIR_DOWN Dir::DIR_TYPE_DOWN
#define DIR_LEFT Dir::DIR_TYPE_LEFT
#define DIR_RIGHT Dir::DIR_TYPE_RIGHT


#define IDLE ObjectState::OBJECT_STATE_TYPE_IDLE
#define MOVE ObjectState::OBJECT_STATE_TYPE_MOVE
#define SKILL ObjectState::OBJECT_STATE_TYPE_SKILL
