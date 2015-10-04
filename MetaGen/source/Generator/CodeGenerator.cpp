
#include "CodeGenerator.h"
#include <sstream>
#include <cstdio>
#include <set>

#if WIN
    #define snprintf _snprintf
#endif

const std::string tab = "    ";
const std::string tab2 = "        ";

template <typename... ArgTypes>
std::string format(const char* format, ArgTypes... args)
{
    static int size = 1024;
    static char* buffer = new char[size];

    int n = snprintf(buffer, size, format, args...);
    if (n >= 0 && n < size)
    {
        return buffer;
    }

    return "";
}

std::string CodeGenerator::GenerateIncludes(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << std::endl;
    stream << "#include \"Meta.h\"" << std::endl;
    stream << "#include \"TypeMeta.h\"" << std::endl;
    stream << "#include \"ClassDefiner.h\"" << std::endl;

    std::set<std::string> set;
    for (auto& classInfo : classes)
    {
        auto name = classInfo.headerName;
        if (set.find(name) == set.end())
        {
            stream << "#include \"" << name << "\"" << std::endl;
            set.insert(name);
        }
    }

    stream << std::endl;

    return stream.str();
}

std::string CodeGenerator::GenerateCpp(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << GenerateIncludes(classes);

    stream << "void Meta::regClasses()" << std::endl << "{" << std::endl;

    auto first = true;
    for (auto& classInfo : classes)
    {
        if (!classInfo.isTemplate)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                stream << std::endl;
            }
            stream << Generate(classInfo);
        }
    }
    stream << "}" << std::endl;

    return stream.str();
}

std::string CodeGenerator::Generate(ClassInfo& classInfo)
{
    std::stringstream stream;

    stream << tab << "ClassDefiner<" << classInfo.name << ">" << "(this, \"" << classInfo.name << "\")" << std::endl;

    bool isAbstract = classInfo.isAbstract();

    if (!isAbstract)
    {
        for (auto& constructor : classInfo.constructors)
        {
            stream << tab2 << ".constructor";
            if (constructor.arguments.size() > 0)
            {
                stream << "<";
                auto first = true;
                for (auto& argumentInfo : constructor.arguments)
                {
                    if (!first)
                    {
                        stream << ", ";
                    }
                    stream << argumentInfo.typeInfo.name;
                    first = false;
                }
                stream << ">";
            }
            stream << "()" << std::endl;
        }
    }

    for (auto& method : classInfo.methods)
    {
        if (!method.isOperator)
        {
            auto type = method.isStatic ? "function" : "method";
            stream << tab2 << "." << type << "(\"" << method.name << "\", &" <<
                classInfo.name << "::" << method.name << ")" << std::endl;
        }
    }

    if (!isAbstract)
    {
        for (auto& field : classInfo.fields)
        {
            if (!field.isStatic)
            {
                stream << tab2 << ".field(\"" << field.name << "\", &" <<
                   classInfo.name << "::" << field.name << ")" << std::endl;
            }
        }
    }

    stream << tab << ";" << std::endl;

    return stream.str();
}


