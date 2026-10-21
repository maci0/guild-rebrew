extern char* g_6b8014;
extern void* __cdecl m_alloc(unsigned int, const char*);
extern void __cdecl m_FreeTracked(void*);
extern int __cdecl fcn_00413e00(float*, float*, float*, float*, float*);
extern int __cdecl fcn_00438100(void*, char*, char);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct V3 { float x; float y; float z; } V3;
typedef struct VB { float x; float y; float z; char pad[4]; } VB;

typedef struct V {
    float x;
    float y;
    float z;
    char pad[0x44];
} V;

typedef struct M {
    char pad[8];
    float m[16];
} M;

typedef struct OBJ {
    char pad0[0x318];
    struct I* itf;
} OBJ;

typedef struct I {
    char pad0[0x44];
    int count;
    char pad1[0x1f0 - 0x48];
    void* (__cdecl *getv)(void*, void*, float*);
    char pad2[0x27c - 0x1f4];
    V3* points;
    unsigned short* idx;
} I;

typedef struct B {
    char pad0[0x1cc];
    OBJ* obj;
    char pad1[0x1c];
    M* mat;
    char pad2[4];
    struct B* next;
    char pad3[8];
    struct B* child;
    char pad4[0x12];
    unsigned char flags;
    char pad5[1];
    int type;
} B;

typedef struct A {
    char pad0[0x10];
    float f10;
    float f14;
    char pad1[0x40];
    float f58;
    char pad2[4];
    float f60;
    char pad3[4];
    float f68;
    float f6c;
    float f70;
} A;

/* ADDRESS: GOLDTL 0x00413fb0 */
int __cdecl fcn_00413fb0(A* a1, B* b)
{
    int r;
    int i;
    VB bmax;
    VB bmin;
    float* buf;
    V* v;
    I* itf;
    B* c;

    r = 1;
    if (b->type == 4) {
        if (b->obj == 0) {
            return r;
        }
        if ((b->flags & 0x20) == 0) {
            fcn_00438100(b, g_6b8014, 0);
        }
        v = (V*) b->obj->itf->getv(b, b->obj, b->mat->m);
        bmin.x = v->x;
        bmin.y = v->y;
        bmin.z = v->z;
        bmax.x = v->x;
        bmax.y = v->y;
        bmax.z = v->z;
        v++;
        /* reverse order: same folds, native register assignment */
        for (i = 6; i >= 0; i--) {
            bmin.x = MIN(bmin.x, v->x);
            bmin.y = MIN(bmin.y, v->y);
            bmin.z = MIN(bmin.z, v->z);
            bmax.x = MAX(bmax.x, v->x);
            bmax.y = MAX(bmax.y, v->y);
            bmax.z = MAX(bmax.z, v->z);
            v++;
        }
        if (bmin.x < a1->f68 && a1->f58 < bmax.x && a1->f6c > bmin.y &&
            a1->f70 > bmin.z && a1->f60 < bmax.z) {
            itf = b->obj->itf;
            buf = (float*) m_alloc(itf->count, (char*) 0x67755c);
            for (i = 0; i < itf->count; i++) {
                buf[i * 3 + 0] = itf->points[i].z * b->mat->m[8] +
                                 itf->points[i].y * b->mat->m[4] +
                                 itf->points[i].x * b->mat->m[0] + b->mat->m[12];
                buf[i * 3 + 1] = itf->points[i].z * b->mat->m[9] +
                                 itf->points[i].y * b->mat->m[5] +
                                 b->mat->m[1] * itf->points[i].x + b->mat->m[13];
                buf[i * 3 + 2] = itf->points[i].z * b->mat->m[10] +
                                 itf->points[i].y * b->mat->m[6] +
                                 b->mat->m[2] * itf->points[i].x + b->mat->m[14];
            }
            for (i = 0; i < itf->count; i++) {
                V3* v0;
                v0 = (V3*) &buf[itf->idx[i * 3 + 0] * 3];
                if (fcn_00413e00((float*) v0,
                                 &buf[itf->idx[i * 3 + 1] * 3],
                                 &buf[itf->idx[i * 3 + 2] * 3],
                                 &a1->f58, &a1->f68)) {
                    a1->f10 = MIN(a1->f10, v0->y);
                    a1->f10 = MIN(a1->f10, buf[itf->idx[i * 3 + 1] * 3 + 1]);
                    a1->f10 = MIN(a1->f10, buf[itf->idx[i * 3 + 2] * 3 + 1]);
                    a1->f14 = MAX(a1->f14, buf[itf->idx[i * 3 + 0] * 3 + 1]);
                    a1->f14 = MAX(a1->f14, buf[itf->idx[i * 3 + 1] * 3 + 1]);
                    a1->f14 = MAX(a1->f14, buf[itf->idx[i * 3 + 2] * 3 + 1]);
                }
            }
            m_FreeTracked(buf);
        }
        r = 0;
    }
    for (c = b->child; c != 0; c = c->next) {
        r &= fcn_00413fb0(a1, c);
    }
    return r;
}
