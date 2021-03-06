
#include "IClassMeta.h"
#include "IFieldMeta.h"
#include "PropertyMeta.h"
#include "Containers/List.h"

IClassMeta::IClassMeta()
    : hasDerives(false)
{
}

List<IFieldMeta*> IClassMeta::getFieldsWithAttribute(std::string attribute, bool includeProperties)
{
    List<IFieldMeta*> list;

    for (auto& pair : fields)
    {
        auto fieldMeta = pair.second;
        if (fieldMeta->hasAttribute(attribute))
        {
            list.push_back(fieldMeta);
        }
    }

    if (includeProperties)
    {
        for (auto& pair : properties)
        {
            auto propertyMeta = pair.second;
            if (propertyMeta->hasAttribute(attribute))
            {
                list.push_back(propertyMeta);
            }
        }
    }

    return list;
}
