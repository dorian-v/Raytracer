/*
** normal.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Wed Aug  3 12:15:01 2016 dorian voravong
** Last update Sat Oct 22 18:41:21 2016 dorian voravong
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

void	simple_position(t_coord_3d *n, t_shape *shape,
			t_intersection *inter)
{
 n->x = inter->pos.x - shape->pos.x;
 n->y = inter->pos.y - shape->pos.y;
 n->z = inter->pos.z - shape->pos.z;
 x_rotation(-shape->x_rot, n);
 y_rotation(-shape->y_rot, n);
 z_rotation(-shape->z_rot, n);
}

void	normal_mapping(t_coord_3d *n, t_intersection *i)
{
  n->x += perlin(i->pos.x, i->pos.z, PERLIN_RES, 0)
    - perlin(i->pos.x + PERLIN_RES * 2, i->pos.z, PERLIN_RES, 0);
  n->y += perlin(i->pos.y, i->pos.x, PERLIN_RES, 0)
    - perlin(i->pos.y + PERLIN_RES * 2, i->pos.z, PERLIN_RES, 0);
  n->z += perlin(i->pos.z, i->pos.x, PERLIN_RES, 0)
    - perlin(i->pos.z + PERLIN_RES * 2, i->pos.y, PERLIN_RES, 0);
}

void	normal_vector(t_coord_3d *n, t_shape *shape,
		      t_intersection *i)
{
  simple_position(n, shape, i);
  if (shape->type == 1)
    {
      n->x = 0;
      n->y = 100 - shape->pos.y;
      n->z = 0;
    }
  if (shape->type == 2 && shape->col.full == (unsigned int)BLUE)
    normal_mapping(n, i);
  if (shape->type == 3 || shape->type == 5
      || shape->type == 6 || shape->type == 7)
    n->y = -powf(tan(shape->angle * M_PI / 180.0), 2)
      * n->y;
  if (shape->type == 4 || shape->type == 8)
       n->y = 0;
  x_rotation(shape->x_rot, n);
  y_rotation(shape->y_rot, n);
  z_rotation(shape->z_rot, n);
}
