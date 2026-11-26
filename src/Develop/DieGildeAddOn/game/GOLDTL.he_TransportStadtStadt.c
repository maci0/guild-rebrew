#include <stdio.h>
extern int g_774650;

extern unsigned short *__cdecl gm_StartFilteredEntitySearch(int, ...);
extern void *__cdecl gm_FindRecordById(int);
extern int __cdecl fcn_00505340(unsigned char *);
extern char *__cdecl fcn_0055d630(char *);
extern void __cdecl fcn_0055d6e0(char *, char *);
extern void *__cdecl fcn_00502cd0(int, int, ...);
extern char *__cdecl fcn_00402610(char *);
extern char __cdecl fcn_0045b990(char *, float *, int *, int *, float *);
extern void __cdecl d3_SelectSceneContext(int, int);
extern void __cdecl d3_TransformPoint(char *, char *, float *);
extern void __cdecl fcn_004c5d20(int, int);
extern void __cdecl cm_RequestWalkOnPath(int, int, int, int);
extern int __cdecl cm_RequestMoveObjekt(int, int, int);
extern void __cdecl cm_RequestChangeBits(int, int, int, int, int);
extern int __cdecl fcn_004c5620(int, char *);
extern int __cdecl CompareVector3WithinTolerance(float *, float *, float);
extern char *__cdecl fcn_005049a0(unsigned char *);
extern void __cdecl io_FormatTextBuffer(char *, int, ...);
extern void __cdecl he_MessageBoxQuickjump(int, int, char *, int, int, int, int,
					   int, int);

/* ADDRESS: GOLDTL 0x0055df80 */
void __cdecl he_TransportStadtStadt(char *transportEvent)
{
	char *v3;
	char *v4;
	char *v5;
	char *v6;
	char *v8;
	int v7;
	int v10;
	int v19;
	int l_saved;
	int l_a;
	int l_b;
	float l_pos[3];
	float l_c;
	float l_v13[3];
	char l_text[1024];
	char l_msg[1032];
	unsigned short v1;

	v3 = (char *)gm_StartFilteredEntitySearch(1, 0, 0x44);
	gm_StartFilteredEntitySearch(1, 0, 0x45);
	v4 = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(transportEvent + 0xb0));
	v5 = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(transportEvent + 0xb4));
	if (*(int *)(transportEvent + 0xc4) == *(int *)(v4 + 1) && !*(char *)(transportEvent + 0xd0)) {
		l_saved = *(int *)0x6b8010;
		d3_SelectSceneContext(0, 1);
		v6 = fcn_0055d630(*(char **)(v5 + 0x61));
		if (!v6)
			v6 = *(char **)(v5 + 0x61);
		d3_TransformPoint(v6, v6 + 0x4c, l_pos);
		if (fcn_00505340((unsigned char *)v4))
			v6 = (char *)fcn_00502cd0(*(int *)(v3 + 0x5d), 1, 1, *(int *)(transportEvent + 0xac));
		else
			v6 = (char *)fcn_00502cd0(*(int *)(v4 + 0x5d), 1, 1,
						  *(int *)(transportEvent + 0xac));
		if (!v6)
			v6 = (char *)gm_FindRecordById(*(int *)(transportEvent + 0xac));
		if (v6) {
			v19 = *(int *)(v6 + 0x3b);
			fcn_0055d6e0(transportEvent, v6);
			v7 = (int)fcn_00402610((char *)v19);
			*(char *)(transportEvent + 0xd0) = 1;
			fcn_0045b990((char *)v7, l_pos, &l_a, &l_b, &l_c);
			*(int *)(transportEvent + 0xd8) = *(int *)&l_pos[0];
			*(int *)(transportEvent + 0xdc) = *(int *)&l_pos[1];
			*(int *)(transportEvent + 0xe0) = *(int *)&l_pos[2];
			if (!fcn_00505340((unsigned char *)v4)) {
				if (*(int *)(v4 + 0x61)) {
					v8 = fcn_0055d630(*(char **)(v4 + 0x61));
					if (!(v8)) {
						v8 = *(char **)(v5 + 0x61);
						*(int *)&l_v13[0] = *(int *)(v8 + 0x4c);
						*(int *)&l_v13[1] = *(int *)(v8 + 0x50);
						*(int *)&l_v13[2] = *(int *)(v8 + 0x54);
					} else {
						d3_TransformPoint(v8, v8 + 0x4c, l_v13);
					}
				}
				fcn_004c5d20(*(int *)(v6 + 2), 1);
			}
			cm_RequestWalkOnPath(*(int *)(v6 + 2), l_a, l_b, 0);
			if (!fcn_00505340((unsigned char *)v4))
				*(int *)(transportEvent + 0xec) = cm_RequestMoveObjekt(*(int *)(v3 + 1),
								   *(int *)(transportEvent + 0xb0),
								   *(int *)(transportEvent + 0xac));
		} else {
			fcn_00502cd0(0, 2, 7, 1, *(int *)(transportEvent + 0xac));
		}
		d3_SelectSceneContext(l_saved, 1);
		*(int *)(transportEvent + 0xc4) = *(int *)(v3 + 1);
		return;
	}
	if (*(int *)(transportEvent + 0xc4) != *(int *)(v3 + 1))
		return;
	v4 = (char *)fcn_00502cd0(*(int *)(v3 + 0x5d), 1, 1, *(int *)(transportEvent + 0xac));
	if (!v4)
		v4 = (char *)fcn_00502cd0(0, 2, 7, 1, *(int *)(transportEvent + 0xac));
	if (v4) {
		v6 = *(char **)(v4 + 0x3b);
		fcn_0055d6e0(transportEvent, v4);
		v8 = *(char **)(v6 + 0x128);
		if (v8 && v8[9] == '-') {
			*(int *)(transportEvent + 0xd8) = *(int *)(v8 + 0x134);
			*(int *)(transportEvent + 0xdc) = *(int *)(v8 + 0x138);
			*(int *)(transportEvent + 0xe0) = *(int *)(v8 + 0x13c);
		}
		if (*(int *)(v6 + 0x128))
			return;
		v8 = *(char **)(v6 + 0x34);
		if (!CompareVector3WithinTolerance((float *)(v8 + 0x4c), (float *)(transportEvent + 0xd8),
				  300.0f) &&
		    *(int *)(transportEvent + 0xd4) <= 6)
			return;
		cm_RequestChangeBits(*(int *)(v4 + 2), 0x13, 1, 0, 0x40);
		if (!fcn_00505340((unsigned char *)v5)) {
			fcn_004c5d20(*(int *)(v4 + 2), 0);
			*(int *)(transportEvent + 0xec) = cm_RequestMoveObjekt(*(int *)(v5 + 1),
							   *(int *)(v3 + 1),
							   *(int *)(transportEvent + 0xac));
		}
		if (fcn_00505340((unsigned char *)v5))
			io_FormatTextBuffer(l_text, 0x1c43);
		else
			io_FormatTextBuffer(l_text, 0x1c44, v5);
		v10 = g_774650;
		if ((*(int *)(0x7e35c0 + v10 * 8) != 0x5ba910 ||
		     (*(int *)0x7746c4 != (int)v5 &&
		      (!fcn_00505340((unsigned char *)v5) || !*(int *)0x7746cc ||
		       (*(int *)0x7746c4 != (int)v5 &&
			(!fcn_00505340((unsigned char *)v5) ||
			 ((v1 = *(unsigned short *)*(int *)0x7746cc,
			   (v1 < 0x92 || v1 > 0x97) && v1 != 0x2db))))))) &&
		    !(*(unsigned char *)(v4 + 0x20) & 1) &&
		    !*(char *)(transportEvent + 0xf2)) {
			v8 = fcn_005049a0((unsigned char *)v5);
			if (v8)
				he_MessageBoxQuickjump(*(int *)(0x7f4ca4 +
								*(unsigned short *)(transportEvent + 8) * 0x21c),
						       *(int *)(v4 + 2), l_text, 0, 0x608,
						       *(int *)(v5 + 1), *(int *)(v8 + 2), 0, 0);
			else
				he_MessageBoxQuickjump(*(int *)(0x7f4ca4 +
								*(unsigned short *)(transportEvent + 8) * 0x21c),
						       *(int *)(v4 + 2), l_text, 0, 0x608,
						       *(int *)(v5 + 1), -1, 0, 0);
		}
		*(int *)(transportEvent + 0xc4) = *(int *)(transportEvent + 0xb4);
		*(int *)(transportEvent + 0x84) = fcn_004c5620(3, transportEvent);
		if (!*(int *)(v6 + 0x128) && *(int *)(transportEvent + 0xd4) > 6 &&
		    !CompareVector3WithinTolerance((float *)(*(int *)(v6 + 0x34) + 0x4c),
				  (float *)(transportEvent + 0xd8), 100.0f))
			sprintf(l_msg, (char *)0x6a6380,
				*(int *)(0x14a6558 + *(unsigned char *)v5 * 0x38));
	} else {
		__asm { int 3 }
		fcn_00502cd0(0, 2, 7, 1, *(int *)(transportEvent + 0xac));
	}
}
