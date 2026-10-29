#include <string.h>

typedef struct MsgItem {
	int id;			/* +0x00 */
	int value;		/* +0x04 */
	char pad08[0x10];	/* +0x08 */
} MsgItem;
/* SIZE 0x18 */

typedef struct MsgCtx {
	int dlg;		/* +0x000 */
	int flags;		/* +0x004 */
	int win;		/* +0x008 */
	int pad0c[0x13];	/* +0x00c */
	int msg;		/* +0x058 */
	char text[0x80];	/* +0x05c */
	MsgItem queue[0x100];	/* +0x0dc */
	int handles[0x300];	/* +0x18dc */
	int ids[0x80];		/* +0x24dc */
	int ids10[0x10];	/* +0x26dc */
	char pad[0x88];		/* +0x271c */
	int count;		/* +0x27a4 */
	char padTail[0x4];	/* +0x27a8 */
} MsgCtx;
/* SIZE 0x27ac */

extern int g_14ce8e0;
extern int g_14ce8d8;
extern int g_7725d0;
extern int g_6ab3dc;
extern int g_67d370;
extern int g_774654;
extern char g_6b5c60[];
extern char* g_1015ea0;
extern char* g_774a68;
extern char* g_10161bc;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005b0dd0(MsgCtx*);
void __cdecl fcn_005b0230(MsgCtx*);
void __cdecl fcn_005b11f0(MsgCtx*);
void __cdecl fcn_0057e880(int, int, int, int);
void __cdecl fcn_005b18c0(int*);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_005d0460(char*, int, int, int);

/* ADDRESS: GOLDTL 0x005bdc30 */
int __cdecl fcn_005bdc30(int flags, void* state, char* name, void (__cdecl* cb)(int, int))
{
	MsgCtx ctx;
	int mask4;
	int id;
	int i;
	int v;

	v = 0;
	memset(ctx.pad0c, 0, 0x50);
	if (state != 0) {
		memcpy(ctx.pad0c, state, 0x50);
	}
	ctx.flags = flags;
	if (name != 0) {
		strcpy(ctx.text, name);
	}
	else {
		ctx.text[0] = g_6b5c60[0];
	}
	fcn_005b0dd0(&ctx);
	fcn_005b0230(&ctx);
	if (fcn_005373e0((void*) fcn_005bdc30, 0x677c7) != 0) {
		mask4 = flags & 4;
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			g_6ab3dc = (g_7725d0 == 0);
			fcn_005b11f0(&ctx);
			id = g_67d370;
			if (mask4) {
				if (g_14ce8d8 != 0 && id != -1) {
					for (i = 0; i < 0x10; i++) {
						if (ctx.ids10[i] != -1 && ctx.ids10[i] == id) {
							v = *(int*) (g_1015ea0 + ctx.ids10[i] * 0x2f4 + 0x2f0);
							if (v != 0 && cb != 0) {
								fcn_00471af0(ctx.dlg, 0);
								fcn_00472170(*(int*) (g_10161bc + ctx.win * 0x3cc), 0);
								cb(v, v);
								fcn_00471af0(ctx.dlg, 1);
								fcn_00472170(*(int*) (g_10161bc + ctx.win * 0x3cc), 1);
								id = g_67d370;
							}
							else {
								g_774654 = 1;
							}
							break;
						}
					}
				}
			}
			else if ((flags & 8) && g_14ce8d8 != 0 && id != -1) {
				for (i = 0; i < 0x100; i++) {
					if (ctx.ids[i] != -1 && ctx.ids[i] == id) {
						v = *(int*) (g_774a68 + i * 4);
						g_774654 = 1;
						break;
					}
				}
			}
			if (ctx.count > 0) {
				for (i = 0; i < ctx.count; i++) {
					if (id != -1 && ctx.queue[i].id == id && g_14ce8d8 != 0) {
						v = 0;
						if (flags & 1) {
							v = ctx.queue[i].value;
						}
						else {
							if (!(flags & 2)) {
								continue;
							}
							fcn_00471af0(ctx.dlg, 0);
							fcn_00472170(*(int*) (g_10161bc + ctx.win * 0x3cc), 0);
							v = fcn_005d0460((char*) ctx.queue[i].value, (int) state, (int) name, (int) cb);
							fcn_00472170(*(int*) (g_10161bc + ctx.win * 0x3cc), 1);
							fcn_00471af0(ctx.dlg, 1);
							id = g_67d370;
						}
						if (v == 0) {
							continue;
						}
						if (cb == 0) {
							g_774654 = 1;
							break;
						}
						if (flags & 2) {
							continue;
						}
						fcn_00471af0(ctx.dlg, 0);
						fcn_00472170(*(int*) (g_10161bc + ctx.win * 0x3cc), 0);
						cb(v, ctx.queue[i].value);
						fcn_00471af0(ctx.dlg, 1);
						fcn_00472170(*(int*) (g_10161bc + ctx.win * 0x3cc), 1);
						break;
					}
				}
			}
		} while (fcn_005373e0((void*) fcn_005bdc30, 0x677c7) != 0);
	}
	fcn_0057e880(0xd, v, 1, 0);
	fcn_005b18c0(&ctx.dlg);
	return v;
}
unsigned char _dpad_1015f50[620];
