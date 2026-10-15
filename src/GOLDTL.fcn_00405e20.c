

extern void* g_14d0020[];
extern int g_67a370;
extern int g_6b8010;
extern int g_6b7fac;
extern int g_6b5c24;
extern unsigned int g_67529c;
extern int g_6b5c30;
extern int g_67531c;
extern char* g_6b5c54;
extern char* g_6b5c58;
extern char g_1043370[];
extern char g_6756a0[];
extern char g_67540c[];
extern char g_67567c[];

void __cdecl fcn_004058f0(char* m);
void __cdecl fcn_004045c0(char* e);
void __cdecl fcn_00435500(char* a, char* b);
int __cdecl fcn_004054b0(char* e);
int __cdecl fcn_00405d70(char* self, char** out, float range);
char* __cdecl fcn_00402610(char* obj);
void __cdecl fcn_00405c70(char* src, float* dst);
char __cdecl fcn_0045b990(char* map, float* pos, int* col, int* row, float* height);
char* __cdecl fcn_0040c120(char* e, int kind, int a, int b, int c);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
char* __cdecl fcn_00404dc0(char* e, char* name, int flag);
#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_004027b0(void);

int __cdecl fcn_00405e20(void)
{
	char** p;
	char* t;
	char* map;
	unsigned short f;
	int row;
	int col;
	float height;
	float pos[4];
	char* list[32];

	g_6b5c24 = g_6b7fac;
	g_6b5c30 = 0;
	if (g_67531c == 0) {
		return 0;
	}
	if (g_6b5c54 != (char*) g_67a370 || g_6b5c58 != (char*) g_67a370) {
		if (*(char**) g_1043370 != 0 && g_6b5c54 != (char*) g_67a370) {
			fcn_004058f0(*(char**) g_1043370);
			g_6b5c54 = (char*) g_67a370;
		}
		if (g_67a370 != 0 && g_6b8010 != 0 && *(char**) ((char*) g_67a370 + 0xb0) != 0 && g_6b5c58 != (char*) g_67a370) {
			fcn_004058f0(*(char**) ((char*) g_67a370 + 0xb0));
			g_6b5c58 = (char*) g_67a370;
		}
	}
	for (p = (char**) g_14d0020; (int) p < (int) (g_14d0020 + 0x300); p++) {
		if (*p == 0 || (*(*p + 0x8c) & 4) != 0) {
			continue;
		}
		t = *(char**) (*p + 0x128);
		fcn_004045c0(*p);
		if (t != 0) {
			if ((*(*p + 0x8d) & 0x20) != 0 && *(char**) (*p + 0x70) != 0) {
				fcn_00435500(*(char**) (*(char**) (*p + 0x34) + 0x1ec) + 0xf4, *(char**) (*(char**) (*p + 0x70) + 0x68));
				*(char**) (*p + 0x70) = 0;
				*(*p + 0x8d) &= 0xdf;
			}
			fcn_004054b0(*p);
		} else if (*(char**) (*p + 0x88) == (char*) g_67a370 && (f = *(unsigned short*) (*p + 0x8c), (f & 0x32) == 0) &&
			   (f & 0x8000) == 0 && *(int*) (*p + 0x124) == 0) {
			if (fcn_00405d70(*p, list, 20.0f) != 0) {
				map = fcn_00402610(*p);
				fcn_00405c70(*(char**) (*p + 0x34) + 0x4c, pos);
				if (fcn_0045b990(map, pos, &col, &row, &height)) {
					fcn_0040c120(*p, 0x2d, col, row, g_6b8010);
				}
			}
		} else {
			*(*p + 0x8c) &= 0xf7;
		}
		if (*(int*) (*p + 0x124) != 0) {
			ch_UpdateAttachedModelPosition(*p, 0);
		}
		if (*(int*) (*p + 0x22c) != 0) {
			ch_Updatelowpoly(*p);
		}
		if (t == 0 && (char*) g_67a370 == *(char**) (*p + 0x88) && g_6b8010 != 0 && *(int*) (*p + 0x70) == 0) {
			f = *(unsigned short*) (*p + 0x8c);
			if ((f & 0x1000) != 0 && (f & 2) == 0 &&
			    (*(*(char**) (*(char**) (*p + 0x34) + 0x1ec) + 0x163d) & 0x40) == 0) {
				if ((f & 0x10) != 0) {
					fcn_00404dc0(*p, g_6756a0, 0);
					if (*(char**) (*p + 0x70) != 0) {
						*(*(char**) (*p + 0x70) + 0x6c) = 0;
						*(*(char**) (*p + 0x70) + 0x6d) &= 0xef;
						*(*p + 0x8d) |= 0x20;
					} else {
						*(*p + 0x8d) &= 0xef;
					}
				} else {
					fcn_00404dc0(*p, g_67540c, 0);
					if (*(char**) (*p + 0x70) != 0) {
						*(*(char**) (*p + 0x70) + 0x6c) = 0;
						*(*(char**) (*p + 0x70) + 0x6d) &= 0xef;
						*(*p + 0x8d) |= 0x20;
					} else {
						*(*p + 0x8d) &= 0xef;
					}
				}
			}
		}
		if (*p != 0 && *(int*) (*p + 0x88) != *(int*) (*(char**) (*p + 0x34) + 0x20c)) {
			fcn_0041d9e0(g_67567c);
		}
	}
	fcn_004027b0();
	g_67529c = g_6b7fac;
	return 1;
}
