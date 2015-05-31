
#pragma once

#include <string>
#include "Singleton.h"
#include <thread>
#include <atomic>

class lua_State;
class lua_Debug;

class LuaMachine : public Singleton<LuaMachine>
{
    friend class Singleton<LuaMachine>;
    friend void hook(lua_State *L, lua_Debug *ar);

private:
    LuaMachine();
    ~LuaMachine();

public:
   bool IsStarted() const;

   void Start(std::string scriptName);
   void Continue();
   void Stop();

private:
   void Hook(lua_State *L, lua_Debug *ar);
   void Execution(std::string scriptName);

private:
   lua_State* L;
   std::thread* executionThread;
   std::atomic_bool	breakpoint;
};
