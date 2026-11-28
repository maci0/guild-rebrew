extern int d2_MouseRightBoundary;
extern int d2_MouseBottomBoundary;
extern int g_6b5c80;
extern int d2_MouseTopBoundary;
extern int d3_CameraHorizontalIndex;
extern int d3_CameraVerticalStep;
extern int g_774734;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
extern char* d3_ActiveCamera;
extern int d3_SavedCameraPos;
extern int d3_SavedCameraPosY;
extern int d3_SavedCameraPosZ;
extern int d3_CameraTargetRotation;
extern int d3_CameraTargetRotY;
extern int d3_CameraTargetRotZ;
extern int d3_CameraAnimating;
extern int d3_ActiveCameraAnimation;
extern int g_6a256c;

int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl d3_FreeObjectAnimation(char*);
void __cdecl d3_AnimateObjectTransform(char*, int*, int*, int, int);

/* ADDRESS: GOLDTL 0x0052ae80 */
void __cdecl d3_UpdateCameraAtScreenEdges(void)
{
	int minx;
	int maxx;
	int miny;
	int maxy;
	int idx;
	float ref[4];
	int next[4];
	int cur[4];

	minx = g_6b5c80 + 1;
	miny = d2_MouseTopBoundary + 1;
	maxx = d2_MouseRightBoundary - 1;
	maxy = d2_MouseBottomBoundary - 1;
	ref[0] = 0.0f;
	ref[1] = 0.0f;
	ref[2] = 0.0f;
	ref[3] = 0.0f;

	if (g_774734) {
		if ((short) io_ActiveCursorX < minx) {
			return;
		}
		if ((short) io_ActiveCursorX > maxx) {
			return;
		}
		if ((short) io_ActiveCursorY < miny) {
			return;
		}
		if ((short) io_ActiveCursorY > maxy) {
			return;
		}
		g_774734 = 0;
		return;
	}

	if ((short) io_ActiveCursorY > miny && (short) io_ActiveCursorY < maxy) {
		if ((short) io_ActiveCursorX < minx) {
			if (d3_CameraHorizontalIndex <= -1) {
				return;
			}
			d3_CameraHorizontalIndex--;
		} else if ((short) io_ActiveCursorX > maxx) {
			if (d3_CameraHorizontalIndex >= 1) {
				return;
			}
			d3_CameraHorizontalIndex++;
		} else {
			return;
		}
		idx = d3_CameraHorizontalIndex;
		d3_CameraVerticalStep = 0;
		if (idx == -1) {
			if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xe4), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (d3_ActiveCamera + 0xe4);
			cur[1] = *(int*) (d3_ActiveCamera + 0xe8);
			cur[2] = *(int*) (d3_ActiveCamera + 0xec);
			next[0] = *(int*) (d3_ActiveCamera + 0xf0);
			next[1] = *(int*) (d3_ActiveCamera + 0xf4);
			next[2] = *(int*) (d3_ActiveCamera + 0xf8);
		} else if (idx == 0) {
			cur[0] = *(int*) (d3_ActiveCamera + 0x5c);
			cur[1] = *(int*) (d3_ActiveCamera + 0x60);
			cur[2] = *(int*) (d3_ActiveCamera + 0x64);
			next[0] = *(int*) (d3_ActiveCamera + 0x90);
			next[1] = *(int*) (d3_ActiveCamera + 0x94);
			next[2] = *(int*) (d3_ActiveCamera + 0x98);
		} else if (idx == 1) {
			if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xfc), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (d3_ActiveCamera + 0xfc);
			cur[1] = *(int*) (d3_ActiveCamera + 0x100);
			cur[2] = *(int*) (d3_ActiveCamera + 0x104);
			next[0] = *(int*) (d3_ActiveCamera + 0x108);
			next[1] = *(int*) (d3_ActiveCamera + 0x10c);
			next[2] = *(int*) (d3_ActiveCamera + 0x110);
		}
	} else {
		idx = d3_CameraVerticalStep;
		if ((short) io_ActiveCursorY < miny) {
			if (idx <= -1) {
				return;
			}
			idx--;
			d3_CameraVerticalStep = idx;
		} else if ((short) io_ActiveCursorY > maxy) {
			if (idx >= 1) {
				return;
			}
			idx++;
			d3_CameraVerticalStep = idx;
		}
		d3_CameraHorizontalIndex = 0;
		if (idx == 0) {
			cur[0] = *(int*) (d3_ActiveCamera + 0x5c);
			cur[1] = *(int*) (d3_ActiveCamera + 0x60);
			cur[2] = *(int*) (d3_ActiveCamera + 0x64);
			next[0] = *(int*) (d3_ActiveCamera + 0x90);
			next[1] = *(int*) (d3_ActiveCamera + 0x94);
			next[2] = *(int*) (d3_ActiveCamera + 0x98);
		} else if (idx == -1) {
			if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xb4), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (d3_ActiveCamera + 0xb4);
			cur[1] = *(int*) (d3_ActiveCamera + 0xb8);
			cur[2] = *(int*) (d3_ActiveCamera + 0xbc);
			next[0] = *(int*) (d3_ActiveCamera + 0xc0);
			next[1] = *(int*) (d3_ActiveCamera + 0xc4);
			next[2] = *(int*) (d3_ActiveCamera + 0xc8);
		} else if (idx == 1) {
			if (CompareVector3WithinTolerance((float*) (d3_ActiveCamera + 0xcc), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (d3_ActiveCamera + 0xcc);
			cur[1] = *(int*) (d3_ActiveCamera + 0xd0);
			cur[2] = *(int*) (d3_ActiveCamera + 0xd4);
			next[0] = *(int*) (d3_ActiveCamera + 0xd8);
			next[1] = *(int*) (d3_ActiveCamera + 0xdc);
			next[2] = *(int*) (d3_ActiveCamera + 0xe0);
		}
	}

	d3_SavedCameraPos = cur[0];
	d3_SavedCameraPosY = cur[1];
	d3_SavedCameraPosZ = cur[2];
	d3_CameraTargetRotation = next[0];
	d3_CameraTargetRotY = next[1];
	d3_CameraTargetRotZ = next[2];
	d3_FreeObjectAnimation(d3_ActiveCamera);
	d3_CameraAnimating = 0;
	d3_ActiveCameraAnimation = 0;
	d3_AnimateObjectTransform(d3_ActiveCamera, cur, next, g_6a256c, 8);
	g_774734 = 1;
}
unsigned char _dpad_6b8014[748];
