
#include "Meta.h"

#include "MetaDefiner.h"

#include "App.h"

Meta::Meta()
{
    MetaDefiner<TestStruct>()
        .field("a", &TestStruct::a)
        .field("b", &TestStruct::b)
        .field("c", &TestStruct::c)
        .field("d", &TestStruct::d);

    MetaDefiner<SubStruct>()
        .field("e", &SubStruct::e);
}

