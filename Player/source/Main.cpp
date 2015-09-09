
#include "LuaMachine/LuaMachine.h"
#include "RemoteDebbuger.h"

#include "App.h"

int main(int argc, char *argv[])
{
    auto debug = false;
    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-d" || arg == "-debug")
        {
            debug = true;
        }

    }

    auto luaMachine = LuaMachine::Instance();

    if (debug)
    {
        RemoteDebbuger::Instance()->Start(2730);
    }

    luaMachine->Start("main.lua", debug);
}

//    SubStruct s;
//    s.arr.push_back(4);
//    s.arr.push_back(8);
//    s.set.insert(3);
//    s.set.insert(7);
//    s.map["efe"] = 4;
//    s.map["efet"] = 44;
//    RemoteDebbuger::netNode = new NetNode();
//    std::string text = RemoteDebbuger::netNode->serializer->Serialize(s);
//    auto f = RemoteDebbuger::netNode->serializer->Deserialize(text);
//    text = RemoteDebbuger::netNode->serializer->Serialize(f);
//    printf("%s \n", text.c_str());
