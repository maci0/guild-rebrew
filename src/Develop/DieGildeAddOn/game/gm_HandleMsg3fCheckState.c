#include <string.h>

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(unsigned short*, int);
int __cdecl gm_ApplyRandomAffliction(unsigned short*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004bb820 */
/* ADDRESS: GOLDDE 0x004a9890 */
int __cdecl gm_HandleMsg3fCheckState(int* request)
{
	char buf[0x400];
	unsigned short* entity;

	entity = gm_LookupEntityRecordById(request[0]);
	if (entity == 0)
		return 1;
	if (gm_HasActiveSpecialObject(entity, 0x290) != 0)
		return 0x400;
	if (gm_ApplyRandomAffliction(entity) == 0)
		return 0x400;
	io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7);
	he_PostEntityMessage(*(int*) (entity + 2), *(int*) (entity + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
