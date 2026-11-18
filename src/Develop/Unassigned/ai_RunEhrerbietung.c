extern int __cdecl gm_LookupEntityRecordById(int id);
extern void __cdecl fcn_004c5420(int, int, int, int, int);
extern void __cdecl fcn_005100f0(int, int);
extern void __cdecl fcn_004c54c0(int, int, int, int);

/* ADDRESS: GOLDTL 0x004abf80 */
int __cdecl ai_RunEhrerbietung(char* entity, char* action)
{
	unsigned short* p;

	p = (unsigned short*) gm_LookupEntityRecordById(*(int*) (action + 4));
	if (p == 0)
		return 0;
	fcn_004c5420(*(int*) (entity + 4), 0x1cc, 4, 0x20, 0);
	fcn_005100f0(*(int*) (entity + 4), -*(int*) (action + 0x10));
	fcn_004c54c0(*(unsigned short*) entity, *p, *(int*) (action + 0x10) * 5, 1);
	return 0x47;
}
