int __cdecl ai_RunSecretRoomDomizilAttack(int a1, char* p, int a3);
int __cdecl ai_RunSecretRoomMode1(int a1, char* p, int a3);
int __cdecl ai_RunSecretRoomMode2(int a1, char* p, int a3);
int __cdecl ai_RunSecretRoomSpyKiller(int a1, char* p, int a3);

/* ADDRESS: GOLD 0x0048eaa0 */
/* ADDRESS: GOLDTL 0x0048e050 */
int __cdecl ai_RunSecretRoom(int a1, char* p, int a3)
{
	switch (*(int*) (p + 0x10)) {
	case 0:
		return ai_RunSecretRoomDomizilAttack(a1, p, a3) ? 0x41 : 0;
	case 1:
		return ai_RunSecretRoomMode1(a1, p, a3) ? 0x41 : 0;
	case 2:
		return ai_RunSecretRoomMode2(a1, p, a3) ? 0x41 : 0;
	case 3:
		return ai_RunSecretRoomSpyKiller(a1, p, a3) ? 0x41 : 0;
	}
	return 0;
}
