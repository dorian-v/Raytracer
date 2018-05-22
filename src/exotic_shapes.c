/*
** bonus_shapes.c for  in /home/callew_j/rendu/semestre2/Infographie/raytracer2
**
** Made by
** Login   <callew_j@epitech.net>
**
** Started on  Sat Oct  8 17:34:06 2016
** Last update Sun Oct 23 15:01:15 2016 dorian voravong
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

double		curd(t_coord_3d *v, t_coord_3d *eye_pos, t_shape *cone)
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	k;

  (void)cone;
  a = v->x * v->x + v->z * v->z;
  b = 2 * (v->x * eye_pos->x
           + v->z * eye_pos->z
           - v->y / 2);
  c = pow(eye_pos->x, 2)
    + pow(eye_pos->z, 2)
    - (pow(eye_pos->y, 1));
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}

double		cyl_hyperb(t_coord_3d *v, t_coord_3d *eye_pos,
			   t_shape *cylinder)
{
  double	a;
  double	b;
  double	c;
  double	d;
  double	k;

  a = v->x * v->x - v->z * v->z;
  b = 2 * (v->x * eye_pos->x - v->z * eye_pos->z);
  c = (pow(eye_pos->x, 2) - pow(eye_pos->z, 2)
       - cylinder->r * cylinder->r) - 10000;
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}

double		doublenap(t_coord_3d *v, t_coord_3d *eye_pos,
			  t_shape *cone)
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
       * powf(tan(cone->angle * M_PI / 180.0), 2)) + 10000;
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}

double		hyperb(t_coord_3d *v, t_coord_3d *eye_pos,
		       t_shape *cone)
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
       * powf(tan(cone->angle * M_PI / 180.0), 2)) - 10000;
  d = pow(b, 2) - 4 * a * c;
  if (d < 0)
    return (-1);
  if (d == 0)
    return (-b / (2 * a));
  k = closest_solution(a, b, d);
  return (k);
}
