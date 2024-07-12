#pragma once

#include "vertex.h"
#include <stdint.h>
#include <stdbool.h>
#include "gl.h"
typedef union
{
    uint32_t color;
    struct
    {
        // Recall how C stores data in memory
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    };
} ARGB;

typedef struct
{
    Vertex4f v;
    ARGB color;
} vInfo;

typedef struct
{
    GLenum mode;
    uint32_t count;
    uint32_t width;
    uint32_t height;
    ARGB color;

} glHandleTypeDef;

int drawTriangle(glHandleTypeDef glHandle, vInfo v1, vInfo v2, vInfo v3);

int drawLineSloped(glHandleTypeDef glHandle, Vertex4f v1, Vertex4f v2);

uint32_t getStepping(GLenum mode);

int drawLine(glHandleTypeDef glHandle, vInfo v1, vInfo v2);

Vertex3f subtractVertex3f(Vertex3f v1, Vertex3f v2);

bool floatEqual(float a, float b);

float dotProductVertex3f(Vertex3f v1, Vertex3f v2);

int drawPixel(uint32_t x, uint32_t y, ARGB color);
