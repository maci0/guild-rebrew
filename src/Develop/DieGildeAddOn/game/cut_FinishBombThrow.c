extern int cut_BombSampleBank;
extern unsigned short* cut_ActivePlayerEntity;
extern int g_68b79c;
extern int cm_PacketDeltaBase;

char* __cdecl gm_GetEquippedCombatGear(char*);
void __cdecl d3_SpawnBombObject(char*);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);
unsigned short* __cdecl gm_FindEntityActiveItem(char*);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);

/* ADDRESS: GOLDTL 0x004d4d80 */
void __cdecl cut_FinishBombThrow(char* a0)
{
	char* obj;
	char* rec;
	char* e;
	int v;

	obj = *(char**) (a0 + 0x180);
	rec = gm_GetEquippedCombatGear(obj);
	d3_SpawnBombObject((char*) (*(int*) (*(int*) (obj + 0x184) + 0x34) + 0x4c));
	sb_PlayVoice(cut_BombSampleBank, (char*) 0x68be64, 3, 0x3f, 0x7f, 0, 0);
	if (*(int*) ((char*) cut_ActivePlayerEntity + 4) == g_68b79c) {
		if (*(int*) (rec + 0x58) == 1 || *(int*) (rec + 0x58) == 2) {
			e = (char*) gm_FindEntityActiveItem(obj);
			if (e != 0) {
				v = -1;
				cm_BeginPacketFieldDelta(e, *(int*) (e + 2));
				cm_AppendPacketFieldValue(4, 1, (int) e - cm_PacketDeltaBase + 0x20, &v);
				cm_RequestChangeAttribute();
			}
		}
	}
}
