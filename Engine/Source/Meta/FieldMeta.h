
#pragma once

#include <string>
#include "Variant.h"
#include "Serializer.h"

class Serializer;
class ITypeMeta;

class IFieldMeta
{
public:
    virtual void set(Variant object, Variant value) = 0;
    virtual void set(void* object, Variant value) = 0;

    virtual void set(void* object, void* value) = 0;
    virtual void* get(void* object) = 0;
    virtual ITypeMeta* GetType() = 0;
    char* name;
};

template <typename ClassType, typename FieldType>
class FieldMeta : public IFieldMeta
{
public:
    virtual ITypeMeta* GetType() override
    {
        return (ITypeMeta*)TypeMeta<FieldType>::Instance();
    }

    FieldMeta(char* name, FieldType ClassType::*pointer)
    {
        this->name = name;
        this->pointer = pointer;
    }

    virtual void set(Variant object, Variant value) override
    {
        (ClassType)object.*pointer = value;
    }

    virtual void set(void* object, Variant value) override
    {
        (ClassType*)object->*pointer = value;
    }

    virtual void set(void* object, void* value) override
    {
        (ClassType*)object->*pointer = *(FieldType*)value;
    }

    virtual void* get(void* object) override
    {
        return &((ClassType*)object->*pointer);
    }

    FieldType ClassType::*pointer;
};