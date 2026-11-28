/* Index of a 20-byte entry within the owner's array for its kind
 * (owner + 8 + kind * 4 holds the four array bases); -1 for other kinds. */

/* ADDRESS: GOLD 0x004ef6b0 */
int __cdecl fcn_004ef6b0(int owner, void* item)
{
	if (*(int*) item == 0)
		return ((int) item - *(int*) (owner + 8)) / 20;
	if (*(int*) item == 1)
		return ((int) item - *(int*) (owner + 0xc)) / 20;
	if (*(int*) item == 2)
		return ((int) item - *(int*) (owner + 0x10)) / 20;
	if (*(int*) item == 3)
		return ((int) item - *(int*) (owner + 0x14)) / 20;
	return -1;
}
