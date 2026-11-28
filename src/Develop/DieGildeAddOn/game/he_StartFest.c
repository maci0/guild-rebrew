#pragma pack(push, 1)
typedef struct
{
	int f00;
	int f04;
	int f08;
	short f0c;
} FEST_CLOCK;
#pragma pack(pop)

extern FEST_CLOCK gm_GameTime;

void __cdecl gm_AddTime(FEST_CLOCK* clock, int days, int hours, int mins);
void __cdecl cm_SendCopyEntityData(int packet);
void __cdecl cm_SendSetHE(int mode, char* e);
char* __cdecl gm_LookupEntityRecordById(int entityId);

/* ADDRESS: GOLDTL 0x0054b820 */
/* ADDRESS: GOLDDE 0x00531cc0 */
void __cdecl he_StartFest(char* e)
{
	char buf[0xf8];
	char* found;
	int i;

	*(int*) (e + 0x70) = 0;
	if ((e[0x78] & 4) != 0) {
		return;
	}
	*(FEST_CLOCK*) (e + 0x52) = gm_GameTime;
	gm_AddTime((FEST_CLOCK*) (e + 0x52), 0x18, 0, 0);
	*(short*) (e + 0x56) = 0x14;
	*(int*) (e + 0x58) = 0;
	if (*(int*) (e + 0xc0) == 1) {
		for (i = 0; i < 4; i++) {
			found = gm_LookupEntityRecordById(*(int*) (e + 0xac + i * 4));
			if (found != 0) {
				buf[4] = 0x36;
				*(int*) (buf + 8) = *(int*) (found + 4);
				*(int*) (buf + 0xc) = -1;
				*(int*) (buf + 0x68) = 1;
				*(FEST_CLOCK*) (buf + 0x58) = *(FEST_CLOCK*) (e + 0x52);
				*(int*) (buf + 0x6c) = *(int*) (e + 4);
				if (found[2] == 6 || found[2] == 7) {
					buf[0x36] = 9;
				}
				else {
					buf[0x36] = 1;
				}
				cm_SendCopyEntityData((int) buf);
			}
		}
	}
	cm_SendSetHE(0, e);
}
