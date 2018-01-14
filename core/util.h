/*
* Copyright (c) 2017 Calvin Rose
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef DST_UTIL_H_defined
#define DST_UTIL_H_defined

#include <dst/dst.h>

/* Utils internal to dst. */

/* Type check Dst C Function arguments */
typedef struct DstCSig {
    int32_t flags;
    DstAbstractType abs;
} DstCSig;

/* Utils */
extern const char dst_base64[65];
int32_t dst_array_calchash(const Dst *array, int32_t len);
int32_t dst_kv_calchash(const DstKV *kvs, int32_t len);
int32_t dst_string_calchash(const uint8_t *str, int32_t len);
int32_t dst_tablen(int32_t n);
int dst_cstrcmp(const uint8_t *str, const char *other);
const void *dst_strbinsearch(
        const void *tab,
        size_t tabcount,
        size_t itemsize,
        const uint8_t *key);

/*
 * vector code modified from
 * https://github.com/nothings/stb/blob/master/stretchy_buffer.h
*/

/* This is mainly used code such as the assembler or compiler, which
 * need vector like data structures that are not garbage collected
 * and used only from C */

#define dst_v_free(v)         (((v) != NULL) ? (free(dst_v__raw(v)), 0) : 0)
#define dst_v_push(v, x)      (dst_v__maybegrow(v, 1), (v)[dst_v__cnt(v)++] = (x))
#define dst_v_pop(v)          (dst_v_count(v) ? dst_v__cnt(v)-- : 0)
#define dst_v_count(v)        (((v) != NULL) ? dst_v__cnt(v) : 0)
#define dst_v_add(v, n)       (dst_v__maybegrow(v, n), dst_v_cnt(v) += (n), &(v)[dst_v__cnt(v) - (n)])
#define dst_v_last(v)         ((v)[dst_v__cnt(v) - 1])
#define dst_v_copy(v)         (dst_v_copymem((v), sizeof(*(v))))
#define dst_v_flatten(v)      (dst_v_flattenmem((v), sizeof(*(v))))

#define dst_v__raw(v) ((int32_t *)(v) - 2)
#define dst_v__cap(v) dst_v__raw(v)[0]
#define dst_v__cnt(v) dst_v__raw(v)[1]

#define dst_v__needgrow(v, n)  ((v) == NULL || dst_v__cnt(v) + (n) >= dst_v__cap(v))
#define dst_v__maybegrow(v, n) (dst_v__needgrow((v), (n)) ? dst_v__grow((v), (n)) : 0)
#define dst_v__grow(v, n)      ((v) = dst_v_grow((v), (n), sizeof(*(v))))

void *dst_v_grow(void *v, int32_t increment, int32_t itemsize);
void *dst_v_copymem(void *v, int32_t itemsize);
void *dst_v_flattenmem(void *v, int32_t itemsize);

#endif