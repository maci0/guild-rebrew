extern char* d3_ActiveCamera;
extern void* __cdecl m_alloc(unsigned int, const char*);
extern void __cdecl m_FreeTracked(void*);
extern int __cdecl d3_TestTriangleBoxOverlap(float*, float*, float*, float*, float*);
extern int __cdecl d3_UpdateObjectCameraTransform(void*, char*, char);

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
/* ADDRESS: GOLDDE 0x00412560 */
int __cdecl d3_AccumulateMeshHeightRange(A* bounds, B* b)
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
            d3_UpdateObjectCameraTransform(b, d3_ActiveCamera, 0);
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
        if (bmin.x < bounds->f68 && bounds->f58 < bmax.x && bounds->f6c > bmin.y &&
            bounds->f70 > bmin.z && bounds->f60 < bmax.z) {
            itf = b->obj->itf;
            buf = (float*) m_alloc(itf->count, "!d3t:Vertices");
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
                V3* point;
                point = (V3*) &buf[itf->idx[i * 3 + 0] * 3];
                if (d3_TestTriangleBoxOverlap((float*) point,
                                 &buf[itf->idx[i * 3 + 1] * 3],
                                 &buf[itf->idx[i * 3 + 2] * 3],
                                 &bounds->f58, &bounds->f68)) {
                    bounds->f10 = MIN(bounds->f10, point->y);
                    bounds->f10 = MIN(bounds->f10, buf[itf->idx[i * 3 + 1] * 3 + 1]);
                    bounds->f10 = MIN(bounds->f10, buf[itf->idx[i * 3 + 2] * 3 + 1]);
                    bounds->f14 = MAX(bounds->f14, buf[itf->idx[i * 3 + 0] * 3 + 1]);
                    bounds->f14 = MAX(bounds->f14, buf[itf->idx[i * 3 + 1] * 3 + 1]);
                    bounds->f14 = MAX(bounds->f14, buf[itf->idx[i * 3 + 2] * 3 + 1]);
                }
            }
            m_FreeTracked(buf);
        }
        r = 0;
    }
    for (c = b->child; c != 0; c = c->next) {
        r &= d3_AccumulateMeshHeightRange(bounds, c);
    }
    return r;
}
