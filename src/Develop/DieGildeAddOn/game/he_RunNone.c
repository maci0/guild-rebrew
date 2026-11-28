extern char str_he_RunNone_invalid[];
extern char gm_EntityNameField[];


void __cdecl fcn_0064d41a(void*, void*, int, void*);

void __cdecl he_RunNone(void* event)
{
	char buf[0x100];
	unsigned int idx;

	idx = *(unsigned short*) ((char*) event + 8);
	fcn_0064d41a(buf, str_he_RunNone_invalid, *(unsigned char*) event, gm_EntityNameField + idx * 0x21c);
}
