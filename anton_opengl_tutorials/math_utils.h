#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include <math.h>

// const used to convert degrees into radians
#define TAU 2.0 * M_PI
#define ONE_DEG_IN_RAD ( 2.0 * M_PI ) / 360.0 // 0.017444444
#define ONE_RAD_IN_DEG 360.0 / ( 2.0 * M_PI ) // 57.2957795

typedef struct {
  float v[2];
} vec2;

void vec2_init(vec2* vec, float x, float y);

typedef struct {
  float v[3];
} vec3;

void vec3_init(vec3* vec, float x, float y, float z);
void vec3_add_vec3(vec3* vec, const vec3* rhs);

typedef struct {
  float v[4];
} vec4;

typedef struct {
  float m[9];
} mat3;

typedef struct {
  float m[16];
} mat4;

typedef struct {
  float q[4];
} versor;

void mat4_identity(mat4 *m);
/* Create a translation matrix m with a translation vector v */
void mat4_translate(mat4* m, const vec3* v);

#endif