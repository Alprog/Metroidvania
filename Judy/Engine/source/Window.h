
#pragma once

#include "Context.h"

class Window
{
public:
    static Window* Create();

    void show();

    virtual void ProcessEvents() = 0;

    void Render();

protected:
    Context* context;

};
