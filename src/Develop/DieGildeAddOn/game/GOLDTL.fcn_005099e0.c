#include <string.h>

int __cdecl fcn_004f4650(void *, void **, void **);
int __cdecl fcn_004f1790(void *, void *);
void __cdecl fcn_004f22e0(void *, void *, int, int);
void __cdecl fcn_004f2a10(void *, void *, int, int);
void *__cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl fcn_004c5f60(int, int, int);
int __cdecl gm_CalculateGebaeudeValue(void *, int);
void __cdecl fcn_004c5530(void *);
void *__cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_SumTreasury(void *);
void __cdecl fcn_004c5150(int, int, int, int);
int __cdecl gm_WalkEntityChain(int);
void __cdecl cm_BeginPacketFieldDelta(void *, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, void *);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void *);
void __cdecl fcn_004c5360(void);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl fcn_00545d40(int, int, int, int, int, char *);

extern int gm_CityEntity;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern unsigned char g_773d75;
extern int g_aed32c;

/* ADDRESS: GOLDTL 0x005099e0 */
void __cdecl fcn_005099e0(void *arg1, void *arg2)
{
	void *ent;
	int cnt;
	void *found;
	int type;
	int i;
	int flag;
	unsigned char pkt[0xf8];
	char buf[0x800];
	void *list[0x80];
	char out[0x1000];
	void *it;
	int val;
	int j;

	cnt = 0;
	flag = 0;
	if (fcn_004f4650(arg1, &ent, &found)) {
		fcn_004f22e0(arg1, ent, *(int *) found,
					 fcn_004f1790(*(void **) ((char *) ent + 0x65), found));
		if (arg2 != 0 && arg2 != (void *) gm_CityEntity
			&& *(int *) ((char *) arg1 + 4) == *(int *) ((char *) found + 4)) {
			fcn_004f2a10(arg2, ent, *(int *) found,
						 fcn_004f1790(*(void **) ((char *) ent + 0x65), found));
		}
	}
	ent = gm_StartFilteredEntitySearch(1, 4, *(unsigned short *) arg1);
	while (ent != 0) {
		type = gm_GetBuildingTypeCategory(*(unsigned char *) ent);
		if (type == 2) {
			fcn_004c5f60(*(int *) ((char *) ent + 1), *(int *) ((char *) gm_CityEntity + 4),
						 *(int *) ((char *) gm_CityEntity + 4));
		} else {
			fcn_004c5f60(*(int *) ((char *) ent + 1), *(int *) ((char *) arg2 + 4),
						 *(int *) ((char *) arg2 + 4));
			flag = 1;
		}
		if (arg2 == (void *) gm_CityEntity && type != 2 && (((unsigned char *) ent)[0x5a] & 1) == 0) {
			pkt[4] = 0x1b;
			*(int *) (pkt + 8) = *(int *) ((char *) gm_CityEntity + 4);
			*(int *) (pkt + 0xc) = -1;
			pkt[0x36] = 2;
			*(int *) (pkt + 0x58) = *(int *) ((char *) ent + 1);
			*(int *) (pkt + 0x5c) = gm_CalculateGebaeudeValue(ent, *((signed char *) ent + 0x5c));
			fcn_004c5530(pkt);
			it = (void *) 0x7f4ca4;
			do {
				if (*(int *) ((char *) it + 0x168) == (int) ent) {
					int recipient = *(int *) it;
					if (recipient != *(int *) ((char *) arg1 + 4)) {
						memset(pkt, 0, 0xf8);
						pkt[4] = 0x31;
						*(int *) (pkt + 8) = *(int *) ((char *) gm_CityEntity + 4);
						*(int *) (pkt + 0x2c) = g_7f4c04;
						*(int *) (pkt + 0xc) = *(int *) ((char *) ent + 1);
						*(int *) (pkt + 0x28) = gm_GameTime;
						pkt[0x36] = 1;
						*(int *) (pkt + 0x30) = g_7f4c08;
						*(unsigned short *) (pkt + 0x34) = g_7f4c0c;
						*(int *) (pkt + 0x58) = recipient;
						fcn_004c5530(pkt);
					}
				}
				it = (void *) ((char *) it + 0x21c);
			} while ((int) it < (int) 0x85a0a4);
		}
		list[cnt] = ent;
		cnt++;
		ent = gm_FindNextFilteredEntity();
	}
	if (arg2 != (void *) gm_CityEntity) {
		val = gm_SumTreasury(arg1);
		i = 4 + (*((unsigned char *) arg1 + 2) == 5);
		fcn_004c5150(*(int *) ((char *) arg2 + 4), -1, g_773d75, val);
		type = gm_WalkEntityChain(*(unsigned short *) arg1);
		cm_BeginPacketFieldDelta(arg2, *(int *) ((char *) arg2 + 4));
		cm_AppendPacketFieldValue(4, 1, (int) arg2 - g_aed32c + 0x1a8, &type);
		if (flag != 0
			&& (*((unsigned char *) arg2 + 2) == 3 || *((unsigned char *) arg2 + 2) == 8
				|| *((unsigned char *) arg2 + 2) == 9)) {
			cm_AppendPacketFieldDelta(1, 1, (int) arg2 - g_aed32c + 2, &i);
		}
		fcn_004c5360();
	}
	if (*((unsigned char *) arg2 + 2) != 6 && *((unsigned char *) arg2 + 2) != 7) {
		if ((*((unsigned char *) arg1 + 2) == 5 || *((unsigned char *) arg1 + 2) == 6
			 || *((unsigned char *) arg1 + 2) == 7)
			&& arg2 == (void *) gm_CityEntity) {
			it = (void *) 0x7f4ca4;
			do {
				if ((*((unsigned char *) it - 2) == 6 || *((unsigned char *) it - 2) == 7)
					&& *(int *) it != *(int *) ((char *) arg1 + 4)) {
					io_FormatTextBuffer(buf, 0x1c4d, *(unsigned short *) arg1);
					fcn_00545d40(*(int *) it, -1, (int) buf, 0, 0x5fe, "_NACHRICHTEN_HS_70");
				}
				it = (void *) ((char *) it + 0x21c);
			} while ((int) it < (int) 0x85a0a4);
			return;
		}
		i = 0;
		do {
			j = 0;
			do {
				if ((*(unsigned char *) (i * 0x21c + 0x7f4ca2) == 6
					 || *(unsigned char *) (i * 0x21c + 0x7f4ca2) == 7)
					&& *(int *) ((i * 0x87 + j) * 4 + 0x7f4cfc) == *(int *) ((char *) arg1 + 4)) {
					io_FormatTextBuffer(buf, 0x1c4e, *(unsigned short *) arg1);
					fcn_00545d40(*(int *) (i * 0x21c + 0x7f4ca4), -1, (int) buf, 0, 0x5f4,
								 "_NACHRICHTEN_HS_63");
					i = 0x300;
				}
				j++;
			} while (j < 8);
			i++;
		} while (i < 0x300);
		return;
	}
	io_FormatTextBuffer(out, 0x1c4a, *(unsigned short *) arg1);
	if (cnt != 0) {
		io_FormatTextBuffer(buf, 0x1c4b);
		strcat(out, buf);
		for (i = 0; i < cnt; i++) {
			if (i >= 6) {
				if (i < cnt) {
					io_FormatTextBuffer(buf, 0xb6, cnt - i);
					strcat(out, buf);
				}
				break;
			}
			if (((((unsigned char **) list)[i])[0x5a] & 1) == 0) {
				io_FormatTextBuffer(buf, (int) "%1G$A", list[i]);
			}
			strcat(out, buf);
		}
	}
	val = gm_SumTreasury(arg1);
	io_FormatTextBuffer(buf, 0x1c4c, val);
	strcat(out, buf);
	fcn_00545d40(*(int *) ((char *) arg2 + 4), -1, (int) out, 1, 0x5ff, "_NACHRICHTEN_HS_63");
}
