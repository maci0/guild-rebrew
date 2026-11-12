#include <math.h>

/* Projected shadow of one scene object into its shadow texture.
 *
 * The object's bounding volume (or the eight corner points returned by the
 * sub-object's corner callback) is projected along the light onto the ground
 * plane at the given height; the resulting ground rectangle is clipped to the
 * shadow-map grid, then the object is rendered with a planar shadow matrix
 * into the render-to-surface target that matches the texture size. */

extern unsigned char g_1040600;
extern float* g_6b89e4;
extern unsigned int g_104061c;
extern void** g_1040610[];
extern void* g_6b5de0;
extern unsigned long g_14ce728;
extern float g_662a98;

void __cdecl fcn_00455350(char* object, float* in, float* out);
void* __cdecl fcn_00436930(char* o, float* r);
void __cdecl fcn_00436fd0(int a);
void __stdcall fcn_005edf4a(float* plane, float* point, float* normal);
void __stdcall fcn_005ed44c(float* out, float* light, float* plane);
void __stdcall fcn_005eb970(float* out, float* a, float* b);
void __stdcall fcn_005ec410(float* out, float x, float y, float z);
void __stdcall fcn_005ec4b3(float* out, float angle);
void __stdcall fcn_005ed39b(float* out, float l, float r, float b, float t,
                            float zn, float zf);

/* ADDRESS: GOLDTL 0x004582d0 */
void __cdecl fcn_004582d0(char* a0, char* a1, char* a2, char* map, float* va,
                          float* vb, char* node, int* rec, float height)
{
    float minx;
    float maxx;
    float minz;
    float maxz;
    void* surf;
    int idx;
    float size;
    float d[3];
    float light[4];
    char* tex;
    float point[3];
    float normal[3];
    int vp[6];
    float plane[4];
    float m[16];
    float t[16];
    float* v;
    float k;
    int i;
    int x;
    int z;
    int x0;
    int x1;
    int z1;
    int w;
    int top;
    int mask;
    void* mesh;
    unsigned int n;

    tex = (char*) rec[0];
    rec[7] = *(int*) &va[0];
    rec[8] = *(int*) &va[1];
    rec[9] = *(int*) &va[2];
    minz = 1.0e10f;
    minx = 1.0e10f;
    maxz = -1.0e10f;
    maxx = -1.0e10f;
    if (*(unsigned char*) &rec[0x26] != 0) {
        fcn_00455350(a0, (float*) (a0 + 0x4c), d);
        height = height + g_662a98;
        minx = d[0] - *(float*) 0x662db8;
        maxx = d[0] + *(float*) 0x662db8;
        minz = d[2] - *(float*) 0x662db8;
        maxz = d[2] + *(float*) 0x662db8;
    } else {
        v = ((float* (__cdecl*) (char*, char*, char*))
            *(void**) (*(char**) (a1 + 0x318) + 0x1f0))(
            a0, a1, *(char**) (a0 + 0x1ec) + 8);
        for (i = 8; i != 0; i--) {
            if (*(unsigned char*) (node + 0x215) & 4) {
                k = -((v[1] - height) / va[1]);
                v[0] = k * va[0] + v[0];
                v[1] = k * va[1] + v[1];
                v[2] = k * va[2] + v[2];
            } else {
                d[0] = vb[0] - v[0];
                d[1] = vb[1] - v[1];
                d[2] = vb[2] - v[2];
                k = -((vb[1] - height) / d[1]);
                v[0] = d[0] * k + vb[0];
                v[1] = d[1] * k + vb[1];
                v[2] = k * d[2] + vb[2];
            }
            if (!(v[2] > minz))
                minz = v[2];
            if (!(v[2] < maxz))
                maxz = v[2];
            if (!(minx < v[0]))
                minx = v[0];
            if (!(maxx > v[0]))
                maxx = v[0];
            v += 0x14;
        }
    }
    if (fabs(maxx) > *(double*) 0x662db0 || fabs(minx) > *(double*) 0x662db0
        || fabs(maxz) > *(double*) 0x662db0 || fabs(minz) > *(double*) 0x662db0
        || fabs(maxx - minx) > *(double*) 0x662db0
        || fabs(maxz - minz) > *(double*) 0x662db0)
        return;
    rec[0x1c] = -1;
    rec[4] = 0;
    rec[5] = 0;
    if (g_1040600 != 0) {
        if (map != 0 && *(unsigned char*) &rec[0x26] == 0) {
            rec[0x18] = (int) ((minx - *(float*) (map + 0x50)) / *(float*) (map + 0x60));
            rec[0x19] = (int) ((maxx - *(float*) (map + 0x50)) / *(float*) (map + 0x60) + 1.0);
            rec[0x1a] = (int) ((maxz - *(float*) (map + 0x58)) / *(float*) (map + 0x78));
            rec[0x1b] = (int) ((minz - *(float*) (map + 0x58)) / *(float*) (map + 0x78) + 1.0);
            w = *(int*) map;
            if (rec[0x18] < w && rec[0x19] > 0 && rec[0x1a] < w && rec[0x1b] > 0) {
                top = 0;
                x0 = rec[0x18] < 0 ? 0 : rec[0x18];
                x1 = w - 1 < rec[0x19] ? w - 1 : rec[0x19];
                z1 = w - 1 < rec[0x1b] ? w - 1 : rec[0x1b];
                rec[0x1d] = x0 / *(int*) (map + 4);
                rec[0x1f] = x1 / *(int*) (map + 4);
                rec[0x1c] = (rec[0x1a] < 0 ? 0 : rec[0x1a]) / *(int*) (map + 4);
                rec[0x1e] = z1 / *(int*) (map + 4);
                for (z = rec[0x1c]; z <= rec[0x1e]; z++) {
                    for (x = rec[0x1d]; x <= rec[0x1f]; x++) {
                        if (top <= *(unsigned char*) (map + (x + z * 8) * 500 + 0x28e))
                            top = *(unsigned char*) (map + (x + z * 8) * 500 + 0x28e);
                    }
                }
                rec[6] = top;
                if (top > 1) {
                    mask = ~(top - 1);
                    rec[0x18] &= mask;
                    if (rec[0x19] & (top - 1))
                        rec[0x19] = (rec[0x19] + top) & mask;
                    rec[0x1a] &= mask;
                    if (rec[0x1b] & (top - 1))
                        rec[0x1b] = (rec[0x1b] + top) & mask;
                }
                rec[4] = *(int*) (map + 0x10);
                rec[5] = *(int*) map - 1;
                rec[0xb] = *(int*) (map + 0x60);
                rec[0xc] = *(int*) (map + 0x84);
                rec[0xd] = *(int*) (map + 0x78);
                rec[0xf] = *(int*) (map + 0x50);
                rec[0x10] = *(int*) (map + 0x54);
                rec[0x11] = *(int*) (map + 0x58);
                minx = (float) rec[0x18] * *(float*) (map + 0x60) + *(float*) (map + 0x50);
                maxx = (float) rec[0x19] * *(float*) (map + 0x60) + *(float*) (map + 0x50);
                minz = (float) rec[0x1a] * *(float*) (map + 0x78) + *(float*) (map + 0x58);
                maxz = (float) rec[0x1b] * *(float*) (map + 0x78) + *(float*) (map + 0x58);
            }
        } else if (g_6b89e4 != 0 && *(unsigned char*) &rec[0x26] == 0) {
            rec[0x18] = (int) ((minx - g_6b89e4[0]) / g_6b89e4[4]);
            rec[0x19] = (int) ((maxx - g_6b89e4[0]) / g_6b89e4[4] + 1.0);
            rec[0x1a] = (int) ((maxz - g_6b89e4[2]) / g_6b89e4[6]);
            rec[0x1b] = (int) ((minz - g_6b89e4[2]) / g_6b89e4[6] + 1.0);
            if (rec[0x18] < *(int*) &g_6b89e4[8] && rec[0x19] > 0
                && rec[0x1a] < *(int*) &g_6b89e4[8] && rec[0x1b] > 0) {
                rec[4] = *(int*) &g_6b89e4[10];
                rec[5] = *(int*) &g_6b89e4[8];
                rec[0xb] = *(int*) &g_6b89e4[4];
                rec[0xc] = *(int*) &g_6b89e4[5];
                rec[0xd] = *(int*) &g_6b89e4[6];
                rec[0xf] = *(int*) &g_6b89e4[0];
                rec[0x10] = *(int*) &g_6b89e4[1];
                rec[0x11] = *(int*) &g_6b89e4[2];
                minx = (float) rec[0x18] * g_6b89e4[4] + g_6b89e4[0];
                maxx = (float) rec[0x19] * g_6b89e4[4] + g_6b89e4[0];
                minz = (float) rec[0x1a] * g_6b89e4[6] + g_6b89e4[2];
                maxz = (float) rec[0x1b] * g_6b89e4[6] + g_6b89e4[2];
            }
        }
    }
    *(float*) &rec[0x14] = maxx;
    *(float*) &rec[0x13] = minx;
    *(float*) &rec[0x17] = height;
    *(float*) &rec[0x15] = minz;
    *(float*) &rec[0x16] = maxz;
    if (*(unsigned char*) &rec[0x26] != 0)
        return;
    size = (float) *(unsigned int*) (tex + 0x64);
    point[0] = 0.0f;
    point[1] = height;
    point[2] = 0.0f;
    normal[0] = 0.0f;
    normal[1] = 1.0f;
    normal[2] = 0.0f;
    fcn_005edf4a(plane, point, normal);
    if (*(unsigned char*) (node + 0x215) & 4) {
        light[0] = -va[0];
        light[1] = -va[1];
        light[2] = -va[2];
        light[3] = 0.0f;
    } else {
        light[3] = 1.0f;
        light[0] = vb[0];
        light[1] = vb[1];
        light[2] = vb[2];
    }
    fcn_005ed44c(m, light, plane);
    fcn_005eb970(m, (float*) (*(char**) (a0 + 0x1ec) + 8), m);
    fcn_005ec410(t, 0.0f, -height - 1.0f, 0.0f);
    fcn_005eb970(m, m, t);
    fcn_005ec4b3(t, -1.5707964f);
    fcn_005eb970(m, m, t);
    vp[2] = (int) size;
    vp[3] = vp[2];
    *(float*) &vp[4] = 0.0f;
    *(float*) &vp[5] = 1.0f;
    vp[1] = 0;
    vp[0] = 0;
    (*(int (__stdcall**) (void*, int, void**)) (**(char***) (tex + 0x50) + 0x3c))(
        *(void**) (tex + 0x50), 0, &surf);
    idx = 0;
    for (n = g_104061c; n != *(unsigned int*) (tex + 0x64); n += n)
        idx++;
    if ((*(int (__stdcall**) (void*, void*, int*)) ((char*) *g_1040610[idx] + 0x14))(
            g_1040610[idx], surf, vp) >= 0) {
        (*(int (__stdcall**) (void*, int, float*)) (*(char**) g_6b5de0 + 0x94))(
            g_6b5de0, 0x100, m);
        fcn_005ed39b(t, minx, maxx, minz, maxz, 0.5f, 1.5f);
        (*(int (__stdcall**) (void*, int, float*)) (*(char**) g_6b5de0 + 0x94))(
            g_6b5de0, 3, t);
        (*(int (__stdcall**) (void*, int, void*, int, int, float, int))
            (*(char**) g_6b5de0 + 0x90))(g_6b5de0, 0, 0, 1, 0, 1.0f, 0);
        mesh = fcn_00436930(a2, 0);
        for (n = 0; n < *(unsigned int*) (*(char**) (a2 + 0x318) + 0x1e4); n++)
            (*(int (__stdcall**) (void*, unsigned int)) (*(char**) mesh + 0xc))(mesh, n);
        (*(int (__stdcall**) (void*)) ((char*) *g_1040610[idx] + 0x18))(g_1040610[idx]);
    }
    g_14ce728 = (*(unsigned long (__stdcall**) (void*)) (*(char**) surf + 8))(surf);
    if (*(unsigned char*) ((char*) rec[3] + 0x10) != 0)
        fcn_00436fd0(*(int*) (tex + 0x50));
}
