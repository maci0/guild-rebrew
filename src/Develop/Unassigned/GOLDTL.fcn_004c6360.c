


void __cdecl cm_EnqueueClientPacket(void*);

#pragma pack(push, 1)

typedef struct
{
	int a;
	short b;
	char c;
} ASSIGN_OFFICE_CMD;
// SIZE 0x7

#pragma pack(pop)

void __cdecl cm_SendAssignOffice(ASSIGN_OFFICE_CMD* body)
{
	char buf[0x9c];

	buf[0] = 0x44;
	*(ASSIGN_OFFICE_CMD*) (buf + 0x10) = *body;
	cm_EnqueueClientPacket(buf);
}
