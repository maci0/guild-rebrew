#include <stdio.h>

extern void __cdecl fcn_004c09b0(void);
extern void *__cdecl fcn_00470820(int a, int b, const char *name);
extern void __cdecl fcn_00471b60(void *obj);
extern void __cdecl fcn_004727a0(void *obj, int a);
extern int __cdecl fcn_00519190(int id);
extern int __cdecl fcn_00472250(void *obj, int a, int b);
extern int __cdecl fcn_00425970(void);
extern void *__cdecl fcn_004c3030(int a, int b, const char *name, int c);
extern int __cdecl fcn_00423460(void *node);
extern void __cdecl fcn_004237f0(void *node, int a);
extern void __cdecl fcn_005373e0(int a, int b);
extern void __cdecl fcn_00471e30(void *obj);

/* ADDRESS: GOLDTL 0x004b5630 */
void __cdecl fcn_004b5630(int a0, unsigned a1)
{
	char buf[256];
	void *obj;
	int tab;
	void *node;
	unsigned b;
	unsigned i;

	fcn_004c09b0();
	obj = fcn_00470820(0, 0, (const char *) 0x681130);
	fcn_00471b60(obj);
	fcn_004727a0(obj, 1);
	fcn_00519190(0x1b9b);
	fcn_004727a0(obj, 2);
	fcn_00519190(0x6811b0);
	tab = fcn_00472250(obj, 2, fcn_00519190(0x7d));
	if (fcn_00425970()) {
		node = fcn_004c3030(-8, 0, (const char *) 0x68119c, 0);
		if (fcn_00423460(node)) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					if (fcn_00423460(node)) {
						fcn_004237f0(node, 1);
					}
					break;
				}
			} while (fcn_00423460(node));
		}
	} else {
		i = *(int *) 0x6b7fac + 0xfa;
		if (*(int *) 0x6b7fac < i) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					break;
				}
			} while (*(int *) 0x6b7fac < i);
		}
	}
	fcn_004727a0(obj, 1);
	fcn_00519190(0x1b9c);
	if (fcn_00425970()) {
		node = fcn_004c3030(-8, 0, (const char *) 0x68119c, 1);
		if (fcn_00423460(node)) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					if (fcn_00423460(node)) {
						fcn_004237f0(node, 1);
					}
					break;
				}
			} while (fcn_00423460(node));
		}
	} else {
		i = *(int *) 0x6b7fac + 0xfa;
		if (*(int *) 0x6b7fac < i) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					break;
				}
			} while (*(int *) 0x6b7fac < i);
		}
	}
	fcn_004727a0(obj, 1);
	fcn_00519190(0x1b9d);
	if (fcn_00425970()) {
		node = fcn_004c3030(-8, 0, (const char *) 0x68119c, 2);
		if (fcn_00423460(node)) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					if (fcn_00423460(node)) {
						fcn_004237f0(node, 1);
					}
					break;
				}
			} while (fcn_00423460(node));
		}
	} else {
		i = *(int *) 0x6b7fac + 0xfa;
		if (*(int *) 0x6b7fac < i) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					break;
				}
			} while (*(int *) 0x6b7fac < i);
		}
	}
	fcn_004727a0(obj, 1);
	fcn_00519190(0x6811b0);
	fcn_00519190(0x1b9e);
	fcn_00519190(*(int *) (a0 + 8) + 2);
	if (fcn_00425970()) {
		sprintf(buf, (const char *) 0x681180, *(unsigned *) (a0 + 0x10));
		node = fcn_004c3030(-7, 0, buf, -1);
		if (fcn_00423460(node)) {
			b = a1 | 0x80;
			while (fcn_005373e0(0, b), *(int *) 0x100f1dc == -1 || *(int *) 0x67d370 != tab) {
				if (!fcn_00423460(node)) {
					fcn_00471e30(obj);
					return;
				}
			}
			if (fcn_00423460(node)) {
				fcn_004237f0(node, 1);
			}
		}
	} else {
		i = *(int *) 0x6b7fac + 0xfa;
		if (*(int *) 0x6b7fac < i) {
			b = a1 | 0x80;
			do {
				fcn_005373e0(0, b);
				if (*(int *) 0x100f1dc != -1 && *(int *) 0x67d370 == tab) {
					break;
				}
			} while (*(int *) 0x6b7fac < i);
		}
	}
	fcn_00471e30(obj);
}
