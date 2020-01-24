#include"GarrysMod/Lua/Interface.h"
#include<stdio.h>
#include<iostream>
#include<string>
#include"stdint.h"
#ifdef DEBUG
	#include"utilities.cpp"
#endif

#ifdef _WIN32
	#include"windows_getprocaddres.cpp"
#elif
	
#endif

using namespace GarrysMod::Lua;

int VAAS_SetUpvalue(lua_State* L){
	GarrysMod::Lua::ILuaBase* LUA = L->luabase;
	LUA->SetState(L);
	const void* func = LUA->GetPointer(1);
	unsigned int index = LUA->GetNumber(2);
	unsigned int new_index = LUA->GetNumber(3);

	lua_setupvalue(L,index,new_index);
	return 2;
}

int VAAS_UpvalueID(lua_State* L){
	GarrysMod::Lua::ILuaBase* LUA = L->luabase;
	LUA->SetState(L);
	const void* func = LUA->GetPointer(1);
	unsigned int index = LUA->GetNumber(2);
	unsigned int place_holder = 0;	// placeholder until I can figure out how to properly handle lua_upvalueid

	lua_upvalueid(L,index,place_holder);
	return 1;
}

int VAAS_UpvalueJoin(lua_State* L) { //best to for sure not use this one
	GarrysMod::Lua::ILuaBase* LUA = L->luabase;
	LUA->SetState(L);
	unsigned int func1 = LUA->GetNumber(1);
	unsigned int index1 = LUA->GetNumber(2);
	unsigned int func2 = LUA->GetNumber(3);
	unsigned int index2 = LUA->GetNumber(4);

	lua_upvaluejoin(L,index1,index1,index2,index2);
	return 1;
}

int VAAS_SetLocal(lua_State* L){ //best to for sure not use this one
	GarrysMod::Lua::ILuaBase* LUA = L->luabase;
	LUA->SetState(L);
	const lua_Debug* ar = 0;
	unsigned int n = LUA->GetNumber(1);

	lua_setlocal(L,ar,n);
	return 1;
}

void VAAS_Upvalues_Init(GarrysMod::Lua::ILuaBase* LUA){
	#ifdef DEBUG
		msg("Vaas Upvalues module loaded.\n",0,255,0);
		msg("Readding functions that I need because they were fucking nuked.\n",0,255,0);
	#endif
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->GetField(-1,"debug");// Was told LUA->SetField("debug") would destroy debug library so I used GetField instead
			LUA->PushCFunction(VAAS_SetUpvalue);
			LUA->SetField(-2,"SetUpvalue");
			LUA->PushCFunction(VAAS_UpvalueID);
			LUA->SetField(-2,"UpvalueID");
			LUA->PushCFunction(VAAS_UpvalueJoin);
			LUA->SetField(-2,"UpvalueJoin");
			LUA->PushCFunction(VAAS_SetLocal);
			LUA->SetField(-2,"SetLocal");
	LUA->Pop();
}

GMOD_MODULE_OPEN(){
	VAAS_Upvalues_Init(LUA);
	return 0;
}

GMOD_MODULE_CLOSE(){
	return 0;
}
