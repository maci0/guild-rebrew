


void __cdecl cm_EnqueueClientPacket(void*);

void __cdecl cm_SendKillTransporter(int transporter_id)
{
	char buf[0x9c];

	buf[0] = 0x4a;
	*(int*) (buf + 0x10) = transporter_id;
	cm_EnqueueClientPacket(buf);
}
