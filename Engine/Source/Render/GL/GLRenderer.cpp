
#include "GLRenderer.h"

#include "Node.h"

#if WIN
    #include <windows.h>
#endif

#include "gl.h"

#include "Win/WinGLContext.h"
#include "Win/WinRenderTarget.h"

#include "../Texture.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer.h"
#include "../ConstantBuffer.h"

GLRenderer::GLRenderer()
{
    auto dummy = (GLContext*)new WinGLContext(0);
    dummy->MakeCurrent();
    glewInit();
    //delete dummy;
}

void GLRenderer::Clear(Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLContext* GLRenderer::GetContext(RenderTarget* renderTarget)
{
    auto context = (GLContext*)contexts[renderTarget];
    if (context == nullptr)
    {
        auto hWnd = ((WinRenderTarget*)renderTarget)->hWnd;
        context = (GLContext*)new WinGLContext(hWnd);
        contexts[renderTarget] = context;
    }

    context->MakeCurrent();
    glewInit();

    return context;
}

void GLRenderer::Draw(RenderCommand command)
{
    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

    glDisable(GL_CULL_FACE);

    auto renderState = command.state;

    auto mvp = renderState->constantBuffer->data.MVP;

    /*for (auto i = 0; i < mesh->vertices.size(); i++)
    {
        auto v3 = mesh->vertices[i].Position;
        auto v4 = v3 * mvp;

        printf("%i\n", v4.x);
    }*/

    GLuint location = glGetUniformLocation(renderState->programId, "MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp.m11);

    location = glGetUniformLocation(renderState->programId, "mainTexture");
    glUniform1i(location, 0);

    glActiveTexture(GL_TEXTURE0);
    GLuint id = renderState->texture->glImpl->id;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    command.mesh->vertexBuffer->glImpl->Bind();
    command.mesh->indexBuffer->glImpl->Bind();

    glUseProgram(renderState->programId);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

    glDrawElements(GL_TRIANGLES, command.mesh->indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}

void GLRenderer::Render(std::vector<RenderCommand> commands, RenderTarget* renderTarget)
{
    auto context = GetContext(renderTarget);

    context->MakeCurrent();

    auto size = renderTarget->GetSize();
    glViewport(0, 0, size.x, size.y);

    //glScissor(0, 0, 400, 800);
    //glEnable(GL_SCISSOR_TEST);

    Color color { 0.3f, 0.3f, 0.3f, 1.0f };
    Clear(color);

    for (auto& command : commands)
    {
        Draw(command);
    }

    context->Swap();
}