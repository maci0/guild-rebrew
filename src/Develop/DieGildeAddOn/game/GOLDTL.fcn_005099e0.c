#include <string.h>

int __cdecl fcn_004f4650(void *, void **, void **);
int __cdecl fcn_004f1790(void *, void *);
void __cdecl fcn_004f22e0(void *, void *, int, int);
void __cdecl fcn_004f2a10(void *, void *, int, int);
void *__cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl cm_SendSetGebBesitzer(int, int, int);
int __cdecl gm_CalculateGebaeudeValue(void *, int);
void __cdecl cm_SendCopyEntityData(void *);
void *__cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_SumTreasury(void *);
void __cdecl cm_RequestMoveCredits(int, int, int, int);
int __cdecl gm_WalkEntityChain(int);
void __cdecl cm_BeginPacketFieldDelta(void *, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, void *);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void *);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_PostEntityMessage(int, int, int, int, int, char *);

extern int gm_CityEntity;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern int g_aed32c;

/* ADDRESS: GOLDTL 0x005099e0 */
void __cdecl gm_TransferEntityBuildings(void *fromEntity, void *toEntity)
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
	if (fcn_004f4650(fromEntity, &ent, &found)) {
		fcn_004f22e0(fromEntity, ent, *(int *) found,
					 fcn_004f1790(*(void **) ((char *) ent + 0x65), found));
		if (toEntity != 0 && toEntity != (void *) gm_CityEntity
			&& *(int *) ((char *) fromEntity + 4) == *(int *) ((char *) found + 4)) {
			fcn_004f2a10(toEntity, ent, *(int *) found,
						 fcn_004f1790(*(void **) ((char *) ent + 0x65), found));
		}
	}
	ent = gm_StartFilteredEntitySearch(1, 4, *(unsigned short *) fromEntity);
	while (ent != 0) {
		type = gm_GetBuildingTypeCategory(*(unsigned char *) ent);
		if (type == 2) {
			cm_SendSetGebBesitzer(*(int *) ((char *) ent + 1), *(int *) ((char *) gm_CityEntity + 4),
						 *(int *) ((char *) gm_CityEntity + 4));
		} else {
			cm_SendSetGebBesitzer(*(int *) ((char *) ent + 1), *(int *) ((char *) toEntity + 4),
						 *(int *) ((char *) toEntity + 4));
			flag = 1;
		}
		if (toEntity == (void *) gm_CityEntity && type != 2 && (((unsigned char *) ent)[0x5a] & 1) == 0) {
			pkt[4] = 0x1b;
			*(int *) (pkt + 8) = *(int *) ((char *) gm_CityEntity + 4);
			*(int *) (pkt + 0xc) = -1;
			pkt[0x36] = 2;
			*(int *) (pkt + 0x58) = *(int *) ((char *) ent + 1);
			*(int *) (pkt + 0x5c) = gm_CalculateGebaeudeValue(ent, *((signed char *) ent + 0x5c));
			cm_SendCopyEntityData(pkt);
			it = (void *) 0x7f4ca4;
			do {
				if (*(int *) ((char *) it + 0x168) == (int) ent) {
					int recipient = *(int *) it;
					if (recipient != *(int *) ((char *) fromEntity + 4)) {
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
						cm_SendCopyEntityData(pkt);
					}
				}
				it = (void *) ((char *) it + 0x21c);
			} while ((int) it < (int) 0x85a0a4);
		}
		list[cnt] = ent;
		cnt++;
		ent = gm_FindNextFilteredEntity();
	}
	if (toEntity != (void *) gm_CityEntity) {
		val = gm_SumTreasury(fromEntity);
		i = 4 + (*((unsigned char *) fromEntity + 2) == 5);
		cm_RequestMoveCredits(*(int *) ((char *) toEntity + 4), -1, g_773d75, val);
		type = gm_WalkEntityChain(*(unsigned short *) fromEntity);
		cm_BeginPacketFieldDelta(toEntity, *(int *) ((char *) toEntity + 4));
		cm_AppendPacketFieldValue(4, 1, (int) toEntity - g_aed32c + 0x1a8, &type);
		if (flag != 0
			&& (*((unsigned char *) toEntity + 2) == 3 || *((unsigned char *) toEntity + 2) == 8
				|| *((unsigned char *) toEntity + 2) == 9)) {
			cm_AppendPacketFieldDelta(1, 1, (int) toEntity - g_aed32c + 2, &i);
		}
		cm_RequestChangeAttribute();
	}
	if (*((unsigned char *) toEntity + 2) != 6 && *((unsigned char *) toEntity + 2) != 7) {
		if ((*((unsigned char *) fromEntity + 2) == 5 || *((unsigned char *) fromEntity + 2) == 6
			 || *((unsigned char *) fromEntity + 2) == 7)
			&& toEntity == (void *) gm_CityEntity) {
			it = (void *) 0x7f4ca4;
			do {
				if ((*((unsigned char *) it - 2) == 6 || *((unsigned char *) it - 2) == 7)
					&& *(int *) it != *(int *) ((char *) fromEntity + 4)) {
					io_FormatTextBuffer(buf, 0x1c4d, *(unsigned short *) fromEntity);
					he_PostEntityMessage(*(int *) it, -1, (int) buf, 0, 0x5fe, "_NACHRICHTEN_HS_70");
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
					&& *(int *) ((i * 0x87 + j) * 4 + 0x7f4cfc) == *(int *) ((char *) fromEntity + 4)) {
					io_FormatTextBuffer(buf, 0x1c4e, *(unsigned short *) fromEntity);
					he_PostEntityMessage(*(int *) (i * 0x21c + 0x7f4ca4), -1, (int) buf, 0, 0x5f4,
								 "_NACHRICHTEN_HS_63");
					i = 0x300;
				}
				j++;
			} while (j < 8);
			i++;
		} while (i < 0x300);
		return;
	}
	io_FormatTextBuffer(out, 0x1c4a, *(unsigned short *) fromEntity);
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
	val = gm_SumTreasury(fromEntity);
	io_FormatTextBuffer(buf, 0x1c4c, val);
	strcat(out, buf);
	he_PostEntityMessage(*(int *) ((char *) toEntity + 4), -1, (int) out, 1, 0x5ff, "_NACHRICHTEN_HS_63");
}
