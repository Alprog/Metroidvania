
#include "LuaMachine.h"
#include <iostream>

#include "Meta/Meta.h"
#include "Meta/Binder.h"
#include "Source/luainc.h"

int const maxStackSize = 256;

LuaMachine::LuaMachine()
    : L{nullptr}
    , isStartedFlag{false}
    , breakCallback{nullptr}
    , resumeCallback{nullptr}
    , level{0}
    , breakRequiredLevel{0}
{
    L = luaL_newstate();
    luaL_openlibs(L);

    // search path for required scripts
    lua_getglobal(L, "package");
    lua_pushstring(L, "?.lua");
    lua_setfield(L, -2, "path");
    lua_pop(L, 1);

    // userdata storage (prevent gc)
    lua_newtable(L);
    lua_setfield(L, LUA_REGISTRYINDEX, "UDATA");

    binder = new LuaBinder(L);
    LuaBinder(L).bind(Meta::getInstance());
}

LuaMachine::~LuaMachine()
{
    if (binder != nullptr)
    {
        delete binder;
        binder = nullptr;
    }

    if (L != nullptr)
    {
        lua_close(L);
        L = nullptr;
    }
}

bool LuaMachine::isStarted() const
{
    return isStartedFlag;
}

bool LuaMachine::isBreaked() const
{
    return isStartedFlag && isSuspended;
}

void hookHelper(lua_State *L, lua_Debug *ar)
{
    LuaMachine::getInstance()->hook(ar);
}

void LuaMachine::hook(lua_Debug *ar)
{
    if (ar->event == LUA_HOOKCALL)
    {
        level++;
    }
    else if (ar->event == LUA_HOOKRET)
    {
        level--;
    }
    else
    {
        if (level <= breakRequiredLevel)
        {
            onBreak(ar);
        }
        else
        {
            if (breakpoints.isAnySet(ar->currentline))
            {
                lua_getinfo(L, "S", ar);
                if (breakpoints.isSet(ar->source, ar->currentline))
                {
                    onBreak(ar);
                }
            }
        }
    }
}

void LuaMachine::onBreak(lua_Debug *ar)
{
    breakRequiredLevel = 0;

    stack.calls.clear();

    auto index = 0;
    while (lua_getstack(L, index, ar))
    {
        lua_getinfo(L, "nSl", ar);
        stack.calls.push_back(getCallInfo(ar));
        index++;
    }

    if (breakCallback) breakCallback();

    suspendExecution();

    if (resumeCallback) resumeCallback();
}

CallInfo LuaMachine::getCallInfo(lua_Debug *ar)
{
    auto name = ar->name ? ar->name : "";
    auto source = ar->source ? ar->source : "";
    auto line = ar->currentline;
    auto startLine = ar->linedefined;
    auto endLine = ar->lastlinedefined;
    return CallInfo(name, source, line, startLine, endLine);
}

void LuaMachine::suspendExecution()
{
    isSuspended = true;
    while (isSuspended)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void LuaMachine::execute(std::string scriptName, bool debug)
{
    isStartedFlag = true;

    if (debug)
    {
        int mask = LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE;
        lua_sethook(L, hookHelper, mask, 0);
        suspendExecution();
    }

    if (luaL_dofile(L, scriptName.c_str()))
    {
        isStartedFlag = false;
        printf("Something went wrong loading the chunk (syntax error?)\n");
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    isStartedFlag = false;
}

void LuaMachine::pause()
{
    if (!isSuspended)
    {
        breakRequiredLevel = maxStackSize;
    }
}

void LuaMachine::resume()
{
    if (isSuspended)
    {
        isSuspended = false;
    }
}

void LuaMachine::stepInto()
{
    if (isSuspended)
    {
        breakRequiredLevel = maxStackSize;
        isSuspended = false;
    }
}

void LuaMachine::stepOver()
{
    if (isSuspended)
    {
        breakRequiredLevel = level;
        isSuspended = false;
    }
}

void LuaMachine::stepOut()
{
    if (isSuspended)
    {
        breakRequiredLevel = level - 1;
        isSuspended = false;
    }
}

void stopHook(lua_State *L, lua_Debug *ar)
{
    luaL_error(L, "Stop execution");
}

void LuaMachine::stop()
{
    if (isSuspended)
    {
        isSuspended = false;
        lua_sethook(L, stopHook, LUA_MASKCOUNT, 1);
    }
}

void LuaMachine::retainUserdata(void* userdata)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "UDATA"); // T
    lua_pushuserdata(L, userdata); // TK
    lua_pushboolean(L, true); // TKV
    lua_rawset(L, -3); // T
    lua_pop(L, 1); //
}

void LuaMachine::releaseUserdata(void* userdata)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "UDATA"); // T
    lua_pushuserdata(L, userdata); // TK
    lua_pushnil(L); // TKV
    lua_rawset(L, -3); // T
    lua_pop(L, 1); //
}
