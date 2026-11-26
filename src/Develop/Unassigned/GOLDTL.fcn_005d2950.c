


int __cdecl abs(int);
#pragma intrinsic(abs)
unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00508eb0(unsigned short, int);

int __cdecl gm_CanCourtEntity(int actorId, int targetId)
{
	unsigned char* actor;
	unsigned char* target;

	actor = gm_LookupEntityRecordById(actorId);
	target = gm_LookupEntityRecordById(targetId);
	if (actor == 0 || target == 0) {
		return -0x400;
	}
	if (!(actor[8] > 0)) {
		return -0x401;
	}
	if (!(target[8] > 0)) {
		return -0x402;
	}
	if (*(int*) (target + 0x5c) != -1 && *(int*) (target + 0x5c) != actorId) {
		return -0x403;
	}
	if (*(int*) (actor + 0x5c) != -1 && *(int*) (actor + 0x5c) != targetId) {
		return -0x404;
	}
	if (actor[0x1b1] > 0) {
		return -0x405;
	}
	if (target[0x1b1] > 0) {
		return -0x406;
	}
	return abs(fcn_00508eb0(*(unsigned short*) actor, 0) - fcn_00508eb0(*(unsigned short*) target, 0)) < 6;
}
