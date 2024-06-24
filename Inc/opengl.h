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


void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

void glColor3f(GLfloat red, GLfloat green, GLfloat blue);

/* Immediate Mode*/
void glArrayElement(GLint);
void glBegin(GLenum mode);

void glColor3b(GLbyte red,
               GLbyte green,
               GLbyte blue);
void glColor3s(GLshort red,
               GLshort green,
               GLshort blue);
void glColor3i(GLint red,
               GLint green,
               GLint blue);
void glColor3f(GLfloat red,
               GLfloat green,
               GLfloat blue);
void glColor3d(GLdouble red,
               GLdouble green,
               GLdouble blue);
void glColor3ub(GLubyte red,
                GLubyte green,
                GLubyte blue);
void glColor3us(GLushort red,
                GLushort green,
                GLushort blue);
void glColor3ui(GLuint red,
                GLuint green,
                GLuint blue);
void glColor4b(GLbyte red,
               GLbyte green,
               GLbyte blue,
               GLbyte alpha);
void glColor4s(GLshort red,
               GLshort green,
               GLshort blue,
               GLshort alpha);
void glColor4i(GLint red,
               GLint green,
               GLint blue,
               GLint alpha);
void glColor4f(GLfloat red,
               GLfloat green,
               GLfloat blue,
               GLfloat alpha);
void glColor4d(GLdouble red,
               GLdouble green,
               GLdouble blue,
               GLdouble alpha);
void glColor4ub(GLubyte red,
                GLubyte green,
                GLubyte blue,
                GLubyte alpha);
void glColor4us(GLushort red,
                GLushort green,
                GLushort blue,
                GLushort alpha);
void glColor4ui(GLuint red,
                GLuint green,
                GLuint blue,
                GLuint alpha);
void glColor3bv(const GLbyte *v);
void glColor3sv(const GLshort *v);
void glColor3iv(const GLint *v);
void glColor3fv(const GLfloat *v);
void glColor3dv(const GLdouble *v);
void glColor3ubv(const GLubyte *v);
void glColor3usv(const GLushort *v);
void glColor3uiv(const GLuint *v);
void glColor4bv(const GLbyte *v);
void glColor4sv(const GLshort *v);
void glColor4iv(const GLint *v);
void glColor4fv(const GLfloat *v);
void glColor4dv(const GLdouble *v);
void glColor4ubv(const GLubyte *v);
void glColor4usv(const GLushort *v);
void glColor4uiv(const GLuint *v);

void glEnd(void);

void glEvalCoord1f(GLfloat u);
void glEvalCoord1d(GLdouble u);
void glEvalCoord2f(GLfloat u,
                   GLfloat v);
void glEvalCoord2d(GLdouble u,
                   GLdouble v);
void glEvalCoord1fv(const GLfloat *u);
void glEvalCoord1dv(const GLdouble *u);
void glEvalCoord2fv(const GLfloat *u);
void glEvalCoord2dv(const GLdouble *u);

void glEvalMesh1(GLenum mode,
                 GLint i1,
                 GLint i2);
void glEvalMesh2(GLenum mode,
                 GLint i1,
                 GLint i2,
                 GLint j1,
                 GLint j2);

void glEvalPoint1(GLint i);
void glEvalPoint2(GLint i,
                  GLint j);
void glFogCoordd(GLdouble coord);
void glFogCoordf(GLfloat coord);

void glIndexs(GLshort c);
void glIndexi(GLint c);
void glIndexf(GLfloat c);
void glIndexd(GLdouble c);
void glIndexub(GLubyte c);

void glIndexsv(const GLshort *c);
void glIndexiv(const GLint *c);
void glIndexfv(const GLfloat *c);
void glIndexdv(const GLdouble *c);
void glIndexubv(const GLubyte *c);

void glMaterialf(GLenum face,
                 GLenum pname,
                 GLfloat param);
void glMateriali(GLenum face,
                 GLenum pname,
                 GLint param);

void glMaterialfv(GLenum face,
                  GLenum pname,
                  const GLfloat *params);
void glMaterialiv(GLenum face,
                  GLenum pname,
                  const GLint *params);

void glMultiTexCoord1s(GLenum target,
                       GLshort s);
void glMultiTexCoord1i(GLenum target,
                       GLint s);
void glMultiTexCoord1f(GLenum target,
                       GLfloat s);
void glMultiTexCoord1d(GLenum target,
                       GLdouble s);
void glMultiTexCoord2s(GLenum target,
                       GLshort s,
                       GLshort t);
void glMultiTexCoord2i(GLenum target,
                       GLint s,
                       GLint t);
void glMultiTexCoord2f(GLenum target,
                       GLfloat s,
                       GLfloat t);
void glMultiTexCoord2d(GLenum target,
                       GLdouble s,
                       GLdouble t);
void glMultiTexCoord3s(GLenum target,
                       GLshort s,
                       GLshort t,
                       GLshort r);
void glMultiTexCoord3i(GLenum target,
                       GLint s,
                       GLint t,
                       GLint r);
void glMultiTexCoord3f(GLenum target,
                       GLfloat s,
                       GLfloat t,
                       GLfloat r);
void glMultiTexCoord3d(GLenum target,
                       GLdouble s,
                       GLdouble t,
                       GLdouble r);
void glMultiTexCoord4s(GLenum target,
                       GLshort s,
                       GLshort t,
                       GLshort r,
                       GLshort q);
void glMultiTexCoord4i(GLenum target,
                       GLint s,
                       GLint t,
                       GLint r,
                       GLint q);
void glMultiTexCoord4f(GLenum target,
                       GLfloat s,
                       GLfloat t,
                       GLfloat r,
                       GLfloat q);
void glMultiTexCoord4d(GLenum target,
                       GLdouble s,
                       GLdouble t,
                       GLdouble r,
                       GLdouble q);

void glMultiTexCoord1sv(GLenum target,
                        const GLshort *v);
void glMultiTexCoord1iv(GLenum target,
                        const GLint *v);
void glMultiTexCoord1fv(GLenum target,
                        const GLfloat *v);
void glMultiTexCoord1dv(GLenum target,
                        const GLdouble *v);
void glMultiTexCoord2sv(GLenum target,
                        const GLshort *v);
void glMultiTexCoord2iv(GLenum target,
                        const GLint *v);
void glMultiTexCoord2fv(GLenum target,
                        const GLfloat *v);
void glMultiTexCoord2dv(GLenum target,
                        const GLdouble *v);
void glMultiTexCoord3sv(GLenum target,
                        const GLshort *v);
void glMultiTexCoord3iv(GLenum target,
                        const GLint *v);
void glMultiTexCoord3fv(GLenum target,
                        const GLfloat *v);
void glMultiTexCoord3dv(GLenum target,
                        const GLdouble *v);
void glMultiTexCoord4sv(GLenum target,
                        const GLshort *v);
void glMultiTexCoord4iv(GLenum target,
                        const GLint *v);
void glMultiTexCoord4fv(GLenum target,
                        const GLfloat *v);
void glMultiTexCoord4dv(GLenum target,
                        const GLdouble *v);

void glNormal3b(GLbyte nx,
                GLbyte ny,
                GLbyte nz);
void glNormal3d(GLdouble nx,
                GLdouble ny,
                GLdouble nz);
void glNormal3f(GLfloat nx,
                GLfloat ny,
                GLfloat nz);
void glNormal3i(GLint nx,
                GLint ny,
                GLint nz);
void glNormal3s(GLshort nx,
                GLshort ny,
                GLshort nz);

void glNormal3bv(const GLbyte *v);
void glNormal3dv(const GLdouble *v);
void glNormal3fv(const GLfloat *v);
void glNormal3iv(const GLint *v);
void glNormal3sv(const GLshort *v);

void glSecondaryColor3b(GLbyte red,
                        GLbyte green,
                        GLbyte blue);
void glSecondaryColor3s(GLshort red,
                        GLshort green,
                        GLshort blue);
void glSecondaryColor3i(GLint red,
                        GLint green,
                        GLint blue);
void glSecondaryColor3f(GLfloat red,
                        GLfloat green,
                        GLfloat blue);
void glSecondaryColor3d(GLdouble red,
                        GLdouble green,
                        GLdouble blue);
void glSecondaryColor3ub(GLubyte red,
                         GLubyte green,
                         GLubyte blue);
void glSecondaryColor3us(GLushort red,
                         GLushort green,
                         GLushort blue);
void glSecondaryColor3ui(GLuint red,
                         GLuint green,
                         GLuint blue);

void glSecondaryColor3bv(const GLbyte *v);
void glSecondaryColor3sv(const GLshort *v);
void glSecondaryColor3iv(const GLint *v);
void glSecondaryColor3fv(const GLfloat *v);
void glSecondaryColor3dv(const GLdouble *v);
void glSecondaryColor3ubv(const GLubyte *v);
void glSecondaryColor3usv(const GLushort *v);
void glSecondaryColor3uiv(const GLuint *v);

void glTexCoord1s(GLshort s);
void glTexCoord1i(GLint s);
void glTexCoord1f(GLfloat s);
void glTexCoord1d(GLdouble s);
void glTexCoord2s(GLshort s,
                  GLshort t);
void glTexCoord2i(GLint s,
                  GLint t);
void glTexCoord2f(GLfloat s,
                  GLfloat t);
void glTexCoord2d(GLdouble s,
                  GLdouble t);
void glTexCoord3s(GLshort s,
                  GLshort t,
                  GLshort r);
void glTexCoord3i(GLint s,
                  GLint t,
                  GLint r);
void glTexCoord3f(GLfloat s,
                  GLfloat t,
                  GLfloat r);
void glTexCoord3d(GLdouble s,
                  GLdouble t,
                  GLdouble r);
void glTexCoord4s(GLshort s,
                  GLshort t,
                  GLshort r,
                  GLshort q);
void glTexCoord4i(GLint s,
                  GLint t,
                  GLint r,
                  GLint q);
void glTexCoord4f(GLfloat s,
                  GLfloat t,
                  GLfloat r,
                  GLfloat q);
void glTexCoord4d(GLdouble s,
                  GLdouble t,
                  GLdouble r,
                  GLdouble q);

void glTexCoord1sv(const GLshort *v);
void glTexCoord1iv(const GLint *v);
void glTexCoord1fv(const GLfloat *v);
void glTexCoord1dv(const GLdouble *v);
void glTexCoord2sv(const GLshort *v);
void glTexCoord2iv(const GLint *v);
void glTexCoord2fv(const GLfloat *v);
void glTexCoord2dv(const GLdouble *v);
void glTexCoord3sv(const GLshort *v);
void glTexCoord3iv(const GLint *v);
void glTexCoord3fv(const GLfloat *v);
void glTexCoord3dv(const GLdouble *v);
void glTexCoord4sv(const GLshort *v);
void glTexCoord4iv(const GLint *v);
void glTexCoord4fv(const GLfloat *v);
void glTexCoord4dv(const GLdouble *v);

void glVertex2s(GLshort x,
                GLshort y);
void glVertex2i(GLint x,
                GLint y);
void glVertex2f(GLfloat x,
                GLfloat y);
void glVertex2d(GLdouble x,
                GLdouble y);
void glVertex3s(GLshort x,
                GLshort y,
                GLshort z);
void glVertex3i(GLint x,
                GLint y,
                GLint z);
void glVertex3f(GLfloat x,
                GLfloat y,
                GLfloat z);
void glVertex3d(GLdouble x,
                GLdouble y,
                GLdouble z);
void glVertex4s(GLshort x,
                GLshort y,
                GLshort z,
                GLshort w);
void glVertex4i(GLint x,
                GLint y,
                GLint z,
                GLint w);
void glVertex4f(GLfloat x,
                GLfloat y,
                GLfloat z,
                GLfloat w);
void glVertex4d(GLdouble x,
                GLdouble y,
                GLdouble z,
                GLdouble w);

void glVertex2sv(const GLshort *v);
void glVertex2iv(const GLint *v);
void glVertex2fv(const GLfloat *v);
void glVertex2dv(const GLdouble *v);
void glVertex3sv(const GLshort *v);
void glVertex3iv(const GLint *v);
void glVertex3fv(const GLfloat *v);
void glVertex3dv(const GLdouble *v);
void glVertex4sv(const GLshort *v);
void glVertex4iv(const GLint *v);
void glVertex4fv(const GLfloat *v);
void glVertex4dv(const GLdouble *v);
