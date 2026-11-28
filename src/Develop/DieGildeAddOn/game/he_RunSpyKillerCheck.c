#include <math.h>

extern char gm_EntitySlotTable[];

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl cm_SendCancelCharacterActions(int a1);
int __cdecl ch_StartMovement(int who, int key, int target, char* name, int mode, char* text);
float __cdecl gm_GetEntitySkill(char* entity, int idx);
int __cdecl cm_SendSetHE(char a1, unsigned char* e);
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);
void __cdecl he_PostEntityMessage();

/* ADDRESS: GOLDTL 0x00577e70 */
unsigned int __cdecl he_RunSpyKillerCheck(char* assassin, char* action, char* spyAction)
{
	char message[1024];
	char* v3;
	char* ent;
	unsigned char* v1;
	unsigned char* v8;
	unsigned short slot;
	float dx;
	double dy;
	double dz;
	float t0;
	float t1;

	if (spyAction != 0 && *spyAction == 0x18) {
		if (*(unsigned int*) (action + 0xc4) < 0x14) {
			*(unsigned int*) (action + 0xc4) = *(unsigned int*) (action + 0xc4) + 1;
			ent = gm_LookupEntityRecordById(*(unsigned int*) (spyAction + 0xd8));
			if (ent != 0 && *(int*) (ent + 0x184) != 0) {
				v3 = (char*) *(int*) (*(int*) (assassin + 0x184) + 0x34);
				ent = (char*) *(int*) (*(int*) (ent + 0x184) + 0x34);
				dx = *(float*) (v3 + 0x4c) - *(float*) (ent + 0x4c);
				dy = (double) *(float*) (v3 + 0x50) - *(float*) (ent + 0x50);
				dz = (double) *(float*) (v3 + 0x54) - *(float*) (ent + 0x54);
				if (sqrt(dz * dz + dy * dy + (double) dx * dx) < 1850.0f) {
				v1 = (unsigned char*) (0x7f4ca0 + *(unsigned short*) (spyAction + 8) * 0x21c);
				v8 = (unsigned char*) gm_LookupEntityRecordById(*(unsigned int*) (spyAction + 0xc4));
				t0 = (float) (*(int*) (spyAction + 0xe8) + 1) * 0.5f;
				t1 = (float) (*(int*) (action + 0xc0) + 1) * 0.5f;
				if (gm_GetEntitySkill((char*) v1, 2) + t0 < gm_GetEntitySkill((char*) v8, 2) + t1) {
					*(unsigned int*) (spyAction + 0x84) = cm_SendSetHE(-1, (unsigned char*) spyAction);
					io_FormatTextBuffer(message, (char*) 0x4028, *(unsigned short*) v8);
					he_PostEntityMessage(*(unsigned int*) (v1 + 4), -1, message, 1, 0x5fb, (char*) 0x6a7ea8);
					io_FormatTextBuffer(message, (char*) 0x4029, *(unsigned short*) v1);
					he_PostEntityMessage(*(unsigned int*) (v8 + 4), -1, message, 1, 0x5fb, (char*) 0x6a7ea8);
					return 1;
				}
				} else {
					if (*(int*) (spyAction + 0xb4) != *(int*) (action + 0xac)) {
						*(int*) (action + 0xac) = *(int*) (spyAction + 0xb4);
						cm_SendCancelCharacterActions(*(unsigned int*) (assassin + 4));
						ch_StartMovement(*(unsigned int*) (assassin + 4), *(unsigned int*) (spyAction + 0xb4), -1, 0, 1, (char*) 0x6a7e3c);
					}
					return 0;
				}
			}
		}
	}
	return 0xffffffff;
}
