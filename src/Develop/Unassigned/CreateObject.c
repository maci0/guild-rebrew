

void __cdecl d3_CreateSceneModelObject(int, int*, float*, int);

void __cdecl CreateObject(int* x, int* y, int* z, int* nameRef)
{
	float a[3];
	int b[4];

	a[0] = 0.0f;
	a[1] = 0.0f;
	b[0] = *x;
	b[1] = *y;
	a[2] = 0.0f;
	b[2] = *z;
	d3_CreateSceneModelObject(0, b, a, *nameRef);
}
