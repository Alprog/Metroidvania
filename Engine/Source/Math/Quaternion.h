
#pragma once

#define __Meta__

class __Meta__ Quaternion
{
public:
    static const Quaternion Identity;

    float x, y, z, w;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);

    static Quaternion YawPitchRoll(float yaw, float pitch, float roll);
};
