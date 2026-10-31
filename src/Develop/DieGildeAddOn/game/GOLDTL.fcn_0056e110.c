


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_00546190(char*);

void __cdecl he_AllocDiePlayer(char* e)
{
	char* p;

	p = gm_LookupEntityRecordById(*(int*) (e + 0xac));
	if (p == 0) {
		ReportClientMessage("he_AllocDiePlayer: player not found!");
		fcn_00546190(e);
		return;
	}
	p[8] = 0;
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
}
