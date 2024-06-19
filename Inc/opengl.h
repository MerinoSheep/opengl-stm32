#include <stdbool.h>
#include <stdint.h>
#define GLboolean bool
#define GLbyte int8_t
#define GLubyte uint8_t
#define GLshort int16_t
#define GLushort uint16_t
#define GLint int32_t
#define GLuint uint32_t
#define GLsizei int32_t
#define GLfloat float
#define GLdouble double

typedef enum
{
    GL_POINTS = 0, // Treats each vertex as a single point. Vertex ndefines point n. N points are drawn.
    GL_LINES,      // Treats each pair of vertices as an independent line segment. Vertices 2n-1 and 2n define line n. N/2 lines are drawn.
    GL_LINE_STRIP, // Draws a connected group of line segments from the first vertex to the last. Vertices n and n+1 define line n. N-1 lines are drawn.
    GL_LINE_LOOP,  // Draws a connected group of line segments from the first vertex to the last, then back to the first. Vertices n and n+1 define line n. The last line, however, is defined by vertices N and 1. N lines are drawn.
    GL_TRIANGLES,  // Treats each triplet of vertices as an independent triangle. Vertices 3n-2, 3n-1, and 3n define triangle n. N/3 triangles are drawn.
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_FAN,
    GL_QUADS,
    GL_QUAD_STRIP,
    GL_POLYGON,
} GLenum;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} Vertex4f;

typedef struct
{
    float x;
    float y;
    float z;
} Vertex3f;

#define MAX_VERTICES 24


void glBegin(GLenum mode);
void glEnd(void);

void glVertex2f(float x, float y);
void glVertex2i(int x, int y);

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

void glColor3f(GLfloat red, GLfloat green, GLfloat blue);
