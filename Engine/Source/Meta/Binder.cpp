
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"

#include "App.h"

LuaBinder::LuaBinder(lua_State* L)
    : L { L }
{
}

template <typename T>
T* CheckType(lua_State* L, int n)
{
    char* name = TypeMeta<T>::Instance()->name;
    return *(T**)luaL_checkudata(L, n, name);
}

/*int SubStruct_GetE(lua_State* L)
{
    SubStruct* obj = CheckType<SubStruct>(L, 1);
    lua_pushnumber(L, obj->e);
    return 1;
}

int SubStruct_SetE(lua_State* L)
{
    SubStruct* obj = CheckType<SubStruct>(L, 1);
    int value = (int)luaL_checknumber(L, 2);
    obj->e = value;
    return 0;
}

int TestStruct_GetD(lua_State* L)
{
    TestStruct* obj = CheckType<TestStruct>(L, 1);

    auto size = sizeof(SubStruct*);
    auto udata = (SubStruct**)lua_newuserdata(L, size);
    *udata = &obj->d;

    luaL_getmetatable(L, "SubStruct");
    lua_setmetatable(L, -2);

    return 1;
}

int TestStruct_SetD(lua_State* L)
{
    TestStruct* obj = CheckType<TestStruct>(L, 1);
    auto value = *CheckType<SubStruct>(L, 2);
    obj->d = value;
    return 0;
}

template <typename ClassType, typename FieldType>
int Setter(lua_State* L)
{
    auto object = CheckType<ClassType>(L, 1);
    auto value = CheckType<FieldType>(L, 2);

    IFieldMeta* meta;
    meta->set(object, value);

    return 0;
}*/

int FunctionInvoker(lua_State* L)
{
    auto method = *(IFunctionMeta**)lua_touserdata(L, lua_upvalueindex(1));

    int index = 1;
    std::vector<Variant> args = {};
    for (auto argType : method->GetArgTypes())
    {
        if (argType == TypeMeta<int>::Instance())
        {
            args.push_back(lua_tointeger(L, index++));
        }
        else if (argType == TypeMeta<char*>::Instance())
        {
            args.push_back(lua_tostring(L, index++));
        }
        else
        {
            void* p = *(void**)lua_touserdata(L, index++);
            args.push_back(p);
        }
    }

    auto returnType = method->GetReturnType();
    if (returnType == nullptr)
    {
        method->Invoke(args);
        return 0;
    }
    else
    {
        Variant result = method->Invoke(args);
        if (returnType == TypeMeta<int>::Instance())
        {
            lua_pushinteger(L, result.as<int>());
        }
        else if (returnType == TypeMeta<char*>::Instance())
        {
            lua_pushstring(L, result.as<char*>());
        }
        else
        {
            *(void**)lua_newuserdata(L, sizeof(void*)) = result;

            printf("%s \n", returnType->name);
            fflush(stdout);

            luaL_getmetatable(L, returnType->name);
            lua_setmetatable(L, -2);
        }

        return 1;
    }
}

void LuaBinder::Bind(Meta* meta)
{
    ITypeMeta* type = TypeMeta<Node>::Instance();
    luaL_newmetatable(L, type->name);

    auto size = sizeof(void*);

    for (auto constructor : type->constructors)
    {
        int argCount = constructor->GetArgCount();
        *(IFunctionMeta**)lua_newuserdata(L, size) = constructor;
        lua_pushcclosure(L, FunctionInvoker, 1);
        std::string text = "constructor" + std::to_string(argCount);
        printf(text.c_str());
        lua_setfield(L, -2, text.c_str());
    }

    for (auto method : type->methods)
    {
        *(IFunctionMeta**)lua_newuserdata(L, size) = method;
        lua_pushcclosure(L, FunctionInvoker, 1);
        lua_setfield(L, -2, method->name);
    }

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_setglobal(L, type->name);

}
