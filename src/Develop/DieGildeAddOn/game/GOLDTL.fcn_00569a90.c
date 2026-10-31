extern int g_100f884;
extern int g_100f1dc;
extern int g_aed32c;
extern unsigned char g_773d75;

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00500cb0(void*, void*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, int, char*, int, int);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c4670(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c51a0(int, int, char, int);
int __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_004c6b20(int, int, int);
int __cdecl fcn_00567170(unsigned short*, int*, int*, int);
int __cdecl gm_GetEntityTableEntry(char*);
int __cdecl fcn_004c5620(int, void*);
void __cdecl fcn_00546190(char*);
int __cdecl he_fn_Handlung(void);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00569a90 */
void __cdecl fcn_00569a90(char* a)
{
	unsigned short* v3;
	unsigned short* v4;
	int v[3];
	char buf[0x200];
	int pkt;
	int entity;

	v3 = gm_LookupEntityRecordById(*(int*) (a + 0xac));
	v4 = gm_LookupEntityRecordById(*(int*) (a + 0xb0));
	if (v3 != 0 && v4 != 0) {
		if (*(char*) ((char*) v3 + 2) != 6 && *(char*) ((char*) v3 + 2) != 7) {
			if (*(int*) (a + 0x70) == 0 || *(int*) (a + 0x70) == 2) {
				if (fcn_00500cb0(a + 0x52, (void*) (char*) 0x7f4c00) > 0)
					return;
				*(int*) (a + 0x70) = 2;
			}
		}
		switch (*(int*) (a + 0x70)) {
		case 0:
			fcn_00545670(a, 0, 0, "locations\\diebesgilde\\Diebesgilde_Loesegeld_Msg", 0x5ec);
			d2_SetForm(*(int*) (*(int*) (a + 0x74) + 8), 0);
			io_AppendText(0x19cb, *(int*) (a + 0xb4));
			(*(int*) (a + 0x70))++;
			return;
		case 1:
			if (g_100f884 != *(int*) (*(int*) (a + 0x74) + 8))
				return;
			if (g_100f1dc == -1)
				return;
			if (g_100f1dc == 2) {
				v[2] = -1;
				pkt = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0x10));
				io_FormatTextBuffer(buf, 0x19d4, *(unsigned short*) v3,
				    *(int*) (a + 0xb4), *(unsigned short*) v3);
				fcn_00545d40(*(int*) ((char*) v4 + 4), *(int*) ((char*) v4 + 4),
				    buf, 0, 0x5fa, 0);
				if (pkt != 0) {
					fcn_004c4510((char*) pkt, *(int*) (pkt + 1));
					fcn_004c4570(4, 1,
					    (pkt - g_aed32c) + 0x65, (void*) &v[2]);
					fcn_004c5360();
				}
				fcn_004c6b20(*(int*) ((char*) v3 + 4),
				    -(int) *(unsigned char*) ((char*) v3 + 0x1b1), 0);
				fcn_004c51a0(*(int*) ((char*) v4 + 4), *(int*) ((char*) v3 + 4),
				    (char) g_773d75, *(int*) (a + 0xb4));
				if (*(int*) ((char*) v3 + 0x184) != 0
				    && fcn_00567170(v3, &v[1], &v[0], 0) != 0)
					fcn_004c5da0(*(int*) ((char*) v3 + 4), v[1], v[0], 0, 0,
					    "L\xf6segeld");
				if (pkt != 0) {
					entity = gm_GetEntityTableEntry((char*) v4);
					fcn_004c4510((char*) pkt, *(int*) (pkt + 1));
					fcn_004c4670(4, 1, 0x69, (void*) (a + 0xb4));
					fcn_004c5360();
					if (entity != 0)
						*(int*) (entity + 0x20) += *(int*) (a + 0xb4);
					*(int*) (pkt + 0x4d) += *(int*) (a + 0xb4);
				}
				*(volatile int*) (a + 0x70) = 3;
				*(int*) (a + 0x70) = -1;
				return;
			}
			if (g_100f1dc == 1) {
				pkt = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0x10));
				if (pkt == 0)
					break;
				io_FormatTextBuffer(buf, 0x19d5, *(unsigned short*) v3);
				entity = *(int*) ((char*) v4 + 4);
				he_MessageBoxQuickjump(entity, entity, buf, 0, 0x5f0, *(int*) (pkt + 1),
				    -1, 0, 0);
			}
			*(int*) (a + 0x70) = -1;
			return;
		case 2:
			if ((unsigned short) gm_RandomMod(100) > 0x14) {
				v[1] = -1;
				pkt = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0x10));
				if (pkt == 0)
					break;
				io_FormatTextBuffer(buf, 0x19d4, *(unsigned short*) v3,
				    *(int*) (a + 0xb4), *(unsigned short*) v3);
				fcn_00545d40(*(int*) ((char*) v4 + 4), *(int*) (a + 0x10),
				    buf, 0, 0x5fa, 0);
				fcn_004c4510((char*) pkt, *(int*) (pkt + 1));
				fcn_004c4570(4, 1, (pkt - g_aed32c) + 0x65, (void*) &v[1]);
				fcn_004c5360();
				fcn_004c6b20(*(int*) ((char*) v3 + 4),
				    -(int) *(unsigned char*) ((char*) v3 + 0x1b1), 0);
				fcn_004c51a0(*(int*) ((char*) v4 + 4), *(int*) ((char*) v3 + 4),
				    (char) g_773d75, *(int*) (a + 0xb4));
				if (*(int*) ((char*) v3 + 0x184) != 0
				    && fcn_00567170(v3, &v[2], &v[0], 0) != 0)
					fcn_004c5da0(*(int*) ((char*) v3 + 4), v[2], v[0], 0, 0,
					    "L\xf6segeld");
				fcn_004c4510((char*) pkt, *(int*) (pkt + 1));
				fcn_004c4670(4, 1, 0x69, (void*) (a + 0xb4));
				fcn_004c5360();
				entity = gm_GetEntityTableEntry((char*) v4);
				if (entity != 0)
					*(int*) (entity + 0x20) += *(int*) (a + 0xb4);
				*(int*) (pkt + 0x4d) += *(int*) (a + 0xb4);
				*(int*) (a + 0x70) = 3;
				return;
			}
			io_FormatTextBuffer(buf, 0x19d5, *(unsigned short*) v3);
			entity = *(int*) ((char*) v4 + 4);
			fcn_00545d40(entity, entity, buf, 0, 0x5fb, 0);
			fcn_00546190(a);
			return;
		case 3:
			pkt = fcn_005463a0(1, 0, 0x3d);
			if (pkt != 0) {
				while (*(int*) (pkt + 0xac) != *(int*) (a + 0xac)) {
					pkt = he_fn_Handlung();
					if (pkt != 0)
						continue;
					fcn_00546190(a);
					return;
				}
				*(int*) (a + 0x84) = fcn_004c5620(-1, a);
			}
			break;
		case -2:
		case -1:
			break;
		default:
			return;
		}
	}
	fcn_00546190(a);
}
