#include "math_utils.h"
#include <math.h>

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

void mat4_zero(mat4* m) {
  for (int i = 0; i < 16; i++) {
    m->m[i] = 0.0f;
  }
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

void mat4_rotate_y(mat4* m, double deg) {
  mat4_identity(m);
  double rad = deg * ONE_DEG_IN_RAD;
  m->m[0]  = (float)cos( rad );
  m->m[8]  = (float)sin( rad );
  m->m[2]  = (float)-sin( rad );
  m->m[10] = (float)cos( rad );
}

void mat4_copy(mat4* m, const mat4* rhs) {
  for (int i = 0; i < 16; i++) {
    m->m[i] = rhs->m[i];
  }
}

void mat4_mult(mat4* r, const mat4* m1, const mat4* m2) {
  /* Going to store the result in a temporary in case r == m1 or r == m2 */
  mat4 result;
  mat4_zero(&result);

  int r_index = 0;
  for ( int col = 0; col < 4; col++ ) {
    for ( int row = 0; row < 4; row++ ) {
      float sum = 0.0f;
      for ( int i = 0; i < 4; i++ ) {
        sum += m1->m[i + col * 4] * m2->m[row + i * 4];
      }
      result.m[r_index] = sum;
      r_index++;
    }
  }
  mat4_copy(r, &result);
}
