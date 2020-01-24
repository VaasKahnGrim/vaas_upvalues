#include "GarrysMod/Lua/Interface.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "stdint.h"
#include "utilities.cpp"

#ifdef _WIN32
	#include <windows.h>
	#include <libloaderapi.h>
#endif
using namespace GarrysMod::Lua;

typedef void* (*set_upvalue)(lua_State* L,int funcinedx,int n);
static set_upvalue lua_setupvalue = (set_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"), "lua_setupvalue");;

typedef void* (*id_upvalue)(lua_State* L,int funcinedx,int n);
static id_upvalue lua_upvalueid = (id_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"), "lua_upvalueid");

// for some reason this shit keeps thinking a ; is missing even tho "ApPaReNtLy" its being used correctly....wtf???
//void* lua_setupvalue = (set_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"),"lua_setupvalue");
//void* lua_upvalueid = (id_upvalue)GetProcAddress(GetModuleHandleA("lua_shared"),"lua_upvalueid");

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

void VAAS_Upvalues_Init(GarrysMod::Lua::ILuaBase* LUA){
	printMessage(LUA,"Vaas Upvalues module loaded.\n",0,255,0);
	printMessage(LUA,"Readding functions that I need because they were fucking nuked.\n",0,255,0);
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->CreateTable();
			LUA->PushCFunction(VAAS_SetUpvalue);
			LUA->SetField(-2,"SetUpvalue");
			LUA->PushCFunction(VAAS_UpvalueID);
			LUA->SetField(-2,"UpvalueID");
		LUA->SetField(-2,"debug");
	LUA->Pop();
}

GMOD_MODULE_OPEN(){
	VAAS_Upvalues_Init(LUA);
	return 0;
}

GMOD_MODULE_CLOSE(){
	return 0;
}
