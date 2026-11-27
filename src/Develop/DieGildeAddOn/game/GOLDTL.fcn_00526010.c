


int __cdecl gm_QueryEntitySum(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int  __cdecl d2_ShowModalMessageBox(void*, int);

int __cdecl gm_CheckEntityStock(void* entity, int amount, int item_id)
{
	char buf[0x40];

	if (gm_QueryEntitySum(*(int*) ((char*) entity + 0x178), item_id) < amount && amount != 0) {
		io_FormatTextBuffer(buf, 0x75, (unsigned char) item_id);
		d2_ShowModalMessageBox(buf, 0);
		return 0;
	}
	return 1;
}
