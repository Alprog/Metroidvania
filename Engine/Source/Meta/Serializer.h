
#pragma once

#include "Any.h"
#include "ITypeMeta.h"
#include "Attributes.h"

struct lua_State;
class ITypeMeta;
class IClassMeta;

class Serializer
{
    template <typename> friend class List;
    template <typename, typename> friend class Map;
    template <typename> friend class Ref;

public:
    Serializer();
    ~Serializer();

    std::string Serialize(Any object);

    template <typename Type>
    Type Deserialize(std::string text)
    {
        ITypeMeta* typeMeta = TypeMetaOf<Type>();
        return Deserialize(text, typeMeta);
    }

    Any Deserialize(std::string text, ITypeMeta* typeMeta = nullptr);

    inline lua_State* getL() const { return L; }

private:
    void Serialize(Any object, ITypeMeta* typeMeta);
    void SerializeAsClass(Any& object, IClassMeta* type);
    void SerializeClassFields(Any& pointer, IClassMeta* classMeta);

    Any DeserializeUnknown();
    Any DeserializeUnknownTable();
    Any DeserializeAsClass(IClassMeta* classMeta);
    void DeserializeClassFields(Any& pointer, IClassMeta* classMeta);
    Any Deserialize(ITypeMeta* const typeMeta);

    lua_State* L;
};
