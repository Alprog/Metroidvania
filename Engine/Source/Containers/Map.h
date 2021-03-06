
#pragma once

#include <unordered_map>
#include "Meta/Serializer.h"
#include "luainc.h"
#include "Attributes.h"

template <typename T1, typename T2>
class [[Meta]] Map : public std::unordered_map<T1, T2>
{
    friend class Meta;
    using base = std::unordered_map<T1, T2>;

public:
    Map() = default;

private:
    static void serialize(Map<T1, T2> map, Serializer* serializer)
    {
        auto L = serializer->getL();
        auto keyType = typeMetaOf<T1>();
        auto valueType = typeMetaOf<T2>();
        lua_newtable(L);
        for (auto& pair : map)
        {
            serialize(pair.first, keyType);
            serialize(pair.second, valueType);
            lua_settable(L, -3);
        }
    }

    static Map<T1, T2> deserialize(Serializer* serializer)
    {
        auto L = serializer->getL();
        auto keyType = typeMetaOf<T1>();
        auto valueType = typeMetaOf<T2>();

        Map<T1, T2> map;
        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            T2 value = serializer->deserialize(valueType);
            lua_pop(L, 1);
            T1 key = serializer->deserialize(keyType);
            map[key] = value;
        }

        return map;
    }
};
