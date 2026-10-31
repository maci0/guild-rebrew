char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ahm_CheckFlag(char*);
int __cdecl fcn_004eeb10(char*, int);
int __cdecl ahm_ApplyColorComponent(char*, int);
int __cdecl fcn_004eec60(char*, int, char*);
int __cdecl fcn_004eebb0(char*, int);
int __cdecl ahm_SlotClearMatch(char*, int, char*);
int __cdecl fcn_004ee8c0(char*, int, char*);

/* ADDRESS: GOLDTL 0x004cdb90 */
int __cdecl fcn_004cdb90(char* cfg, char* out)
{
	char* s;
	int r;

	if (out) {
		out[0] = 2;
		out[1] = 0;
		*(int*)(out + 6) = 0;
	}
	s = (char*) gm_LookupEntityRecordById(*(int*)(cfg + 0x14));
	if (!s)
		return -1;
	if (!ahm_CheckFlag(s))
		return -2;

	switch (*(unsigned int*)(cfg + 0x10)) {
	case 0x61535263:
		r = fcn_004eeb10(cfg + 0x10, *(int*)(*(char**)(s + 0x16c) + 0x65));
		break;
	case 0x61437353:
		r = ahm_ApplyColorComponent(cfg + 0x10, *(int*)(*(char**)(s + 0x16c) + 0x65));
		break;
	case 0x46697245:
		r = fcn_004eec60(cfg + 0x10, *(int*)(*(char**)(s + 0x16c) + 0x65), *(char**)(s + 0x16c));
		break;
	case 0x61536d53:
		r = fcn_004eebb0(cfg + 0x10, *(int*)(*(char**)(s + 0x16c) + 0x65));
		break;
	case 0x61736452:
		r = ahm_SlotClearMatch(cfg + 0x10, *(int*)(*(char**)(s + 0x16c) + 0x65), *(char**)(s + 0x16c));
		break;
	case 0x61616452:
		r = fcn_004ee8c0(cfg + 0x10, *(int*)(*(char**)(s + 0x16c) + 0x65), *(char**)(s + 0x16c));
		break;
	default:
		return -3;
	}

	if (out && r)
		out[0] = 1;
	return 0;
}
