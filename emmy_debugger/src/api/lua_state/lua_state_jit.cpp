#include "emmy_debugger/api/lua_state.h"
#include "emmy_debugger/api/lua_api.h"

// Multi-state LuaJIT support.
//
// LuaJIT internal headers are intentionally not available here, so we cannot read
// G(L)->mainthread directly. Instead we exploit the fact that a LuaJIT coroutine and its
// main thread SHARE one registry (the registry is per global_State): at registration we
// stash the family's main thread into that registry under a fixed light-userdata key, and
// resolve it back from any state of the family later. This gives a stable, per-family
// identity so each independent lua_State (main VM + every worker VM) gets its own Debugger,
// while coroutines correctly resolve to their owning main thread.

// Address of this static is used as a unique, collision-free registry key.
static const char EMMY_MAIN_THREAD_KEY = 0;

void SetMainState_luaJIT(lua_State* L)
{
	// REGISTRY[&EMMY_MAIN_THREAD_KEY] = L  (L must be a main thread)
	lua_pushlightuserdata(L, (void*)&EMMY_MAIN_THREAD_KEY);
	lua_pushthread(L);
	lua_rawset(L, LUA_REGISTRYINDEX);
}

lua_State* GetMainState_luaJIT(lua_State* L)
{
	// return REGISTRY[&EMMY_MAIN_THREAD_KEY] (the family's main thread), or L if unset.
	lua_pushlightuserdata(L, (void*)&EMMY_MAIN_THREAD_KEY);
	lua_rawget(L, LUA_REGISTRYINDEX);
	lua_State* mainL = lua_tothread(L, -1);
	lua_pop(L, 1);
	return mainL ? mainL : L;
}
