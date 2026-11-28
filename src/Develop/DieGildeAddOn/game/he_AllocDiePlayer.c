





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/Units/Error/error_message.h"
void __cdecl he_FreeAction(char*);

void __cdecl he_AllocDiePlayer(char* e)
{
	char* p;

	p = gm_LookupEntityRecordById(*(int*) (e + 0xac));
	if (p == 0) {
		ReportClientMessage("he_AllocDiePlayer: player not found!");
		he_FreeAction(e);
		return;
	}
	p[8] = 0;
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
}
