/*
** solution.c for raytracer in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Tue Aug  2 18:47:29 2016 dorian voravong
** Last update Sun Oct 23 15:27:52 2016 dorian voravong
*/

#include <math.h>
#include "my.h"

double		closest_solution(double a, double b, double d)
{
  double	x1;
  double	x2;

  if (a == 0)
    return (-1);
  x1 = (-b + sqrtf(d)) / (2 * a);
  x2 = (-b - sqrtf(d)) / (2 * a);
  if (x1 < 0 && x2 < 0)
    return (x1);
  if (x1 > 0 && x2 <= 0)
    return (x1);
  if (x2 > 0 && x1 <= 0)
    return (x2);
  if (x1 < x2)
    return (x1);
  else
    return (x2);
}

void	fill_ftab(double (*tabfnc[8])(t_coord_3d *, t_coord_3d *, t_shape *))
{
  tabfnc[0] = plane;
  tabfnc[1] = sphere;
  tabfnc[2] = cone;
  tabfnc[3] = cyl;
  tabfnc[4] = hyperb;
  tabfnc[5] = curd;
  tabfnc[6] = doublenap;
  tabfnc[7] = cyl_hyperb;
}

double		which_shape(t_coord_3d *v, t_coord_3d *eye_pos,
			    t_shape *shape)
{
  double	(*tabfnc[8])(t_coord_3d *, t_coord_3d *, t_shape *);
  double	result;
  t_coord_3d	eye_tr;
  t_coord_3d	v_rot;

  v_rot = *v;
  eye_tr = *eye_pos;
  eye_tr.x = eye_tr.x - shape->pos.x;
  eye_tr.y = eye_tr.y - shape->pos.y;
  eye_tr.z = eye_tr.z - shape->pos.z;
  x_rotation(-shape->x_rot, &eye_tr);
  y_rotation(-shape->y_rot, &eye_tr);
  z_rotation(-shape->z_rot, &eye_tr);
  x_rotation(-shape->x_rot, &v_rot);
  y_rotation(-shape->y_rot, &v_rot);
  z_rotation(-shape->z_rot, &v_rot);
  fill_ftab(tabfnc);
  result = tabfnc[(shape->type) - 1](&v_rot, &eye_tr, shape);
  return (result);
}
