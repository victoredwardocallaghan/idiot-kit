#include "winsys/winsys.h"
#include "winsys/shaders.h"

int main()
{
	init();
	idk();
	build_glsl();
	draw_loop();
	finit();

	return 0;
}
