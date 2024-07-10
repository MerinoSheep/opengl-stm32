#include <math.h>
#include <string.h>
#include "gl.h"
#include "vertex.h"
#include "dma2d.h"

#define EPSILON 0.00001

int counter = 0; // temporary counter

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
    GLenum mode;
    uint32_t count;
    uint32_t width;
    uint32_t height;
    ARGB color;

} glHandleTypeDef;

typedef struct
{
    Vertex4f v;
    ARGB color;
} vInfo;

glHandleTypeDef glHandle;
vInfo vertices[MAX_VERTICES];

int drawLine(vInfo v1, vInfo v2);
int drawTriangle(vInfo v1, vInfo v2, vInfo v3);
int drawLineSloped(Vertex4f v1, Vertex4f v2);
void glVertex4f(float x, float y, float z, float w);

uint32_t getStepping(GLenum mode);

bool floatEqual(float a, float b)
{
    if (a == b)
    {
        return true;
    }
    return fabs(a - b) < EPSILON;
}

void glBegin(GLenum mode)
{
    // Resetting counter here might not be a good idea
    counter = 0;
    glHandle.mode = mode;
}

void glEnd(void)
{
    GLenum mode = glHandle.mode;
    uint32_t step = getStepping(mode);
    switch (mode)
    {
    case GL_POINTS:
        break;
    case GL_LINES:
        for (int i = 0; i < counter; i += step)
        {
            drawLine(vertices[i], vertices[i + 1]);
        }
        break;
    case GL_LINE_STRIP:
        // Stepping is different on this which seperates it from
        for (int i = 0; i < counter; i += step)
        {
            drawLine(vertices[i], vertices[i + 1]);
        }
        break;
    case GL_LINE_LOOP:
        for (int i = 0; i < counter; i += step)
        {
            drawLine(vertices[i], vertices[i + 1]);
        }
        drawLine(vertices[counter - 1], vertices[0]);
        break;
    case GL_TRIANGLES:
        for (int i = 0; i < counter; i += step){
        drawTriangle(vertices[i], vertices[i + 1], vertices[i + 2]);
        }
        break;
    case GL_TRIANGLE_STRIP:
        break;
    case GL_TRIANGLE_FAN:
        break;
    case GL_QUADS:
        for (int i = 0; i < counter; i += step)
        {
        }
        break;
    case GL_QUAD_STRIP:
        break;
    case GL_POLYGON:
        break;
    }
}

void glVertex2f(float x, float y)
{
    glVertex4f(x, y, 0.0, 1.0);
}

void glVertex2i(GLint x, GLint y)
{
    glVertex4f((float)x, (float)y, 0.0, 1.0);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glHandle.width = width;
    glHandle.height = height;
}

void glColor3s(GLshort red, GLshort green, GLshort blue)
{
    glColor3i((GLint)red, (GLint)green, (GLint)blue);
}

void glColor3i(GLint red, GLint green, GLint blue)
{
    glHandle.color.a = 0xFF;
    glHandle.color.r = (uint8_t)red;
    glHandle.color.g = (uint8_t)green;
    glHandle.color.b = (uint8_t)blue;
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
    glHandle.color.a = 0xFF;
    glHandle.color.r = (uint8_t)(red * 255);
    glHandle.color.g = (uint8_t)(green * 255);
    glHandle.color.b = (uint8_t)(blue * 255);
}

void glVertex4f(float x, float y, float z, float w)
{
    vertices[counter].v.x = x;
    vertices[counter].v.y = y;
    vertices[counter].v.z = z;
    vertices[counter].v.w = w;
    vertices[counter].color = glHandle.color;
    counter++;
}

// Helper functions, probably move into another file later
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

int drawLine(vInfo v1, vInfo v2)
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
        drawLineSloped(v1.v, v2.v);
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

int drawTriangle(vInfo v1, vInfo v2, vInfo v3)
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
int drawLineSloped(Vertex4f v1, Vertex4f v2)
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
