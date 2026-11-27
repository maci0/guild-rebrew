unsigned short __cdecl gm_RandomMod(unsigned short n);
double __cdecl gm_RandomFloat01(void);
void __cdecl gm_RandomizeIntArray(unsigned int n, int *arr);
int __cdecl gm_IsNpcEntityState(void *p);
void __cdecl amt_CalcOfficeHolderAges(int n, int *out, unsigned char *src);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_FlushCommandQueue(void);
void __cdecl cm_PollCommandQueue(void);
void __cdecl fcn_004c4b00(void);
char *__cdecl cm_GetCommandResult(int h);
int __cdecl cm_RequestAllocSpieler(int, int, int, int, int, int, int, int);
void __cdecl cm_RequestMoveCredits(int, int, int, int);
void __cdecl cm_BeginPacketFieldDelta(char *p, int h);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void *p);
int __cdecl cm_RequestChangeBits(int, int, int, int, int);
int __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_StepCommandQueue(void);
int __cdecl cm_GetCommandStatus(int h);
int __cdecl amt_FindOfficeSlotByKey(unsigned char c, void *out);
int __cdecl amt_GetRoleTemplate(int i, void *out);
int __cdecl amt_FindOfficeSlotByType(int i, void *out);
int __cdecl amt_AssignOfficeHolder(int a, void *p, int b);
void __cdecl fcn_004fee50(void *p, int h);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_GetRangeStatId(int, int);
int __cdecl fcn_0050b750(int, int);
void __cdecl amt_SpawnHistoricalOfficeHolders(void);
extern unsigned char g_773d75;
/* ADDRESS: GOLDTL 0x00511c60 */
int __cdecl fcn_00511c60(void)
{
	int v36;
	int v42;
	char v37;
	int v38;
	int v49;
	float v50;
	int v25[50];
	int v35[6];
	int v39[6];
	int v41[6];
	int shuffledIds[30];
	int v40[6];
	int v34[6];
	int v26[30];
	int v33[30];
	int i;
	int n;
	int m;
	int k;
	char *p;

	v25[1] = 0x12;
	v25[5] = 0x12;
	v25[9] = 0x12;
	v25[16] = 0x1d;
	v25[17] = 0x1d;
	v25[22] = 0x1d;
	v25[23] = 0x1d;
	v25[26] = 0x1d;
	v25[2] = 0x14;
	v25[6] = 0x14;
	v25[10] = 0x14;
	m = 0;
	v25[0] = 0x10;
	v25[3] = 0x18;
	v25[4] = 0x10;
	v25[7] = 0x18;
	v25[8] = 0x10;
	v25[11] = 0x18;
	v25[12] = 0x16;
	v25[13] = 0x18;
	v25[14] = 0x19;
	v25[15] = 0x1b;
	v25[18] = 0x16;
	v25[19] = 0x18;
	v25[20] = 0x19;
	v25[21] = 0x1b;
	v25[24] = 0x19;
	v25[25] = 0x1b;
	v25[27] = 0x20;
	v25[28] = 0x22;
	v25[29] = 0x25;
	gm_RandomizeIntArray(4, &v25[0]);
	gm_RandomizeIntArray(4, &v25[4]);
	gm_RandomizeIntArray(4, &v25[8]);
	gm_RandomizeIntArray(6, &v25[12]);
	gm_RandomizeIntArray(6, &v25[18]);
	gm_RandomizeIntArray(6, &v25[24]);
	for (i = 0; i < 0x1e; i++) {
		v26[i] = 0;
	}
	for (i = 0; i < 0x1e; i++) {
		v25[i] = v25[i] + gm_RandomMod(3);
	}
	n = 0;
	p = (char *) 0x7f4ca0;
	while ((int) p < 0x85a0a0) {
		if (n >= 0x1e) {
			break;
		}
		if (n >= 0xc) {
			break;
		}
		if (gm_IsNpcEntityState(p) != 0) {
			if (*(unsigned char *) (p + 2) != 5) {
				v26[n] = (int) p;
				n++;
			}
		}
		p += 0x21c;
	}
	for (i = 0; i < 0x1e; i++) {
		shuffledIds[i] = i;
	}
	gm_RandomizeIntArray(4, &shuffledIds[0]);
	gm_RandomizeIntArray(4, &shuffledIds[4]);
	gm_RandomizeIntArray(4, &shuffledIds[8]);
	gm_RandomizeIntArray(6, &shuffledIds[12]);
	gm_RandomizeIntArray(6, &shuffledIds[18]);
	gm_RandomizeIntArray(6, &shuffledIds[24]);
	amt_CalcOfficeHolderAges(0x1e - n, &v33[n], (unsigned char *) &shuffledIds[n]);
	i = n;
	while (i < 0x1e) {
		cm_BeginCommandSync();
		if (m < 3 && i > 0xc) {
			if ((gm_RandomMod(4) & 0xffff) == 0) {
				k = cm_RequestAllocSpieler(0x10, -1, -1, 0x10, -1, 0, 0, 0);
				m++;
			} else {
				k = cm_RequestAllocSpieler(3, -1, -1, 0x10, -1,
						 (unsigned char) v33[i], 0, 2);
			}
		} else {
			k = cm_RequestAllocSpieler(3, -1, -1, 0x10, -1,
					 (unsigned char) v33[i], 0, 2);
		}
		cm_EndCommandSync();
		while (cm_AreQueuedCommandsDone() == 0) {
			cm_FlushCommandQueue();
			cm_PollCommandQueue();
			fcn_004c4b00();
		}
		v26[i] = (int) cm_GetCommandResult(k);
		i++;
	}
	v25[30] = 1;
	v25[31] = 3;
	v25[32] = 3;
	v25[35] = 5;
	v25[33] = 4;
	v25[34] = 4;
	v25[36] = 6;
	v25[37] = 7;
	v25[38] = 7;
	v25[39] = 7;
	v25[41] = 10000;
	v25[42] = 10000;
	v25[40] = 1000;
	v25[43] = 20000;
	v25[44] = 20000;
	v25[45] = 40000;
	v25[46] = 50000;
	v25[47] = 60000;
	v25[48] = 80000;
	v25[49] = 100000;
	for (i = 0; i < 0x1e; i++) {
		v36 = 2;
		amt_FindOfficeSlotByKey(shuffledIds[i], v34);
		amt_GetRoleTemplate(v34[2] & 0xff, v35);
		v37 = (char) (int) ((float) gm_RandomMod(0x2a) +
				    (float) ((v35[2] & 0xff) / 3 + 1) *
				    21.0f);
		v36 = (gm_RandomMod(2) & 0xffff) + v25[(v35[2] & 0xff) + 30];
		v38 = v25[(v35[2] & 0xff) + 40];

		v49 = fcn_0050b750(v38 - (int) ((float) v38 *
						 gm_RandomFloat01() *
						 -0.5f),
				   *(unsigned char *) 0x773d75);
		p = (char *) v26[i];
		cm_RequestMoveCredits(*(int *) (p + 4), -1, g_773d75,
			     v49);
		cm_BeginPacketFieldDelta(p, *(int *) (p + 4));
		cm_AppendPacketFieldDelta(1, 1, 0xd, &v36);
		if (*(unsigned char *) (p + 2) == 3) {
			cm_AppendPacketFieldDelta(1, 1, 0x84, &v37);
			if ((gm_RandomMod(2) & 0xffff) != 0) {
				v50 = gm_RandomFloat01() + 1.0f;
				v42 = (gm_RandomMod(8) & 0xffff) + 1;
				v38 = (int) ((float) v42 * v50 *
					     (float) v49 *
					     0.01f);
				cm_AppendPacketFieldDelta(4, 1, 0x1ac, &v38);
			}
		}
		cm_RequestChangeAttribute();
		fcn_004fee50(p, v25[i] & 0xffff);
		k = amt_AssignOfficeHolder((unsigned char) shuffledIds[i], p, 0xff);
		if (k != -1) {
			while (cm_GetCommandStatus(k) == 0) {
				cm_StepCommandQueue();
			}
		}
		if (*(unsigned char *) (p + 0x166) == 0x18 ||
		    *(unsigned char *) (p + 0x166) == 0x1a ||
		    *(unsigned char *) (p + 0x166) == 0x1b) {
			k = cm_RequestChangeBits(*(int *) (p + 4), 0x1cc, 4, 0x80, 0);
		} else if (*(unsigned char *) (p + 0x166) == 0x16 ||
			   *(unsigned char *) (p + 0x166) == 0x17 ||
			   *(unsigned char *) (p + 0x166) == 0x19) {
			k = cm_RequestChangeBits(*(int *) (p + 4), 0x1cc, 4, 0x40, 0);
		} else {
			k = -1;
		}
		if (k != -1) {
			while (cm_GetCommandStatus(k) == 0) {
				cm_StepCommandQueue();
			}
		}
		if (*(unsigned char *) (p + 0x166) == 0x1b) {
			amt_FindOfficeSlotByType(0x25, v39);
			amt_AssignOfficeHolder(v39[0], p, 0xff);
		} else if (*(unsigned char *) (p + 0x166) == 0x1a) {
			amt_FindOfficeSlotByType(0x24, v40);
			amt_AssignOfficeHolder(v40[0], p, 0xff);
		} else if (*(unsigned char *) (p + 0x166) == 0x19) {
			amt_FindOfficeSlotByType(0x23, v41);
			amt_AssignOfficeHolder(v41[0], p, 0xff);
		}
	}
	do {
		m = 0;
		i = 0;
		n = 0;
		do {
			if (n != 0 && m != 0) {
				break;
			}
			p = (char *) v26[i];
			if (*(unsigned short *) (p + 0xa) >= 0x17) {
				if (m == 0 &&
				    *(unsigned char *) (p + 9) == 0 &&
				    *(int *) (p + 0x5c) == -1) {
					m = (int) p;
				} else if (n == 0 &&
					   *(unsigned char *) (p + 9) == 1 &&
					   *(int *) (p + 0x5c) == -1) {
					n = (int) p;
				}
			}
			i++;
		} while (i < 0x1e);
		if (m == 0 || n == 0) {
			break;
		}
		v42 = *(unsigned short *) (n + 0xa) - 0x12;
		v36 = n;
		cm_BeginPacketFieldDelta((char *) m, *(int *) (m + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x5c, (char *) (n + 4));
		cm_RequestChangeAttribute();
		cm_BeginPacketFieldDelta((char *) n, *(int *) (n + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x5c, (char *) (m + 4));
		cm_RequestChangeAttribute();
		if (v42 > 5) {
			if ((gm_RandomMod(2) & 0xffff) != 0) {
				k = *(unsigned char *) (m + 0x164);
			} else {
				k = *(unsigned char *) (n + 0x164);
			}
			k = gm_GetRangeStatId(gm_MapEntityStatRange(k), 1);
			v38 = 2;
			k = cm_RequestAllocSpieler(8, *(int *) (m + 4), *(int *) (n + 4),
					 v42, -1, k, 0, 2);
			if (k != -1) {
				while (cm_GetCommandStatus(k) == 0) {
					cm_StepCommandQueue();
				}
			}
			p = cm_GetCommandResult(k);
			k = gm_RandomMod(0x400);
			cm_RequestMoveCredits(*(int *) (p + 4), -1,
				     g_773d75,
				     ((k & 0xffff) + 0x200) << 5);
			cm_BeginPacketFieldDelta(p, *(int *) (p + 4));
			cm_AppendPacketFieldDelta(1, 1, 0xd, &v38);
			cm_RequestChangeAttribute();
		}
		k = gm_RandomMod(0x20);
		cm_RequestCopyEntityData(*(int *) (m + 4), *(int *) (n + 4),
			     (k & 0xffff) + 0x60, 0);
		k = gm_RandomMod(0x20);
		k = cm_RequestCopyEntityData(*(int *) (n + 4), *(int *) (m + 4),
				 (k & 0xffff) + 0x60, 0);
		if (k != -1) {
			while (cm_GetCommandStatus(k) == 0) {
				cm_StepCommandQueue();
			}
		}
	} while (v36 != 0);
	i = 8;
	do {
		v36 = 2;
		v42 = (gm_RandomMod(9) & 0xffff) + 1;
		k = gm_GetRangeStatId((gm_RandomMod(2) & 0xffff) + 1,
				 (gm_RandomMod(0xc) & 0xffff) + 1);
		k = cm_RequestAllocSpieler(3, -1, -1, gm_RandomMod(4) + 0xf, -1, k, 0, 0);
		if (k != -1) {
			while (cm_GetCommandStatus(k) == 0) {
				cm_StepCommandQueue();
			}
		}
		p = cm_GetCommandResult(k);
		k = gm_RandomMod(0x400);
		cm_RequestMoveCredits(*(int *) (p + 4), -1, g_773d75,
			     ((k & 0xffff) + 0x200) << 5);
		cm_BeginPacketFieldDelta(p, *(int *) (p + 4));
		cm_AppendPacketFieldDelta(1, 1, 0xd, &v36);
		cm_AppendPacketFieldDelta(1, 1, 0x167, &v42);
		cm_RequestChangeAttribute();
		k = gm_GetRangeStatId((gm_RandomMod(2) & 0xffff) + 1,
				 (gm_RandomMod(0xc) & 0xffff) + 1);
		k = cm_RequestAllocSpieler(3, -1, -1, gm_RandomMod(4) + 0xe, -1, k, 0, 0);
		if (k != -1) {
			while (cm_GetCommandStatus(k) == 0) {
				cm_StepCommandQueue();
			}
		}
		p = cm_GetCommandResult(k);
		k = gm_RandomMod(0x400);
		cm_RequestMoveCredits(*(int *) (p + 4), -1, g_773d75,
			     ((k & 0xffff) + 0x200) << 5);
		cm_BeginPacketFieldDelta(p, *(int *) (p + 4));
		cm_AppendPacketFieldDelta(1, 1, 0xd, &v36);
		cm_AppendPacketFieldDelta(1, 1, 0x167, &v42);
		cm_RequestChangeAttribute();
		i--;
	} while (i != 0);
	amt_SpawnHistoricalOfficeHolders();
	return 1;
}
