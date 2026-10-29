char* __cdecl ch_AttachMotion(char* obj, int kind);
void __cdecl fcn_004311a0(char* node, char* an, int from, int to, int flags);
void __cdecl fcn_00435500(char* o, char* name);

/* Finish the animation parked on the object. A fresh clip is started when
 * none is running and the event has no follow-up; otherwise the clip is
 * closed and the call returns -1. The flag-clear path reloads the clip
 * into its own local and branches to the byte return on the nonzero
 * side: that is what keeps the null test, the far jne back to the byte
 * return, and a separate copy of the -1 epilogue. */

/* ADDRESS: GOLDTL 0x00404f60 */
int __cdecl fcn_00404f60(char* ev)
{
	char* obj;
	char* an;
	char* an2;
	char* frames;

	obj = *(char**) (ev + 0x14);
	an = *(char**) (obj + 0x70);
	if (an == 0) {
		if (*(int*) (ev + 0xc) == 0) {
			*(char**) (obj + 0x70) = ch_AttachMotion(obj, (unsigned char) ev[9]);
byte_ret:
			return (unsigned char) ev[0x10];
		}
		an = *(char**) (obj + 0x70);
		if (an == 0) {
			goto fail;
		}
	}
	if ((an[0x6d] & 0x20) != 0) {
		frames = *(char**) (an + 0x68);
		if (frames[0x169] == 0 && (an[0x70] & 3) != 0) {
			fcn_004311a0(*(char**) (obj + 0x34), an, 0, *(int*) an, 3);
		}
		if ((obj[0x8c] & 2) != 0) {
			goto clear_anim;
		}
		fcn_00435500(*(char**) (*(char**) (*(char**) (ev + 0x14) + 0x34) + 0x1ec) + 0xf4, *(char**) (*(char**) (obj + 0x70) + 0x68));
		*(char**) (obj + 0x70) = 0;
		return -1;
	}
	an = *(char**) (obj + 0x70);
	if (an == 0) {
		goto fail;
	}
	if (ev[0x190] != 0) {
		frames = *(char**) (an + 0x68);
		if (frames[0x169] == 0 && (an[0x70] & 3) != 0) {
			fcn_004311a0(*(char**) (obj + 0x34), an, 0, *(int*) an, 3);
		}
		if ((obj[0x8c] & 2) != 0) {
			goto clear_anim;
		}
		fcn_00435500(*(char**) (*(char**) (*(char**) (ev + 0x14) + 0x34) + 0x1ec) + 0xf4, *(char**) (*(char**) (obj + 0x70) + 0x68));
clear_anim:
		*(char**) (obj + 0x70) = 0;
		return -1;
	}
	an2 = *(char**) (obj + 0x70);
	if (an2 == 0) {
		goto fail;
	}
	goto byte_ret;
fail:
	return -1;
}
