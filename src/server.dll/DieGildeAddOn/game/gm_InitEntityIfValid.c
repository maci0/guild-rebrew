/* gm_InitEntityIfValid - proper C */

// FUNCTION: SERVER 0x10017f90
// SIZE: 23

int __cdecl amt_ClearEntityLinks(int arg1); /* 0x1000b990 */

/* Initialises an entity when it is a valid (non-empty) record. */

void __cdecl gm_InitEntityIfValid(short* entity)
{
	if (entity != 0 && *(unsigned short*) entity != 0xffff)
		amt_ClearEntityLinks(entity);
}
