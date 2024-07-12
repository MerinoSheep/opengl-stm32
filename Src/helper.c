#include "helper.h"
#include "dma2d.h"
#include "gl.h"
#include <math.h>
#define EPSILON 0.00001

int drawTriangle(glHandleTypeDef glHandle, vInfo v1, vInfo v2, vInfo v3)
{
    // TODO bounding box check
    Vertex3f a = (Vertex3f){v1.v.x, v1.v.y, v1.v.z};
    Vertex3f b = (Vertex3f){v2.v.x, v2.v.y, v2.v.z};
    Vertex3f c = (Vertex3f){v3.v.x, v3.v.y, v3.v.z};
    Vertex3f ab = subtractVertex3f(b, a);
    Vertex3f ac = subtractVertex3f(c, a);
    float d00 = dotProductVertex3f(ab, ab);
    float d01 = dotProductVertex3f(ab, ac);
    float d11 = dotProductVertex3f(ac, ac);
    uint32_t minX, minY;
    uint32_t maxX, maxY;
    minX = (uint32_t)fminf(fminf(a.x, b.x), c.x);
    maxX = (uint32_t)(fmaxf(fmaxf(a.x, b.x), c.x) + 1);
    minY = (uint32_t)fminf(fminf(a.y, b.y), c.y);
    maxY = (uint32_t)(fmaxf(fmaxf(a.y, b.y), c.y) + 1);
    bool isUniformColor = v1.color.color == v2.color.color && v2.color.color == v3.color.color;
    for (uint32_t x = minX; x < maxX; x++)
    {
        for (uint32_t y = minY; y < maxY; y++)
        {
            float u, v, w;
            // Cramer's rule
            Vertex3f ap = subtractVertex3f((Vertex3f){x, y, 0}, a);

            float d20 = dotProductVertex3f(ap, ab);
            float d21 = dotProductVertex3f(ap, ac);
            float denom = d00 * d11 - d01 * d01;
            v = (d11 * d20 - d01 * d21) / denom;
            w = (d00 * d21 - d01 * d20) / denom;
            u = 1.0f - v - w;

            if ((u >= 0 && v >= 0 && w >= 0) && (u <= 1 && v <= 1 && w <= 1))
            {
                if (isUniformColor)
                {
                    dma2dDrawHorizLine(v1.color.color, 1, x, y, 1, 1);
                }
                else
                {
                    ARGB color;
                    color.a = 0xFF; // TODO change later
                    color.r = (uint8_t)(u * v1.color.r + v * v2.color.r + w * v3.color.r);
                    color.g = (uint8_t)(u * v1.color.g + v * v2.color.g + w * v3.color.g);
                    color.b = (uint8_t)(u * v1.color.b + v * v2.color.b + w * v3.color.b);
                    drawPixel(x, y, color);
                    // dma2dDrawHorizLine(color.color, 1, x, y, 1, 1);
                }
            }
        }
    }

    return 0;
}
// DDA algorithm
int drawLineSloped(glHandleTypeDef glHandle,Vertex4f v1, Vertex4f v2)
{
    float x, y, x1, y1;
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float m;
    if (fabs(dx) > fabs(dy))
    {
        m = fabs(dx);
    }
    else
    {
        m = fabs(dy);
    }

    dx /= m;
    dy /= m;
    x = v1.x;
    y = v1.y;
    for (int i = 0; i < m; i++)
    {
        // TODO optimize this later
        dma2dDrawHorizLine(glHandle.color.color, 1, x, y, 1, 1);
        x += dx;
        y += dy;
    }
    return 0;
}


uint32_t getStepping(GLenum mode)
{
    uint32_t step = 0;
    switch (mode)
    {
    case GL_POINTS:
        step = 1;
        break;
    case GL_LINES:
        step = 2;
        break;
    case GL_LINE_STRIP:
        step = 1;
        break;
    case GL_LINE_LOOP:
        step = 1;
        break;
    case GL_TRIANGLES:
        step = 3;
        break;
    case GL_TRIANGLE_STRIP:
        step = 1;
        break;
    case GL_TRIANGLE_FAN:
        step = 1;
        break;
    case GL_QUADS:
        step = 4;
        break;
    case GL_QUAD_STRIP:
        step = 1;
        break;
    case GL_POLYGON:
        step = 1;
        break;
    }
    return step;
}

int drawLine(glHandleTypeDef glHandle, vInfo v1, vInfo v2)
{
    // Vertical Line
    if (floatEqual(v1.v.x, v2.v.x))
    {
        for (int i = v1.v.y; i < v2.v.y; i++)
        {
            // TODO check rule on color
            dma2dDrawHorizLine(v1.color.color, 1, v1.v.x, i, 1, 1);
        }
    }
    else if (floatEqual(v1.v.y, v2.v.y))
    {
        // horizontal line
        dma2dDrawHorizLine(v1.color.color, 1, v1.v.x, v1.v.y, v2.v.x - v1.v.x, 1);
    }
    else
    {
        drawLineSloped(glHandle,v1.v, v2.v);
    }
    return 0;
}

Vertex3f crossProduct(Vertex3f v1, Vertex3f v2)
{
    Vertex3f result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

float dotProductVertex3f(Vertex3f v1, Vertex3f v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vertex4f subtractVertex4f(Vertex4f v1, Vertex4f v2)
{
    Vertex4f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    result.w = v1.w - v2.w;
    return result;
}

// v1 - v2
Vertex3f subtractVertex3f(Vertex3f v1, Vertex3f v2)
{
    Vertex3f result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

int drawPixel(uint32_t x, uint32_t y, ARGB color)
{
    uint32_t offset = (y * 240 + x) * 4;
    *(uint32_t *)(0xD0000000 + offset) = color.color;
    return 0;
}


bool floatEqual(float a, float b)
{
    if (a == b)
    {
        return true;
    }
    return fabs(a - b) < EPSILON;
}