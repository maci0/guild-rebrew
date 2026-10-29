/* ADDRESS: GOLD 0x005f38a0 */
extern int g_677680;
/* ADDRESS: GOLD 0x00631130 */
extern char* g_6b5d08;



void __cdecl fcn_00418d70(char*);

/* ADDRESS: GOLD 0x00417990 */
void __cdecl fcn_00418f50(void)
{
	int i;
	char* p;

	for (i = 0; i < g_677680; i++) {
		p = g_6b5d08 + i * 0x54;
		if (*(int*) (p + 0x38) != 0) {
			fcn_00418d70(p);
		}
	}
}
