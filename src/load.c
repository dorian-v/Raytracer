/*
** load.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sat Jul 30 15:52:37 2016 dorian voravong
** Last update Sun Oct 23 15:16:15 2016 dorian voravong
*/

#include <stdlib.h>
#include "lapin.h"
#include "my.h"

int		load_field(t_bunny_ini *ini, int i)
{
  static int	j = 0;
  int		res;

  res = my_get_nbr(bunny_ini_get_field(ini, "Pic", "shape_data", i * 11 + j));
  j = (j + 1) % 11;
  return (res);
}

int		test_shape(t_shape *shape)
{
  unsigned int	tab[8];

  if (shape->type < 1 || shape->type > 8 || shape->r <= 0
      || shape->brillance > 1 || shape->brillance < 0
      || shape->col.full > 8 || shape->col.full < 1
      || (shape->angle != 0 && (int)shape->angle % 90 == 0))
    return (1);
  color_tab(tab);
  shape->col.full = tab[shape->col.full - 1];
  return (0);
}

int	load_shapes(t_bunny_ini *ini, t_map *map)
{
  int	i;

  i = 0;
  if ((map->shape = bunny_malloc(sizeof(t_shape) * map->nb_shapes)) == NULL)
    return (1);
  while (i < map->nb_shapes)
    {
      map->shape[i].type = load_field(ini, i);
      map->shape[i].pos.x = load_field(ini, i);
      map->shape[i].pos.y = load_field(ini, i);
      map->shape[i].pos.z = load_field(ini, i);
      map->shape[i].col.full = load_field(ini, i);
      map->shape[i].r = load_field(ini, i);
      map->shape[i].angle = load_field(ini, i);
      map->shape[i].brillance = (double)load_field(ini, i) / 10.0;
      map->shape[i].x_rot = load_field(ini, i);
      map->shape[i].y_rot = load_field(ini, i);
      map->shape[i].z_rot = load_field(ini, i);
      if (test_shape(&map->shape[i]) == 1)
	return (1);
      if (get_tex(&map->shape[i], map->water) == 1)
	return (1);
      i = i + 1;
    }
  return (0);
}

int	load_lights(t_bunny_ini *ini, t_map *map)
{
  int	i;

  i = 0;
  if ((map->light = bunny_malloc(sizeof(t_light) * map->nb_lights)) == NULL)
    return (1);
  while (i < map->nb_lights)
    {
      map->light[i].pos.x =
	my_get_nbr(bunny_ini_get_field(ini, "Pic", "light_data", i * 3));
      map->light[i].pos.y =
	my_get_nbr(bunny_ini_get_field(ini, "Pic", "light_data", i * 3 + 1));
      map->light[i].pos.z =
	my_get_nbr(bunny_ini_get_field(ini, "Pic", "light_data", i * 3 + 2));
      map->light[i].col.full = WHITE;
      i = i + 1;
    }
  return (0);
}

int		load_map(char *file_path, t_map *map)
{
  t_bunny_ini	*ini;

  if ((ini = bunny_load_ini(file_path)) == NULL)
    return (1);
  if ((map->water =
       my_get_nbr(bunny_ini_get_field(ini, "Pic", "water", 0))) < 0
      || (map->nb_shapes =
	  my_get_nbr(bunny_ini_get_field(ini, "Pic", "nb_shapes", 0))) <= 0
      || (map->nb_lights =
	  my_get_nbr(bunny_ini_get_field(ini, "Pic", "nb_lights", 0))) <= 0)
    return (1);
  if (load_lights(ini, map) == 1 || load_shapes(ini, map) == 1)
    return (1);
  return (0);
}
