/*
** shapes.c for raytracer in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sun Jul 31 16:06:22 2016 dorian voravong
** Last update Sun Oct 23 15:26:56 2016 dorian voravong
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

double		sphere(t_coord_3d *v, t_coord_3d *eye_pos, t_shape *sphere)
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	k;

  a = v->x * v->x + v->y * v->y + v->z * v->z;
  b = 2 * (v->x * eye_pos->x
	   + v->y * eye_pos->y
	   + v->z * eye_pos->z);
  c = pow(eye_pos->x, 2)
    + pow(eye_pos->y, 2)
    + pow(eye_pos->z, 2) - pow(sphere->r, 2);
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}

double		cyl(t_coord_3d *v, t_coord_3d *eye_pos, t_shape *cylinder)
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	k;

  a = v->x * v->x + v->z * v->z;
  b = 2 * (v->x * eye_pos->x + v->z * eye_pos->z);
  c = pow(eye_pos->x, 2) + pow(eye_pos->z, 2)
    - cylinder->r * cylinder->r;
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}

double		cone(t_coord_3d *v, t_coord_3d *eye_pos, t_shape *cone)
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	k;

  a = v->x * v->x + v->z * v->z
    - (v->y * v->y * powf(tan(cone->angle * M_PI / 180.0), 2));
  b = 2 * (v->x * eye_pos->x
           + v->z * eye_pos->z
           - v->y * eye_pos->y
	   * powf(tan(cone->angle * M_PI / 180.0), 2));
  c = pow(eye_pos->x, 2)
    + pow(eye_pos->z, 2)
    - (pow(eye_pos->y, 2)
       * powf(tan(cone->angle * M_PI / 180.0), 2));
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}

double		plane(t_coord_3d *v, t_coord_3d *eye_pos, t_shape *shape)
{
  double	k;

  (void)shape;
  if (v->y == 0)
    return (-1);
  k = (- eye_pos->y) / v->y;
  return (k);
}
