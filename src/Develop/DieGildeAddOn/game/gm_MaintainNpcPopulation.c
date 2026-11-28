extern unsigned char g_slot_table[2];
extern unsigned char gm_ActiveTownIndex;
extern int cm_PacketDeltaBase;

int __cdecl gm_RandomMod(int);
int __cdecl gm_IsEntityOrphaned(unsigned char*);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CheckEntityAgeLimit(int);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
void __cdecl cm_SendSetAttribute(void);
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
int __cdecl cm_RequestAllocSpieler(int, int, int, int, int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl gm_GetRangeStatId(int, int);
int __cdecl gm_IsNpcEntityState(void*);

/* ADDRESS: GOLDTL 0x004ff8f0 */
/* ADDRESS: GOLDDE 0x004eb300 */
void __cdecl gm_MaintainNpcPopulation(void)
{
	unsigned char* s;
	unsigned char* e;
	unsigned char* p;
	unsigned char* q;
	int active;
	int count;
	int top;
	int passes;
	int rnd2;
	int handle;
	int val;
	int syncVal;
	int initFlag;

	active = 0;
	count = 0;
	top = 0;
	for (s = g_slot_table; (int) s < 0x85a0a0; s += 0x21c) {
		if (*(short*) s != -1 && s[8])
			active++;
	}
	for (s = g_slot_table + 2; (int) s < 0x85a0a2; s += 0x21c) {
		e = s - 2;
		if (*(short*) e == -1 || !s[6] || s[0] != 3)
			continue;
		if ((((gm_RandomMod(4) & 0xffff) + 0x2c <= *(unsigned short*) (s + 8)) || 652.8f <= (float) active)
		    && !s[0x164] && !s[0x166] && !s[0x167]) {
			if (gm_IsEntityOrphaned(e)) {
				val = (int) (-(*(float*) (s + 0x1a) + 1.0f));
				gm_ApplyEntityHealthDelta(*(unsigned short*) e, val);
				active--;
			}
		}
	}
	for (s = g_slot_table + 2; (int) s < 0x85a0a2; s += 0x21c) {
		e = s - 2;
		if (*(short*) e == -1 || s[6] <= 1)
			continue;
		if ((float) active > 652.8f) {
			if (s[0] == 8) {
				p = (unsigned char*) gm_LookupEntityRecordById(*(int*) (e + 0x60));
				q = (unsigned char*) gm_LookupEntityRecordById(*(int*) (e + 0x64));
				if ((!p || p[2] == 0x0f) && (!q || q[2] == 0x0f)) {
					if (gm_IsEntityOrphaned(e)) {
						val = (int) (-(*(float*) (s + 0x1a) + 1.0f));
						gm_ApplyEntityHealthDelta(*(unsigned short*) e, val);
						active--;
					}
					continue;
				}
			}
		}
		if (s[0] == 8 && !gm_CheckEntityAgeLimit(*(unsigned short*) e)) {
			p = (unsigned char*) gm_LookupEntityRecordById(*(int*) (e + 0x60));
			q = (unsigned char*) gm_LookupEntityRecordById(*(int*) (e + 0x64));
			if ((p && p[2] != 0x0f) || (q && q[2] != 0x0f))
				continue;
			syncVal = 3;
			initFlag = 2;
			cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
			cm_AppendCommandSyncField(1, 1, (short) ((int) s - cm_PacketDeltaBase), &syncVal);
			if (s[0xb] < 2)
				cm_AppendCommandSyncField(1, 1, (short) ((int) s - cm_PacketDeltaBase + 0xb), &initFlag);
			cm_SendSetAttribute();
			cm_RequestTransferCurrencyNoKill(*(int*) (e + 4), -1, gm_ActiveTownIndex,
				((gm_RandomMod(0x800) & 0xffff) + 0x800) * initFlag * 0x20);
			count++;
			continue;
		}
		if (gm_IsNpcEntityState(e)) {
			count++;
			if (*(int*) (e + 0x1f0))
				top++;
		}
	}
	if (top < 6 && !(unsigned short) gm_RandomMod(4)) {
		handle = cm_RequestAllocSpieler(0x10, -1, -1, gm_RandomMod(4) + 0x10, -1, 0, 0, 0);
		if (handle != -1) {
			while (!cm_GetCommandStatus(handle)) {
				cm_StepCommandQueue();
			}
		}
		if (cm_GetCommandStatus(handle) == 1) {
			count++;
			handle = (int) cm_GetCommandResult(handle);
			val = ((gm_RandomMod(0x2000) & 0xffff) + 10000) * 0x40;
			cm_RequestTransferCurrencyNoKill(*(int*) (handle + 4), -1, gm_ActiveTownIndex, val);
		}
	}
	if ((float) active <= 652.8f) {
		if (count < 0x1e)
			val = (0x28 - count) / 2;
		else if (count < 0x28)
			val = (gm_RandomMod(2) & 0xffff) + 1;
		else
			val = 0;
		while (val > 0) {
			rnd2 = gm_RandomMod(2);
			passes = gm_RandomMod(0xc);
			handle = cm_RequestAllocSpieler(3, -1, -1, 0x14, -1,
				gm_GetRangeStatId((passes & 0xffff) + 1, (rnd2 & 0xffff) + 1), 0, 2);
			if (handle != -1) {
				while (!cm_GetCommandStatus(handle)) {
					cm_StepCommandQueue();
				}
			}
			if (cm_GetCommandStatus(handle) == 1) {
				syncVal = (gm_RandomMod(0xc) & 0xffff) + 10;
				handle = (int) cm_GetCommandResult(handle);
				passes = gm_RandomMod(0x400);
				cm_RequestTransferCurrencyNoKill(*(int*) (handle + 4), -1, gm_ActiveTownIndex,
					((passes & 0xffff) + 0x400) * 0x40);
				cm_BeginPacketFieldDelta(handle, *(int*) (handle + 4));
				cm_AppendCommandSyncField(1, 1, (short) (handle - cm_PacketDeltaBase + 0x167), &syncVal);
				cm_SendSetAttribute();
			}
			val--;
		}
	}
}
