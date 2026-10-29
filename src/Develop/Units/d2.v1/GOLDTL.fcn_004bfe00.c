#include <string.h>

void *__cdecl fcn_004be2a0(void *);
void *__cdecl fcn_004be1f0(void *);
int __cdecl fcn_004be340(void *);
void __cdecl fcn_004be280(void *);
void __cdecl fcn_004be3d0(void *, void *, void *, void *);
void __cdecl fcn_004be530(void);
void __cdecl fcn_004bf1b0(int, void *);
void __cdecl fcn_004bf8e0(void *, void *);
void __cdecl fcn_004bfc10(void);
void __cdecl fcn_004bfca0(void *, void *);
int __cdecl fcn_00469510(int);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4700(int, int, int, char *);
void __cdecl fcn_004c53a0(void);
void __cdecl fcn_004c6e20(int, void *);
void __cdecl fcn_004c6ea0(int);
int __cdecl gm_SearchTable67(int);
void __cdecl fcn_00533bb0(int, int, void *, int, int, int, int);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_005b0230(void *);
int __cdecl fcn_005b0dd0(void *);
void __cdecl fcn_005b11f0(void *);
void __cdecl fcn_005b18c0(void *);

/* ADDRESS: GOLDTL 0x004bfe00 */
int __cdecl fcn_004bfe00(char *obj)
{
	char loc[0x27dc];
	char *town;
	char *p;
	int *slot;
	int head;
	int i;
	int j;
	int n;
	int v;

	town = loc + 0x30;
	*(int *) 0x772904 = 0;
	if (obj == 0) {
		return 0;
	}
	*(void **) 0x772908 = fcn_004be2a0(*(void **) (obj + 0x29));
	memset(loc + 0x3c, 0, 0x50);
	*(int *) (loc + 0x40) = 0x400;
	*(int *) (loc + 0x4c) = 0;
	*(int *) (loc + 0x48) = 0x40000001;
	*(int *) (loc + 0x44) = (int) 0xb07d7fb0;
	*(int *) (loc + 0x34) = 0x10;
	*(int *) (loc + 0x88) = 0x723;
	strcpy(loc + 0x90, *(char **) 0x14b5e84);
	fcn_005b0dd0(town);
	fcn_005b0230(town);
	*(int *) 0x772900 = 0;
	for (i = 0; i < 8; i++) {
		*(int *) (0x10058a0 + i * 8) = -1;
		*(int *) (0x10058a4 + i * 8) = 0;
	}
	head = *(int *) 0x772908;
	if (head == 0) {
		fcn_004c4510((int) obj, *(int *) (obj + 2));
		fcn_004c4700(1, 1, (int) (obj - *(int *) 0xaed32c) + 0x33, loc + 0x0b);
		fcn_004c53a0();
		head = (int) fcn_004be1f0(0);
		*(int *) 0x772908 = head;
		*(int *) (head + 4) = *(int *) (obj + 0x1c);
		*(int *) head = *(int *) (obj + 2);
		fcn_004be3d0(town, obj, (void *) head, (void *) head);
		fcn_004695a0(*(int *) 0x6816d8, 0);
		*(int *) 0x772904 = 0;
	} else {
		for (p = (char *) head; p != 0; p = *(char **) (p + 0x3c)) {
			fcn_004be3d0(town, obj, (void *) head, p);
		}
	}
	d2_SetForm(*(int *) town, 2);
	fcn_00533bb0(*(int *) 0x772514, 5, loc + 0x14, 3,
		*(int *) 0x14b5e90, *(int *) 0x14b5e94, *(int *) 0x14b5e98);
	while (fcn_005373e0((void *) 0x4bfe00, 0x657c7) != 0) {
		if (*(int *) 0x14ce8e0 != 0) {
			*(int *) 0x774654 = 1;
		}
		*(int *) 0x6ab3dc = (*(int *) 0x7725d0 == 0);
		if (*(int *) 0x100f1dc != -1) {
			if (*(int *) 0x67d370 == *(int *) (loc + 8)) {
				fcn_004bf8e0(obj, town);
			} else if (*(int *) 0x67d370 == *(int *) town) {
				if (*(int *) 0x6816d8 != -1) {
					v = *(int *) (*(int *) 0x6816d8 * 0x8c + 0x102cbc8);
					if (v != -1) {
						fcn_004bf1b0(*(int *) (0x10058a4 + v * 8), town);
					}
				}
			} else if (*(int *) 0x67d370 == *(int *) (loc + 0x34) && *(int *) 0x772904 != 0) {
				p = (char *) fcn_004be1f0((void *) *(int *) 0x772908);
				*(int *) (p + 4) = *(int *) (*(int *) 0x772904 + 1);
				*(int *) p = *(int *) (obj + 2);
				fcn_004be3d0(town, obj, (void *) *(int *) 0x772908, p);
				fcn_004695a0(*(int *) 0x6816d8, *(int *) 0x772900 - 1);
				*(int *) 0x772904 = 0;
			}
		}
		fcn_005b11f0(town);
		if (*(int *) 0x14ce8d8 != 0 && *(int *) 0x67d370 != -1 &&
		    *(int *) (loc + 0x27a4) > 0) {
			n = *(int *) (loc + 0x27a4);
			for (i = 0; i < n; i++) {
				slot = (int *) (loc + 0x10c + i * 0x18);
				if (slot[0] == *(int *) 0x67d370) {
					*(int *) 0x772904 = slot[1];
					for (j = 0; j < 8; j++) {
						v = *(int *) (0x10058a4 + j * 8);
						if (v != 0 && (v = *(int *) (v + 4)) != -1 &&
						    gm_SearchTable67(v) == *(int *) 0x772904) {
							fcn_004695a0(*(int *) 0x6816d8, j);
							*(int *) 0x772904 = 0;
						}
					}
					break;
				}
			}
		}
		if (*(int *) 0x772904 == 0) {
			fcn_00472640(*(int *) (loc + 4), 0);
			fcn_00472640(*(int *) town, 1);
		} else {
			fcn_00472640(*(int *) (loc + 4), 1);
			fcn_00472640(*(int *) town, 0);
		}
		fcn_004bfca0((void *) *(int *) 0x772908, town);
		fcn_004bfc10();
		fcn_004be530();
	}
	n = fcn_004be340((void *) *(int *) 0x772908);
	if (n < 2) {
		fcn_004c6ea0((int) obj);
		fcn_004c4510((int) obj, *(int *) (obj + 2));
		fcn_004c4700(1, 1, (int) (obj - *(int *) 0xaed32c) + 0x33, loc + 0x07);
		fcn_004c53a0();
	} else {
		fcn_004c6e20((int) obj, (void *) *(int *) 0x772908);
	}
	fcn_005b18c0(town);
	if (*(int *) 0x6816d8 != -1) {
		fcn_00469510(*(int *) 0x6816d8);
		*(int *) 0x6816d8 = -1;
	}
	fcn_004be280((void *) *(int *) 0x772908);
	return 0;
}
