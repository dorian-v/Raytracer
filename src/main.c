/*
** main.c for  in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sun Jul 17 15:30:15 2016 dorian voravong
** Last update Sun Oct 23 15:17:09 2016 dorian voravong
*/

#include <math.h>
#include <stdlib.h>
#include "lapin.h"
#include "my.h"

t_bunny_response	escape(t_bunny_event_state state,
                               t_bunny_keysym key, void *data)
{
  t_prog		*prog;

  prog = data;
  if (key == BKS_ESCAPE && state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  if (key == BKS_L && state == GO_DOWN)
    {
      prog->map->light_mode = (prog->map->light_mode + 1) % 2;
      prog->map->done = 0;
    }
  return (GO_ON);
}

t_bunny_response	raytracer(void *data)
{
  t_prog		*prog;

  prog = data;
  if (prog->map->done == 0)
    {
      draw(prog, prog->eye_dist, &prog->eye_pos, prog->map);
      if (prog->map->light_mode == 1)
	anti_alias(prog->pix);
    }
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, NULL);
  bunny_display(prog->win);
  camera_move(prog);
  camera_rotation(prog);
  object_rotation(prog);
  object_translation(prog);
  if (prog->map->light_mode == 1)
    prog->map->done = 1;
  return (GO_ON);
}

int		initialize(t_prog *prog, char *file_path)
{
  if ((prog->win = bunny_start(1024, 768, 0, "raytracer")) == NULL
      || (prog->pix = bunny_new_pixelarray(1024, 768)) == NULL
      || (prog->menu = load_bmp("ressources/menu.bmp")) == NULL
      || (prog->map = bunny_malloc(sizeof(t_map))) == NULL
      || (prog->k = bunny_get_keyboard()) == NULL
      || (prog->map->font = load_bmp("ressources/star.bmp")) == NULL)
  return (1);
  if (load_map(file_path, prog->map) == 1)
    return (1);
  prog->map->dist_font = 10000;
  prog->eye_dist = prog->pix->clipable.clip_width / (2 * tan(M_PI / 8));
  return (0);
}

void		init_info_var(t_prog *prog)
{
  prog->eye_pos.x = 0;
  prog->eye_pos.y = 0;
  prog->eye_pos.z = -2000;
  prog->x_angle = 0;
  prog->y_angle = 0;
  prog->z_angle = 0;
  prog->select = 0;
  prog->map->done = 0;
  prog->map->light_mode = 0;
}

int		main(int argc, char **argv)
{
  t_prog	prog;

  bunny_set_maximum_ram(314572800);
  if (argc != 2)
    {
      my_putstr_err("Usage: ./raytracer pic.ini\n");
      return (1);
    }
  if (initialize(&prog, argv[1]) == 1)
    {
      my_putstr_err("Error: incorrect .ini format\n");
      return (1);
    }
  while (main_menu(&prog) != 1)
    {
      init_info_var(&prog);
      bunny_set_loop_main_function(raytracer);
      bunny_set_key_response(escape);
      bunny_loop(prog.win, 15, &prog);
    }
  free_all(&prog);
  bunny_set_memory_check(true);
  return (0);
}
