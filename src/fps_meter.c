#include <stdio.h>
#include <time.h>
#include "libft/libft_compat.h"

void fps_meter_frame()
{
	static uint i = 0;
	static clock_t cl = 0;

	i++;
	if ((double)(clock() - cl) / CLOCKS_PER_SEC >= 1)
	{
		cl = clock();
		printf("fps: %d\n", i);
		i = 0;
	}
}
