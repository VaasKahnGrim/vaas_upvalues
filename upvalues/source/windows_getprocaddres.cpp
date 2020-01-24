#include"GarrysMod/Lua/Interface.h"

#ifdef _WIN32
	#include<windows.h>
	#include<libloaderapi.h>
#endif

typedef struct lua_Debug{ // Yanked from lua.org, their doccumentation is shit. if this causes issues, comment it out and comment out anything related to set_local
	int event;
	const char* name;
	const char* namewhat;
	const char* what;
	const char* source;
	int currentline;
	int linedefined;
	int lastlinedefined;
	unsigned char nups;
	unsigned char nparams;
	char isvararg;
	char istailcall;
}lua_Debug;

typedef void* (*set_upvalue)(lua_State* L,int funcinedx,int n);
static set_upvalue lua_setupvalue = (set_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"),"lua_setupvalue");;

typedef void* (*id_upvalue)(lua_State* L,int funcinedx,int n);
static id_upvalue lua_upvalueid = (id_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"),"lua_upvalueid");

typedef void* (*join_upvalue)(lua_State* L,int funcinedx1,int n1,int funcinedx2,int n2);
static join_upvalue lua_upvaluejoin = (join_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"),"lua_upvaluejoin");

typedef void* (*set_local)(lua_State* L,const lua_Debug* ar,int n);
static set_local lua_setlocal = (set_local)GetProcAddress(GetModuleHandleA("lua_shared"),"lua_setlocal");


