#include "cub3d.h"

int key_pressed_function(int keycode, void *param)
{
	t_mlx *mlx = param;

	if (keycode == KEY_ESC)
		mlx_loop_end(mlx->mlx_ptr);
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		ft_printf("W, A, S or D was pressed\n");
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		ft_printf("left or right was pressed\n");
	return (0);
}

int key_released_function(int keycode, void *param)
{
	t_mlx *mlx = param;

	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		ft_printf("W, A, S or D was released\n");
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		ft_printf("left or right was released\n");
	return (0);
}
int main(void)
{
	t_mlx	mlx;

	ft_bzero(&mlx, sizeof(t_mlx));
	//MLX INIT
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (1);
	mlx.window = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!mlx.window)
	{
		mlx_destroy_display(mlx.mlx_ptr);
		free(mlx.mlx_ptr);
		return (1);
	}
	mlx.frame_buffer.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx.frame_buffer.img_ptr)
	{
		mlx_destroy_window(mlx.mlx_ptr, mlx.window);
		mlx_destroy_display(mlx.mlx_ptr);
		free(mlx.mlx_ptr);
		return (1);
	}
	mlx.frame_buffer.data_address = mlx_get_data_addr(mlx.frame_buffer.img_ptr, &mlx.frame_buffer.bits_per_pixel, 
											&mlx.frame_buffer.line_length, &mlx.frame_buffer.endian);
	
	//MLX HOOK - Touches awsd ESC, fleche gauche et droite via key_handler() 
	mlx_hook(mlx.window, KeyPress, KeyPressMask, key_pressed_function, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, key_released_function, &mlx);
	//MLX HOOK - Croix rouge pour fermer
	mlx_hook(mlx.window, DestroyNotify, StructureNotifyMask, mlx_loop_end, &mlx);
	mlx_loop(mlx.mlx_ptr);

	mlx_destroy_image(mlx.mlx_ptr, mlx.frame_buffer.img_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.window);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
	return 0;

}