/*
** textures.c for  in /home/fourni_2/rendu/raytracer2
**
** Made by Quentin Fournier Montgieux
** Login   <fourni_2@epitech.net>
**
** Started on  Sun Oct  9 17:08:12 2016 Quentin Fournier Montgieux
** Last update Sun Oct 23 15:31:41 2016 dorian voravong
*/

#include <math.h>
#include "my.h"

void	inv_rotate(t_coord_3d *n, t_shape *cyl)
{
  n->x -= cyl->pos.x;
  n->y -= cyl->pos.y;
  n->z -= cyl->pos.z;
  x_rotation(-cyl->x_rot, n);
  y_rotation(-cyl->y_rot, n);
  z_rotation(-cyl->z_rot, n);
}

unsigned int		plan_texture(t_coord_3d *pix, t_shape *plan)
{
  t_bunny_position	pos;

  if (plan->water == 0)
    return (plan->col.full);
  pos.y = (int)pix->z % plan->tex->clipable.clip_height;
  pos.x = (int)pix->x % plan->tex->clipable.clip_width;
  pos.x = pos.x * (1 - 2 * (pos.x < 0));
  pos.y = pos.y * (1 - 2 * (pos.y < 0));
  return (tekgetpixel(plan->tex, &pos));
}

unsigned int		circul_texture(t_coord_3d *pix, t_shape *cyl)
{
  t_coord_3d		v1;
  t_coord_3d		v2;
  double		angle;
  t_bunny_position	pos;

  v1.x = pix->x;
  v1.y = 0;
  v1.z = pix->z;
  v2.x = 0;
  v2.y = 0;
  v2.z = -cyl->r;
  angle = (v1.z * v2.z) / (vecnorm(&v1) * vecnorm(&v2));
  angle = acos(angle);
  pos.y = (int)(pix->y) % cyl->tex->clipable.clip_height;
  pos.x = (int)(angle * (float)cyl->r) % cyl->tex->clipable.clip_width;
  pos.x = pos.x * (1 - 2 * (pos.x < 0));
  pos.y = pos.y * (1 - 2 * (pos.y < 0));
  return (tekgetpixel(cyl->tex, &pos));
}

unsigned int		texture_mapping(t_coord_3d *pos_pix,
					t_shape *shape)
{
  t_coord_3d		pix;

  pix = *pos_pix;
  inv_rotate(&pix, shape);
  if (shape->type == 1)
    return (plan_texture(&pix, shape));
  else
    return (circul_texture(&pix, shape));
}
