#include <string.h>
#include <stddef.h>

/* Private inferred views; only the accessed offsets and extents are known. */
typedef struct {
    char *entity;
    int control;
    char unknown[8];
    int x, y;
    char rest[0x20];
} ITEM;

typedef struct {
    int enabled, size, field8, fieldc, kind, field14;
    char field18[4];
    unsigned short excluded[4];
    char remainder[0x2c];
} REQUEST;

typedef char item_size_check[sizeof(ITEM) == 0x38 ? 1 : -1];
typedef char item_control_check[offsetof(ITEM, control) == 4 ? 1 : -1];
typedef char item_position_check[offsetof(ITEM, x) == 0x10 && offsetof(ITEM, y) == 0x14 ? 1 : -1];
typedef char request_size_check[sizeof(REQUEST) == 0x50 ? 1 : -1];
typedef char request_excluded_check[offsetof(REQUEST, excluded) == 0x1c ? 1 : -1];

extern unsigned short g_774970;
extern int g_772514, g_14b59e8, g_14b59ec;
extern int g_14b59fc, g_14b5a00, g_14ce8e0, g_774654;
extern int g_100f1dc, g_67d370, g_666018, g_66601c;
extern unsigned int g_6b7fac;
extern char *g_772500, *g_1015ea0;
extern char g_7f4ca0[], g_1015f4c[], g_6811b0[];
extern char *g_14b59f0, *g_14b59f4;

void __cdecl fcn_005263d0(int, int, int);
int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00533a60(int, int, int *, int, ...);
int __cdecl fcn_00510400(char *);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005ca560(ITEM *);
void __cdecl fcn_005ca740(int, int, int, int, ITEM *, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_004e99c0(int);
int __cdecl fcn_00525f60(char *, int);
int __cdecl io_FormatTextBuffer(char *, int, ...);
float __cdecl fcn_00507e70(char *, char *, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_005b2a40(unsigned short *, int, char **);
void __cdecl fcn_00526120(char *, int);
char *__cdecl fcn_005cd440(REQUEST *, char *, int, int);
int __cdecl fcn_005373e0(void (__cdecl *)(void *), int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005e53b0 */
void __cdecl fcn_005e53b0(void *arg)
{
    ITEM items[5];
    REQUEST request;
    int cache[5], buttons[2];
    char *selected[4];
    char text[0x800];
    char *house, *p, *ui;
    int window, refresh, cost, count, i, n, j, width;
    unsigned int last;

    memset(items, 0, sizeof(items));
    for (i = 0; i < 5; ++i) cache[i] = -1;
    refresh = 1;
    cost = 0;
    last = 0;
    house = g_7f4ca0 + g_774970 * 0x21c;
    if (house[0x1cc] & 8) {
        fcn_005263d0(g_14b59e8, g_14b59ec, 0);
        return;
    }
    window = fcn_00470820(0, 0, "Locations\\zigeuner\\blutrache");
    d2_SetOverlayAnimation(0, 0);
    fcn_00471b60(window);
    d2_SetForm(window, 0);
    fcn_005340f0(g_772514);
    d2_SetForm(window, 1);
    width = *(int *)(g_1015f4c + g_772514 * 972) - *(short *)(g_772500 + 0x1ebd8);
    items[0].x = width / 2; items[0].y = 30;
    items[1].x = width / 3 - 10; items[1].y = 125;
    items[2].x = width * 2 / 3 + 10; items[2].y = 125;
    items[3].x = width / 3 - 100; items[3].y = 220;
    items[4].x = width * 2 / 3 + 100; items[4].y = 220;
    d2_SetForm(window, 3);
    fcn_00533a60(g_772514, 0, buttons, 2, g_14b59fc, g_14b5a00);
    do {
        if (refresh) {
            count = fcn_00510400((char *)arg) + 1;
            last = g_6b7fac;
            refresh = 0;
            d2_SetForm(window, 1);
            io_AppendText((int)g_6811b0);
            io_AppendText(0x41b2);
            cost = 0;
            for (i = 0; i < 5; ++i) {
                if (i >= count) { items[i].entity = 0; cache[i] = -1; }
                fcn_005ca560(&items[i]);
                fcn_005ca740(items[i].x, items[i].y, g_772514, 0x54, &items[i], 1);
                if (i < count) {
                    fcn_00472640(items[i].control, 1);
                    ui = g_1015ea0 + items[i].control * 756;
                    *(int *)(ui + 0x5c) = 1;
                    *(int *)(ui + 0x1d0) = 3;
                    *(char **)(ui + 0x2f0) = items[i].entity;
                    *(int *)(ui + 0x60) = 0;
                } else {
                    ui = g_1015ea0 + items[i].control * 756;
                    *(int *)(ui + 0x60) = 1;
                }
                p = items[i].entity;
                if (p && i) cost += fcn_004e99c0((unsigned char)p[0x166]) / 3 + 2;
            }
            d2_SetForm(window, 2);
            io_AppendText((int)g_6811b0, cost);
            io_AppendText(0x41b6, cost);
            fcn_00472640(buttons[0], items[0].entity != 0 && cost != 0);
        }
        if (g_14ce8e0) g_774654 = 1;
        else if (g_100f1dc != -1) {
            if (g_67d370 == buttons[0]) {
                house = g_7f4ca0 + g_774970 * 0x21c;
                if (fcn_00525f60(house, cost) == 1) {
                    p = items[0].entity;
                    io_FormatTextBuffer(text, 0x41bf, *(unsigned short *)p);
                    n = 0;
                    for (i = 1; i < 5; ++i) {
                        if (items[i].entity) {
                            j = (int)(fcn_00507e70(g_7f4ca0 + g_774970 * 0x21c, items[i].entity, 4) * -50.0f);
                            fcn_004c54c0(*(unsigned short *)items[0].entity, *(unsigned short *)items[i].entity, j - 50, 1);
                            selected[n++] = items[i].entity;
                        }
                    }
                    fcn_005100f0(*(int *)(g_7f4ca0 + g_774970 * 0x21c + 4), -cost);
                    fcn_004c5420(*(int *)(g_7f4ca0 + g_774970 * 0x21c + 4), 0x1cc, 4, 8, 0);
                    fcn_005b2a40((unsigned short *)p, n, selected);
                    io_FormatTextBuffer(text, 0x41b9, 0x41b2);
                    fcn_00526120(text, 0);
                    g_774654 = 1;
                }
            } else if (g_67d370 == buttons[1]) g_774654 = 1;
            else {
                for (i = 0; i < 5; ++i) if (g_67d370 == items[i].control) break;
                if (i < 5) {
                    memset(&request, 0, sizeof(request));
                    n = 0;
                    for (j = 0; j < 5; ++j) {
                        if (j != i) request.excluded[n++] = items[j].entity ? *(unsigned short *)items[j].entity : 0xffff;
                    }
                    request.enabled = 1; request.size = 0x400;
                    request.field8 = g_666018; request.fieldc = g_66601c;
                    request.kind = 6; request.field14 = 2;
                    p = fcn_005cd440(&request, i ? g_14b59f4 : g_14b59f0, 0, 0);
                    items[i].entity = p;
                    cache[i] = p ? *(int *)(p + 4) : -1;
                    refresh = 1;
                }
            }
        } else if (g_6b7fac > last + 140u) {
            for (i = 0; i < 5; ++i) {
                p = items[i].entity;
                if (p && (*(unsigned short *)p == 0xffff || *(int *)(p + 4) != cache[i])) {
                    items[i].entity = 0;
                    cache[i] = -1;
                }
            }
            refresh = 1;
        }
    } while (fcn_005373e0(fcn_005e53b0, 0x677c7));
    fcn_00471e30(window);
    fcn_00532ef0();
}
