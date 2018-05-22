/*
** interesection.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Thu Jul 28 12:39:23 2016 dorian voravong
** Last update Sun Oct 23 15:09:03 2016 dorian voravong
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

void	perlin_noise(t_intersection *inter)
{
  int	p;

  p = perlin(inter->pos.x, inter->pos.z, PERLIN_RES, 0);
  inter->base_col.argb[0] = p;
  inter->base_col.argb[1] = 0;
  inter->base_col.argb[2] = 0;
}

void		get_point_info(t_coord_3d *v, t_coord_3d *eye_pos,
			       t_shape *shape, t_intersection *inter)
{
  inter->pos.x = eye_pos->x + inter->k * v->x;
  inter->pos.y = eye_pos->y + inter->k * v->y;
  inter->pos.z = eye_pos->z + inter->k * v->z;
  if (shape->type == 1)
    {
      if ((abs(inter->pos.x) % 400 < 200 && abs(inter->pos.z) % 400 < 200)
	  || ((abs(inter->pos.x) % 400 >= 200
	       && abs(inter->pos.z) % 400 >= 200)))
	inter->base_col.full = texture_mapping(&inter->pos, shape);
      else
	perlin_noise(inter);
      inter->brillance = shape->brillance;
    }
  else if (shape->type == 4)
    inter->base_col.full = texture_mapping(&inter->pos, shape);
  else
    {
      inter->brillance = shape->brillance;
      inter->base_col.full = shape->col.full;
    }
}

unsigned int		get_font(t_map *map, t_coord_3d *v,
				 t_coord_3d *eye_pos)
{
  t_coord_3d		pix;
  t_shape		f_shape;
  double		k;

  f_shape.type = 4;
  f_shape.pos = *eye_pos;
  f_shape.x_rot = 0;
  f_shape.y_rot = 0;
  f_shape.z_rot = 0;
  f_shape.tex = map->font;
  f_shape.r = map->dist_font;
  k = sphere(v, eye_pos, &f_shape);
  pix.x = eye_pos->x + k * v->x;
  pix.y = eye_pos->y + k * v->y;
  pix.z = eye_pos->z + k * v->z;
  return (texture_mapping(&pix, &f_shape));
}

unsigned int		find_color(t_coord_3d *v, t_coord_3d *eye_pos,
				   t_map *map, int shape_nb)
{
  t_intersection	inter;
  int			i;
  int			j;
  double		k;

  i = 0;
  j = 0;
  inter.k = which_shape(v, eye_pos, &map->shape[i]);
  while (i < map->nb_shapes)
    {
      if (i != shape_nb && (((k = which_shape(v, eye_pos, &map->shape[i])) > 0
			     && inter.k < 0)
			    || (k > 0 && inter.k > 0 && k < inter.k)))
	{
	  inter.k = k;
	  j = i;
	}
      i = i + 1;
    }
  if (inter.k <= 0)
    return (get_font(map, v, eye_pos));
  get_point_info(v, eye_pos, &map->shape[j], &inter);
  if (map->light_mode == 1)
    light(v, map, &inter, j);
  return (inter.base_col.full);
}
