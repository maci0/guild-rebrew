extern char g_6b5c60[];
int __cdecl sprintf(char* buf, const char* fmt, ...);

char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl fcn_004e9180(char* a1, int a2);
int __cdecl ai_CompareOfficeCandidates(unsigned short* a1, unsigned short* a2, unsigned short* a3, int* a4);
int __cdecl fcn_004aae50(char a1, unsigned short* a2, int* a3, int* a4);

/* ADDRESS: GOLDTL 0x004dc6e0 */
void __cdecl fcn_004dc6e0(char* obj, int* request)
{
	char* entity;
	char* firstEntity;
	char* secondEntity;
	int tmp;
	int r;

	*(int*) (obj + 0x94) = -1;
	*(int*) (obj + 0x98) = -1;
	if (*(int*) (obj + 0x9c) != 0) {
		return;
	}
	entity = gm_LookupEntityRecordById(*(int*) (obj + 0x10));
	if (entity == 0) {
		return;
	}
	if (*(char*) (entity + 0x166) == 0) {
		return;
	}
	if (*(unsigned char*) (entity + 0x1b1) > 0) {
		return;
	}
	if (request[0] == 1) {
		firstEntity = gm_LookupEntityRecordById(request[3]);
		secondEntity = gm_LookupEntityRecordById(request[4]);
		if (firstEntity == 0 || secondEntity == 0) {
			return;
		}
		r = ai_CompareOfficeCandidates((unsigned short*) entity, (unsigned short*) firstEntity, (unsigned short*) secondEntity, &tmp);
		*(int*) (obj + 0x98) = tmp;
		*(int*) (obj + 0x94) = r;
		obj += 0x14;
		sprintf(obj, g_6b5c60);
		return;
	}
	if (request[0] == 2) {
		r = fcn_004e9180(entity, request[2]);
		if (r == 0) {
			return;
		}
		r = fcn_004aae50(*(char*) (request + 1), (unsigned short*) entity, request + 3, &tmp);
		*(int*) (obj + 0x98) = tmp;
		*(int*) (obj + 0x94) = r;
		obj += 0x14;
		sprintf(obj, g_6b5c60);
		return;
	}
}
