

typedef struct Snd Snd;

// SIZE 0x20
typedef struct {
	void* m[7];
	long (__stdcall* SetVolume)(Snd* self, long vol);
} SndVtbl;

// SIZE 0x4
struct Snd {
	SndVtbl* vtbl;
};

char* __cdecl FindVideoById(int id);

int __cdecl fcn_0041f4c0(int id, float vol)
{
	char* o;
	Snd* s;

	o = FindVideoById(id);
	if (o != 0 && vol >= 0.0f && vol <= 1.0f) {
		s = *(Snd**) (o + 0x12c);
		if (s->vtbl->SetVolume(s, (long) (vol * -10000.0f)) >= 0) {
			return 1;
		}
	}
	return 0;
}
