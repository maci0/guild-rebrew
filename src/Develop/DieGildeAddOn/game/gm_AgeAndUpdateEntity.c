#include <string.h>

#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern float g_662a94;
extern float flt_0_0;
extern float g_66444c;
extern float g_665370;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char gm_SlotTableKindView[];
extern char gm_EntityIdField[];
extern int gm_QueuedCommandCount;
extern char* cm_PacketDeltaBase;
extern char str_empty[];
extern char g_6964f0[];

int __cdecl gm_CanDeleteEntity(char*);
int __cdecl gv_DecayGravediggerHealth(char*);
void __cdecl cm_RequestKillSpieler(int, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendCommandSyncField(int, int, char*, void*);
void __cdecl cm_SendSetAttribute(void);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_GetBuildingTechEffect(int, int, int);
void __cdecl gm_UpdateEntityPregnancy(char*);

/* ADDRESS: GOLDTL 0x004fe5f0 */
double __cdecl gm_AgeAndUpdateEntity(char* entity)
{
	char msg[0xf8];
	char nb[0x200];
	char c;
	char kind;
	float v10;
	float v15;
	double v11;
	int e;
	int v4;
	unsigned int v5;
	int v6;
	unsigned short w = 0;

	if (*(unsigned short*) entity == 0xffff) {
		return g_662a94;
	}
	if (*(char*) (entity + 2) == 0x0f) {
		v4 = gm_CanDeleteEntity(entity);
		if (v4 != 0) {
			cm_RequestKillSpieler(*(int*) (entity + 4), 1);
			gm_QueuedCommandCount += 1;
		}
		return g_662a94;
	}
	if (*(char*) (entity + 2) == 0x14) {
		v4 = gv_DecayGravediggerHealth(entity);
		if (v4 == 1) {
			c = 0;
			cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
			cm_AppendCommandSyncField(1, 1, (char*) ((int) entity + (8 - (int) cm_PacketDeltaBase)),
			             &c);
			cm_SendSetAttribute();
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = *(int*) (entity + 4);
			*(int*) (msg + 0xc) = -1;

			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;


			*(int*) (msg + 0x58) = *(int*) (entity + 4);
			cm_SendCopyEntityData(msg);
			e = *(int*) (entity + 0x16c);
			if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
				kind = *(char*) (gm_SlotTableKindView +
				                 *(unsigned short*) (e + 0x27) * 0x21c);
				if (kind == 6 || kind == 7) {
					io_FormatTextBuffer(nb, 0x414a, *(unsigned short*) entity, e);
					he_PostEntityMessage(*(int*) (gm_EntityIdField +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             str_empty);
				}
			}
		}
		return flt_0_0;
	}
	v5 = *(int*) (entity + 0x2c);
	if (v5 != 0) {
		if ((v5 & 0xf) != 0) {
			if ((v5 & 0xf) == 1) {
				v5 &= 0xfffffff0;
			} else {
				v5 = (v5 & 0xfffffff0) | ((v5 >> 1) & 7);
			}
		}
		v6 = (v5 >> 4) & 0xf;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xffffff0f;
			} else {
				v5 = (v5 & 0xffffff0f) | ((v5 >> 1) & 0x70);
			}
		}
		v6 = (v5 >> 8) & 0xf;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfffff0ff;
			} else {
				v5 = (v5 & 0xfffff0ff) | ((v5 >> 1) & 0x700);
			}
		}
		v6 = (v5 >> 0xc) & 3;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xffffcfff;
			} else {
				v5 = (v5 & 0xffffcfff) | ((v5 >> 1) & 0x1000);
			}
		}
		v6 = (v5 >> 0xe) & 7;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfffe3fff;
			} else {
				v5 = (v5 & 0xfffe3fff) | ((v5 >> 1) & 0xc000);
			}
		}
		v6 = (v5 >> 0x11) & 7;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfff1ffff;
			} else {
				v5 = (v5 & 0xfff1ffff) | ((v5 >> 1) & 0x60000);
			}
		}
		v6 = (v5 >> 0x14) & 7;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xff8fffff;
			} else {
				v5 = (v5 & 0xff8fffff) | ((v5 >> 1) & 0x300000);
			}
		}
		v6 = (v5 >> 0x17) & 3;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfe7fffff;
			} else {
				v5 = (v5 & 0xfe7fffff) | ((v5 >> 1) & 0x800000);
			}
		}
		v6 = (v5 >> 0x19) & 0xf;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xe1ffffff;
			} else {
				v5 = (v5 & 0xe1ffffff) | ((v5 >> 1) & 0xe000000);
			}
		}
		cm_RequestChangeBits(*(int*) (entity + 4), 0x2c, 4, v5, -1);
		gm_QueuedCommandCount += 1;
	}
	if ((*(unsigned char*) (entity + 0x1cc) & 2) != 0) {
		v10 = *(float*) (entity + 0x1c) -
		      (float) (int) ((gm_RandomMod(0x10) & 0xffff) + 0x11);
		cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x1c, &v10);
		cm_RequestChangeAttribute();
		gm_QueuedCommandCount += 1;
		if (v10 <= 0.0f) {
			c = 0;
			cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
			cm_AppendCommandSyncField(1, 1, (char*) ((int) entity + (8 - (int) cm_PacketDeltaBase)),
			             &c);
			cm_SendSetAttribute();
			gm_QueuedCommandCount += 1;
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = *(int*) (entity + 4);
			*(int*) (msg + 0xc) = -1;


			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;

			*(int*) (msg + 0x58) = *(int*) (entity + 4);
			cm_SendCopyEntityData(msg);
			gm_QueuedCommandCount += 1;
			e = *(int*) (entity + 0x16c);
			if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
				kind = *(char*) (gm_SlotTableKindView +
				                 *(unsigned short*) (e + 0x27) * 0x21c);
				if (kind == 6 || kind == 7) {
					io_FormatTextBuffer(nb, 0x1c51, e, *(unsigned short*) entity);
					he_PostEntityMessage(*(int*) (gm_EntityIdField +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             str_empty);
					gm_QueuedCommandCount += 1;
				}
			}
		}
		return v10;
	}
	v15 = (float) *(unsigned short*) (entity + 0xa);
	if (v15 <= *(float*) (entity + 0x20)) {
		v10 = ((*(float*) (entity + 0x1c) - *(float*) (entity + 0x10)) /
		       *(float*) (entity + 0x20)) *
		          v15 +
		      *(float*) (entity + 0x10);
	} else {
		float adjusted;
		adjusted = *(float*) (entity + 0x14);
		if (*(int*) (entity + 0x170) != 0) {
			v4 = gm_GetBuildingTechEffect(*(int*) (entity + 0x170), 8, 1);
			adjusted = v4 * g_665370 * g_66444c + adjusted;
		}
		v10 = adjusted / *(float*) (entity + 0x1c);
		v10 += *(float*) (entity + 0x1c) - adjusted;
		cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x1c, &v10);
		cm_RequestChangeAttribute();
		gm_QueuedCommandCount += 1;
	}
	v11 = (double) *(int*) (entity + 0x24) + v10;
	v15 = (float) v11;
	if (v11 <= 0.0) {
		c = 0;
		if ((*(unsigned char*) (entity + 0x1cc) & 1) != 0 &&
		    *(char*) (entity + 2) != 6 && *(char*) (entity + 2) != 7) {
			float v14 = 0.0f;
			v10 = 100.0f;
			cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
			cm_AppendPacketFieldDelta(4, 1, 0x1c, &v10);
			cm_AppendPacketFieldDelta(4, 1, 0x24, &v14);
			cm_RequestChangeAttribute();
			gm_QueuedCommandCount += 1;
			cm_RequestChangeBits(*(int*) (entity + 4), 0x1cc, 4, 2, 0);
			gm_QueuedCommandCount = gm_QueuedCommandCount + 1;
			return v10;
		}
		cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
		cm_AppendCommandSyncField(1, 1, (char*) ((int) entity + (8 - (int) cm_PacketDeltaBase)), &c);
		cm_SendSetAttribute();
		gm_QueuedCommandCount += 1;
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x72;
		*(int*) (msg + 8) = *(int*) (entity + 4);
		*(int*) (msg + 0xc) = -1;

		msg[0x36] = 2;
		*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;


		*(int*) (msg + 0x58) = *(int*) (entity + 4);
		cm_SendCopyEntityData(msg);
		gm_QueuedCommandCount += 1;
		e = *(int*) (entity + 0x16c);
		if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
			kind = *(char*) (gm_SlotTableKindView +
			                 *(unsigned short*) (e + 0x27) * 0x21c);
			if (kind == 6 || kind == 7) {
				if ((*(unsigned char*) (entity + 0x1cc) & 4) != 0) {
					io_FormatTextBuffer(nb, 0x4080, entity + 0x30, entity + 0x40,
					             *(unsigned short*) (entity + 0xa));
					he_PostEntityMessage(*(int*) (gm_EntityIdField +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             g_6964f0);
				} else {
					io_FormatTextBuffer(nb, 0x1c51, e, *(unsigned short*) entity);
					he_PostEntityMessage(*(int*) (gm_EntityIdField +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             str_empty);
				}
				gm_QueuedCommandCount += 1;
			}
		}
		return flt_0_0;
	}
	gm_UpdateEntityPregnancy(entity);
	if (v15 > 0.0) {
		v11 = v15;
	} else {
		v11 = 0.0;
	}
	w = *(unsigned short*) (entity + 0xa) + 1;
	cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(2, 1, 10, &w);
	cm_RequestChangeAttribute();
	gm_QueuedCommandCount = gm_QueuedCommandCount + 1;
	return v11;
}
