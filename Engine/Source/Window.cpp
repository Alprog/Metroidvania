
#include "Window.h"
#include "Platforms.h"

#ifdef WIN
#include "GLRenderer.h"
#include "DXRenderer.h"
#endif

#include "Quad.h"
#include "Model.h"

WindowM* WindowM::Create()
{
    return new PlatformWindow();
}

WindowM::WindowM()
{
    auto model = new Model();

    auto c1 = new Model();
    auto c2 = new Model();

//    auto quad = new Quad();
//    quad->Size = Vector2(0.3f, 0.3f);

    scene = model;
    scene->transform.setScaling(Vector3::One * 0.3f);

    scene->AddChild(c1);
    scene->AddChild(c2);

    c1->transform.setTranslation(Vector3(2, 0, 0));
    c1->transform.setScaling(Vector3::One * 0.3f);

    c2->transform.setTranslation(Vector3(-2, 0, 0));
    c2->transform.setScaling(Vector3::One * 0.4f);
}

WindowM::~WindowM()
{
    delete scene;
}

void WindowM::Update()
{
    scene->Update(0.0);

    static float a = 0;
    a += 0.003f;
    auto rotation = Quaternion::YawPitchRoll(a / 2, a, a / 2);
    scene->transform.setRotation(rotation);

}

void WindowM::Render()
{
    renderer->Render(scene, renderTarget);
}

void WindowM::show()
{
}

