/*
** free.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sun Jul 17 15:45:53 2016 dorian voravong
** Last update Fri Oct 14 18:55:57 2016 Quentin Fournier Montgieux
*/

#include "lapin.h"
#include "my.h"

void	free_all(t_prog *prog)
{
  int	i;

  perlin(0, 0, 0, 1);
  bunny_free(prog->map->shape);
  bunny_free(prog->map->light);
  bunny_free(prog->map);
  bunny_delete_clipable(&prog->pix->clipable);
  bunny_delete_clipable(&prog->map->font->clipable);
  bunny_delete_clipable(&prog->menu->clipable);
  i = 0;
  while (i < prog->map->nb_shapes)
    {
      if (prog->map->shape[i].tex != NULL)
	bunny_delete_clipable(&prog->map->shape[i].tex->clipable);
      i += 1;
    }
  bunny_stop(prog->win);
}
