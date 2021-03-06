#version 440

struct PSInput
{
    vec4 position;
    vec2 uv;
};

layout(binding = 0, std140) uniform ConstantBuffer
{
    mat4 MVP;
} _21;

layout(location = 0) in vec3 _position;
layout(location = 1) in vec4 _uv;
layout(location = 0) out vec2 uv;

void vsmain()
{
    PSInput result;
    result.position = (_21.MVP * vec4(_position, 1.0));
    result.uv = vec2(_uv.xy);
    gl_Position = result.position;
    uv = result.uv;
}

