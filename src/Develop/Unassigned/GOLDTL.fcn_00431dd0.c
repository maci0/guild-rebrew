
extern float g_6628a0;

typedef struct Cam {
    char pad_00[0x4c];
    float pos[3];
    char pad_58[0x20];
    float off[3];
    char pad_84[0x108];
    float rot[3][4];
} Cam;

typedef struct Seg {
    int id;
    int len;
    char pad_08[0x18];
    float sx;
    float sy;
    float sz;
    char pad_2c[0x94];
} Seg;

typedef struct PathInfo {
    char pad_00[0x15c];
    Seg* segs;
    char pad_160[9];
    unsigned char flag;
} PathInfo;

typedef struct PathState {
    int a;
    int b;
    int c;
    int d;
    int e;
    char pad_14[0x54];
    PathInfo* info;
} PathState;

/* ADDRESS: GOLDTL 0x00431dd0 */
void __cdecl fcn_00431dd0(Cam* cam, PathState* ps, int a2, int a3, float* out)
{
    PathInfo* info;
    Seg* segs;
    Seg* cur;
    Seg* tgt;
    int v1;
    int v2;
    int i;
    float t;
    float p[3];
    float d[3];

    info = ps->info;
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    if (info->flag != 0) {
        segs = info->segs;
        tgt = &segs[a2];
        v1 = ps->d;
        v2 = ps->e;
        cur = &segs[v1];
        if (a3 == v2 && v1 == a2) {
            out[0] = cam->off[0] + cam->pos[0];
            out[1] = cam->off[1] + cam->pos[1];
            out[2] = cam->off[2] + cam->pos[2];
            return;
        }
        if (v1 < a2) {
            t = g_6628a0 - (float) v2 / (float) cur->len;
            d[0] = segs[v1 + 1].sx - cur->sx;
            d[1] = segs[v1 + 1].sy - cur->sy;
            d[2] = segs[v1 + 1].sz - cur->sz;
            p[0] = d[0] * t;
            p[1] = d[1] * t;
            p[2] = d[2] * t;
        }
        for (i = v1 + 1; i < a2; i++) {
            d[0] = segs[i + 1].sx - segs[i].sx;
            d[1] = segs[i + 1].sy - segs[i].sy;
            d[2] = segs[i + 1].sz - segs[i].sz;
            p[0] += d[0];
            p[1] += d[1];
            p[2] += d[2];
        }
        if (v1 == a2) {
            a3 -= v2;
        }
        t = (float) a3 / (float) tgt->len;
        d[0] = segs[a2 + 1].sx - tgt->sx;
        d[1] = segs[a2 + 1].sy - tgt->sy;
        d[2] = segs[a2 + 1].sz - tgt->sz;
        p[0] += d[0] * t;
        p[1] += d[1] * t;
        p[2] += d[2] * t;
        out[0] = cam->rot[2][0] * p[2] + cam->rot[1][0] * p[1] + cam->rot[0][0] * p[0] + cam->pos[0];
        out[1] = cam->rot[2][1] * p[2] + cam->rot[1][1] * p[1] + cam->rot[0][1] * p[0];
        out[2] = cam->rot[2][2] * p[2] + cam->rot[1][2] * p[1] + cam->rot[0][2] * p[0];
    } else {
        segs = info->segs;
        cur = &segs[ps->a];
        tgt = &segs[ps->b];
        t = (float) ps->c / (float) cur->len;
        p[0] = cur->sx + (tgt->sx - cur->sx) * t;
        p[1] = cur->sy + (tgt->sy - cur->sy) * t;
        p[2] = cur->sz + (tgt->sz - cur->sz) * t;
        out[0] = cam->rot[2][0] * p[2] + cam->rot[1][0] * p[1] + cam->rot[0][0] * p[0] + cam->pos[0];
        out[1] = cam->rot[2][1] * p[2] + cam->rot[1][1] * p[1] + cam->rot[0][1] * p[0];
        out[2] = cam->rot[2][2] * p[2] + cam->rot[1][2] * p[1] + cam->rot[0][2] * p[0];
    }
    out[1] = cam->pos[1] + out[1];
    out[2] = cam->pos[2] + out[2];
    out[0] = cam->off[0] + out[0];
    out[1] = cam->off[1] + out[1];
    out[2] = cam->off[2] + out[2];
}
