/*
** light.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sun Jul 31 16:04:26 2016 dorian voravong
** Last update Fri Oct 14 22:06:30 2016 Quentin Fournier Montgieux
*/

#include <stdio.h>
#include <math.h>
#include "lapin.h"
#include "my.h"

void		light_ratio(t_intersection *inter,
			    t_color *col)
{
  col->full = inter->base_col.full;
  if (inter->angle < 0)
    {
      col->argb[0] = 0;
      col->argb[1] = 0;
      col->argb[2] = 0;
    }
  else
    {
      col->argb[0] = inter->base_col.argb[0]
	* inter->angle;
      col->argb[1] = inter->base_col.argb[1]
	* inter->angle;
      col->argb[2] = inter->base_col.argb[2]
	* inter->angle;
    }
}

void		light_angle(t_intersection *inter,
			    t_coord_3d *v, t_shape *shape,
			    double k)
{
  t_coord_3d	n;
  t_color	col;

  if (k > 0 && k < 1)
    return ;
  normal_vector(&n, shape, inter);
  inter->angle = (n.x * v->x + n.y * v->y + n.z * v->z)
    / (vecnorm(&n) * vecnorm(v));
  if (inter->angle < 0.1)
    inter->angle = 0.1;
  light_ratio(inter, &col);
  inter->col.r = inter->col.r + col.argb[0];
  inter->col.g = inter->col.g + col.argb[1];
  inter->col.b = inter->col.b + col.argb[2];
}

void		brillance(t_intersection *inter, t_light *light,
			  double k)
{
  double	a;

  if (k > 0 && k < 1)
    return ;
  if (inter->angle > 0.95)
    {
      a = (inter->angle - 0.95) / 0.05;
      inter->col.r = inter->col.r
	+ inter->brillance * light->col.argb[0] * a;
      inter->col.g = inter->col.g
	+ inter->brillance * light->col.argb[1] * a;
      inter->col.b = inter->col.b
	+ inter->brillance * light->col.argb[2] * a;
    }
}

unsigned int	reflexion(t_coord_3d *v, t_intersection *inter,
			  t_map *map, int a)
{
  static int	i = 1;
  t_coord_3d	r;
  t_coord_3d	n;
  unsigned int	col;

  if (i < 5000 && (map->shape[a].type == 2
		   && map->shape[a].col.full != (unsigned int)BLUE))
    {
      i = i + 1;
      normal_vector(&n, &map->shape[a], inter);
      if (inter->angle <= 0)
	return (0);
      r.x = 2.0 * n.x * inter->angle * vecnorm(&n) * vecnorm(v) + v->x;
      r.y = 2.0 * n.y * inter->angle * vecnorm(&n) * vecnorm(v) + v->y;
      r.z = 2.0 * n.z * inter->angle * vecnorm(&n) * vecnorm(v) + v->z;
      col = find_color(&r, &inter->pos, map, a);
      return (reflexion_average(inter->base_col.full, col));
    }
  i = 0;
  return (inter->base_col.full);
}

void		light(t_coord_3d *first_v,
		      t_map *map, t_intersection *inter, int a)
{
  int		i;
  int		j;
  double	k;
  t_coord_3d	v;

  set_color(inter, &i, &k);
  while (i < map->nb_lights)
    {
      get_vector(&v, inter, &map->light[i], &j);
      while ((k >= 1 || k <= 0) && j < map->nb_shapes)
        {
          if (j != a)
            k = which_shape(&v, &inter->pos, &map->shape[j]);
	  j = j + 1;
        }
      light_angle(inter, &v, &map->shape[a], k);
      brillance(inter, &map->light[i], k);
      i = i + 1;
      k = 2;
    }
  color_average(inter, map->nb_lights);
  inter->base_col.full = reflexion(first_v, inter, map, a);
}
