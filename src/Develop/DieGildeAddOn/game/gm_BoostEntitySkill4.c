int __cdecl io_FormatTextBuffer(void *buf, int len);
int __cdecl d2_OpenEntityPicker(char *a0, char *a1);
int __cdecl gm_LookupEntityRecordById(int value);
int __cdecl gm_IncreaseEntitySkill(unsigned char *e, int idx);

/* ADDRESS: GOLDTL 0x005dd130 */
/* ADDRESS: GOLDDE 0x005be6d0 */
int __cdecl gm_BoostEntitySkill4(char *entity, int *request)
{
	char buf[0x100];
	int r;

	if (entity[2] == 6) {
		io_FormatTextBuffer(buf, 0x9d);
		r = d2_OpenEntityPicker(entity, buf);
		if (r != 0) {
			gm_IncreaseEntitySkill((unsigned char *) r, 4);
			return 1;
		}
		return 0;
	} else {
		r = gm_LookupEntityRecordById(request[1]);
		if (r != 0) {
			gm_IncreaseEntitySkill((unsigned char *) r, 4);
			return 1;
		}
		return 0;
	}
}
