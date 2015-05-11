
#pragma once

#include "ITypeMeta.h"
#include "Sfinae.h"
#include "Singleton.h"

class ClassMetaBase : public ITypeMeta
{
    bool isPointer() override { return false; }
    bool isVector() override { return false; }
    bool isClass() override { return true; }
};

template <typename T>
class TypeMeta<T, typename enable_class<T>::type> : public ClassMetaBase, public Singleton<TypeMeta<T>>
{
public:
    Any CreateOnStack() override { return T(); }
    Any CreateOnHeap() override { return new T(); }

    virtual Any Dereferencing(Any& object) override
    {
        return *(object.as<T*>());
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return &(object.as<T>());
    }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        throw new std::exception();
    }

    template <typename... Types>
    inline static T* New(Types... args)
    {
        return new T(args...);
    }
};
