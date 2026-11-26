void __cdecl gm_ExecZunftAufruhr(int, int*);


/* ADDRESS: GOLDTL 0x0049fc30 */
int __cdecl ai_RunZunftAufruhr(int a, char* e)
{
	int msg[5];

	if (*e == 4) {
		msg[0] = 2;
		msg[1] = *(int*) (e + 4);
		msg[2] = *(int*) (e + 0x10);
		gm_ExecZunftAufruhr(a, msg);
		return 0x37;
	}
	return 0;
}
