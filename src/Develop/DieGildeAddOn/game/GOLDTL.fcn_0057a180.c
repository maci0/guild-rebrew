extern char g_773d75;

char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl fcn_0050d320(char* entity, char season);
void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
void __cdecl fcn_00546190(void* u);
float __cdecl fcn_004ff210(unsigned short id, int delta);

/* Releases every played sound of the behaviour when its counter ran out. */
/* ADDRESS: GOLDTL 0x0057a180 */
void __cdecl fcn_0057a180(char* a0)
{
	char* entity;
	char* sound;
	int* p;
	int i;
	int found;
	int count;

	if (*(int*) (a0 + 0x70) < -2) {
		return;
	}
	if (*(int*) (a0 + 0x70) > 0) {
		return;
	}
	entity = gm_LookupEntityRecordById(*(int*) (a0 + 0xc));
	if (entity != 0) {
		count = fcn_0050d320(entity, g_773d75);
		if (count > *(int*) (a0 + 0xac)) {
			fcn_004c5150(-1, *(int*) (entity + 4), g_773d75, *(int*) (a0 + 0xac));
			fcn_00546190(a0);
			return;
		}
		found = 0;
		p = (int*) (entity + 0x68);
		for (i = 0; i < 5; i++) {
			if (*p != -1) {
				sound = gm_LookupEntityRecordById(*p);
				if (sound != 0) {
					fcn_004ff210(*(unsigned short*) sound, -1001);
					found = 1;
				}
			}
			p++;
		}
		if (found == 0) {
			fcn_004ff210(*(unsigned short*) entity, -1001);
		}
		fcn_00546190(a0);
	}
	fcn_00546190(a0);
}
