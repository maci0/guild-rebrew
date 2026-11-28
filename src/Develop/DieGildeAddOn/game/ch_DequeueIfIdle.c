


// fcn_0040abd0 — if(!a[0xc]) { fcn_00402480(a[0x14], a[0x30]); fcn_004047a0(a); }.

int __cdecl ch_SetVisible(int, int);
int __cdecl ch_RemoveQueueEntry(void*);

/* ADDRESS: GOLDDE 0x0040a900 */
void __cdecl ch_DequeueIfIdle(char* a)
{
	if (*(int*) (a + 0xc) != 0) {
		return;
	}
	ch_SetVisible(*(int*) (a + 0x14), *(int*) (a + 0x30));
	ch_RemoveQueueEntry(a);
}

