extern unsigned char g_slot_table[2];
extern unsigned char g_773d75;
extern int g_aed32c;

int __cdecl gm_RandomMod(int);
int __cdecl gm_IsEntityOrphaned(unsigned char*);
float __cdecl fcn_004ff210(unsigned short, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CheckEntityAgeLimit(int);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
void __cdecl cm_SendSetAttribute(void);
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
int __cdecl cm_RequestAllocSpieler(int, int, int, int, int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_00507400(int, int);
int __cdecl gm_IsNpcEntityState(void*);

/* ADDRESS: GOLDTL 0x004ff8f0 */
void __cdecl fcn_004ff8f0(void)
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
	int v10;
	int v11;
	int v12;

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
				v10 = (int) (-(*(float*) (s + 0x1a) + 1.0f));
				fcn_004ff210(*(unsigned short*) e, v10);
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
						v10 = (int) (-(*(float*) (s + 0x1a) + 1.0f));
						fcn_004ff210(*(unsigned short*) e, v10);
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
			v11 = 3;
			v12 = 2;
			cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
			cm_AppendCommandSyncField(1, 1, (short) ((int) s - g_aed32c), &v11);
			if (s[0xb] < 2)
				cm_AppendCommandSyncField(1, 1, (short) ((int) s - g_aed32c + 0xb), &v12);
			cm_SendSetAttribute();
			cm_RequestTransferCurrencyNoKill(*(int*) (e + 4), -1, g_773d75,
				((gm_RandomMod(0x800) & 0xffff) + 0x800) * v12 * 0x20);
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
				fcn_00535960();
			}
		}
		if (cm_GetCommandStatus(handle) == 1) {
			count++;
			handle = (int) cm_GetCommandResult(handle);
			v10 = ((gm_RandomMod(0x2000) & 0xffff) + 10000) * 0x40;
			cm_RequestTransferCurrencyNoKill(*(int*) (handle + 4), -1, g_773d75, v10);
		}
	}
	if ((float) active <= 652.8f) {
		if (count < 0x1e)
			v10 = (0x28 - count) / 2;
		else if (count < 0x28)
			v10 = (gm_RandomMod(2) & 0xffff) + 1;
		else
			v10 = 0;
		while (v10 > 0) {
			rnd2 = gm_RandomMod(2);
			passes = gm_RandomMod(0xc);
			handle = cm_RequestAllocSpieler(3, -1, -1, 0x14, -1,
				fcn_00507400((passes & 0xffff) + 1, (rnd2 & 0xffff) + 1), 0, 2);
			if (handle != -1) {
				while (!cm_GetCommandStatus(handle)) {
					fcn_00535960();
				}
			}
			if (cm_GetCommandStatus(handle) == 1) {
				v11 = (gm_RandomMod(0xc) & 0xffff) + 10;
				handle = (int) cm_GetCommandResult(handle);
				passes = gm_RandomMod(0x400);
				cm_RequestTransferCurrencyNoKill(*(int*) (handle + 4), -1, g_773d75,
					((passes & 0xffff) + 0x400) * 0x40);
				cm_BeginPacketFieldDelta(handle, *(int*) (handle + 4));
				cm_AppendCommandSyncField(1, 1, (short) (handle - g_aed32c + 0x167), &v11);
				cm_SendSetAttribute();
			}
			v10--;
		}
	}
}
