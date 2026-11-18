#include "entity_record.h"










unsigned short __cdecl gm_RandomMod(int n);
#include "client_packet_builder.h"
void __cdecl fcn_004c4570(int a, int b, int c, int* flags);
void __cdecl fcn_004c5360(void);

/* ADDRESS: GOLDTL 0x00495890 */
void __cdecl fcn_00495890(void)
{
	int flags;
	int i;

	flags = 1;
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_state != 3) {
			continue;
		}
		flags |= gm_RandomMod(2) ? 2 : 0;
		flags |= gm_RandomMod(3) ? 4 : 0;
		flags |= gm_RandomMod(3) ? 8 : 0;
		flags |= gm_RandomMod(2) ? 0x10 : 0;
		fcn_004c4510((char*) &((ENTITY_RECORD*)g_7f4ca0)[i], ((ENTITY_RECORD*)g_7f4ca0)[i].entity_id);
		fcn_004c4570(4, 1, 0x1e8, &flags);
		fcn_004c5360();
	}
}
