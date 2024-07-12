#include <math.h>
#include <string.h>
#include "gl.h"
#include "vertex.h"
#include "helper.h"
#include "dma2d.h"
#include <math.h>
int counter = 0; // temporary counter







glHandleTypeDef glHandle;
vInfo vertices[MAX_VERTICES];




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
            drawLine(glHandle,vertices[i], vertices[i + 1]);
        }
        break;
    case GL_LINE_STRIP:
        // Stepping is different on this which seperates it from
        for (int i = 0; i < counter; i += step)
        {
            drawLine(glHandle,vertices[i], vertices[i + 1]);
        }
        break;
    case GL_LINE_LOOP:
        for (int i = 0; i < counter; i += step)
        {
            drawLine(glHandle,vertices[i], vertices[i + 1]);
        }
        drawLine(glHandle,vertices[counter - 1], vertices[0]);
        break;
    case GL_TRIANGLES:
        for (int i = 0; i < counter; i += step){
        drawTriangle(glHandle,vertices[i], vertices[i + 1], vertices[i + 2]);
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


