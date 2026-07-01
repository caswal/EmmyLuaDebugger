
#include <vector>
typedef struct lua_State lua_State;

std::vector<lua_State*> FindAllCoroutine(lua_State* L);

std::vector<lua_State*> FindAllCoroutine_lua51(lua_State* L);

std::vector<lua_State*> FindAllCoroutine_lua52(lua_State* L);

std::vector<lua_State*> FindAllCoroutine_lua53(lua_State* L);

std::vector<lua_State*> FindAllCoroutine_lua54(lua_State* L);

std::vector<lua_State*> FindAllCoroutine_lua55(lua_State* L);

// std::vector<lua_State*> FindAllCoroutine_luaJIT(lua_State* L);

lua_State* GetMainState(lua_State* L);

lua_State* GetMainState_lua54(lua_State* L);

lua_State* GetMainState_lua53(lua_State* L);

lua_State* GetMainState_lua52(lua_State* L);

lua_State* GetMainState_lua51(lua_State* L);

lua_State* GetMainState_lua55(lua_State* L);

lua_State* GetMainState_luaJIT(lua_State* L);

// Multi-state LuaJIT support: record L as its family's main thread in that family's registry,
// so GetMainState_luaJIT can later resolve any coroutine of the family back to this main thread.
// Must be called from the main thread of each independent lua_State (lua_pushthread(L)==1).
void SetMainState_luaJIT(lua_State* L);
