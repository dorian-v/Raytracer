/*
** rotation.c for rotation in /home/voravo_d/rendu/raytracer1
** 
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
** 
** Started on  Mon Aug  1 14:53:48 2016 dorian voravong
** Last update Mon Aug  8 19:57:46 2016 dorian voravong
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

void		x_rotation(double angle, t_coord_3d *v)
{
  double	y;
  double	z;

  y = cos(angle) * v->y - sin(angle) * v->z;
  z = sin(angle) * v->y + cos(angle) * v->z;
  v->y = y;
  v->z = z;
}

void		y_rotation(double angle, t_coord_3d *v)
{
  double	x;
  double	z;

  x = cos(angle) * v->x + sin(angle) * v->z;
  z = -sin(angle) * v->x + cos(angle) * v->z;
  v->x = x;
  v->z = z;
}

void		z_rotation(double angle, t_coord_3d *v)
{
  double	x;
  double	y;

  x = cos(angle) * v->x - sin(angle) * v->y;
  y = sin(angle) * v->x + cos(angle) * v->y;
  v->x = x;
  v->y = y;
}

void	rotation(t_prog *prog, t_coord_3d *v)
{
  x_rotation(prog->x_angle, v);
  y_rotation(prog->y_angle, v);
  z_rotation(prog->z_angle, v);
}

void	object_rotation(t_prog *prog)
{
  if (prog->k[BKS_R])
    prog->map->shape[prog->select].z_rot += M_PI / 50;
  if (prog->k[BKS_T])
    prog->map->shape[prog->select].z_rot -= M_PI / 50;
  if (prog->k[BKS_F])
    prog->map->shape[prog->select].y_rot += M_PI / 50;
  if (prog->k[BKS_G])
    prog->map->shape[prog->select].y_rot -= M_PI / 50;
  if (prog->k[BKS_C])
    prog->map->shape[prog->select].x_rot += M_PI / 50;
  if (prog->k[BKS_V])
    prog->map->shape[prog->select].x_rot -= M_PI / 50;
}
