#include "mlx.h"
#include <libc.h>

int main()
{
	void *init = mlx_init();
	void *window = mlx_new_window(init, 7 * 64, 7 * 64, "test");
	mlx_pixel_put(init, window, 3 * 64, 3 * 64, 16777215);
	mlx_loop(init);
}
