/* Polls the device through vtable slot 0x28, updates the key tables and then
   runs the key repeat timer.
   DATA TODO: 0x14673cc, 0x1468410, 0x14681c0, 0x1468420, 0x6310c0, 0x6310e0,
   0x631098 and 0x6333d8 have no Gold definition, so raw addresses stay. */
/* ADDRESS: GOLD 0x004112e0 */
void __cdecl fcn_004112e0(void)
{
	int state[5];
	int dev;
	int hr;
	unsigned char cur;
	unsigned char held;
	unsigned int t;

	*(unsigned char*) 0x1468410 = 0;
	state[0] = 1;
top:
	dev = *(int*) 0x14673cc;
	hr = ((int (__stdcall*) (int, int, int*, int*, int)) (*(int**) dev)[0x28 / 4])
		(dev, 0x10, state + 1, state, 0);
	if (hr < 0 || state[0] == 0) {
		goto done;
	}
	if (state[2] & 0x80) {
		if (*(int*) 0x6310c0 != 0) {
			goto top;
		}
		*(unsigned char*) 0x1468410 = (unsigned char) state[1];
		*(unsigned char*) (0x14681c0 + (unsigned char) state[1]) = 1;
	} else {
		if (*(int*) 0x6310c0 != 0) {
			goto top;
		}
		*(unsigned char*) (0x14681c0 + (unsigned char) state[1]) = 0;
		*(unsigned char*) (0x1468420 + (unsigned char) state[1]) = 1;
	}
	goto top;
done:
	cur = *(unsigned char*) 0x1468410;
	if (cur != 0) {
		t = *(unsigned int*) 0x6333d8 + 9;
		held = cur;
		*(unsigned char*) 0x6310e0 = held;
		*(unsigned int*) 0x631098 = t;
	} else {
		t = *(unsigned int*) 0x631098;
		held = *(unsigned char*) 0x6310e0;
	}
	if (held != 0) {
		if (cur == 0 && *(unsigned char*) (0x14681c0 + *(unsigned char*) 0x6310e0) != 0
		    && *(unsigned int*) 0x6333d8 > t + 5) {
			*(unsigned char*) 0x1468410 = held;
			*(unsigned int*) 0x631098 = *(unsigned int*) 0x6333d8;
		}
		if (*(unsigned char*) (0x14681c0 + *(unsigned char*) 0x6310e0) == 0) {
			*(unsigned char*) 0x6310e0 = 0;
			*(unsigned int*) 0x631098 = 0x4e729fff;
		}
	}
}
