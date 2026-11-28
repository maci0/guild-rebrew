


extern char g_699aa4[];

unsigned char* __cdecl gm_QueryEntities(int list, int a, int b, int c, int d);
int __cdecl sprintf(char* buf, const char* fmt, ...);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldValue(int a, int b, int c, char* v);
void __cdecl cm_RequestChangeAttribute(void);

void __cdecl gm_ChangeObjektZustand(int id, int delta)
{
	char buf[0x80];
	char v;
	unsigned char* r;

	v = (char) delta;
	r = gm_QueryEntities(0, 2, 7, 1, id);
	if (r == 0) {
		sprintf(buf, g_699aa4, id);
		return;
	}
	if (r[0x12] + delta < 0) {
		v = 0;
	}
	cm_BeginPacketFieldDelta((char*) r, id);
	cm_AppendPacketFieldValue(1, 1, 0x12, &v);
	cm_RequestChangeAttribute();
}
