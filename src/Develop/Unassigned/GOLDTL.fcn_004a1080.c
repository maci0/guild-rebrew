char* __cdecl gm_LookupEntityRecordById(int a1);
void __cdecl cm_SendCopyEntityData(int a1);
void __cdecl cm_RequestChangeBits(int a1, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x004a1080 */
int __cdecl ai_RunStudium(char* a0, char* a1, char* a2)
{
	char packet[0xf8];
	char* entity;

	if (*(unsigned char*) a1 == 7 && *(unsigned char*) a2 == 0x0e) {
		entity = gm_LookupEntityRecordById(0);
		if (entity != 0) {
			*(unsigned char*) (packet + 0x36) = 0x12;
			*(unsigned char*) (packet + 0x04) = 0x5f;
			*(int*) (packet + 0x08) = *(int*) (entity + 4);
			*(int*) (packet + 0x58) = *(int*) (a0 + 4);
			*(unsigned char*) (packet + 0x64) = *(unsigned char*) (a2 + 4);
			*(int*) (packet + 0x0c) = -1;
			*(unsigned char*) (packet + 0x65) = *(unsigned char*) (a2 + 0x10);
			*(int*) (packet + 0x60) = *(int*) (a1 + 0x10);
			cm_SendCopyEntityData((int) packet);
			cm_RequestChangeBits(*(int*) (entity + 4), 0x1c8, 4, 0x10000, 0);
			return 0x3b;
		}
	}
	return 0;
}
