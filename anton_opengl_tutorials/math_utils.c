#include "math_utils.h"

void vec2_init(vec2* vec, float x, float y) {
  vec->v[0] = x;
  vec->v[1] = y;
}

void vec3_init(vec3* vec, float x, float y, float z) {
  vec->v[0] = x;
  vec->v[1] = y;
  vec->v[2] = z;
}

void vec3_add_vec3(vec3* vec, const vec3* rhs) {
  vec->v[0] += rhs->v[0];
  vec->v[1] += rhs->v[1];
  vec->v[2] += rhs->v[2];
}

void mat4_identity(mat4* m) {
  m->m[0] = 1.0f;
  m->m[1] = 0.0f;
  m->m[2] = 0.0f;
  m->m[3] = 0.0f;

  m->m[4] = 0.0f;
  m->m[5] = 1.0f;
  m->m[6] = 0.0f;
  m->m[7] = 0.0f;

  m->m[8] = 0.0f;
  m->m[9] = 0.0f;
  m->m[10] = 1.0f;
  m->m[11] = 0.0f;

  m->m[12] = 0.0f;
  m->m[13] = 0.0f;
  m->m[14] = 0.0f;
  m->m[15] = 1.0f;
}

void mat4_translate(mat4* m, const vec3* v) {
  mat4_identity(m);
  m->m[12] = v->v[0];
  m->m[13] = v->v[1];
  m->m[14] = v->v[2];
}