/*
** draw.c for draw in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sat Jul 30 17:40:17 2016 dorian voravong
** Last update Fri Oct 14 22:03:21 2016 Quentin Fournier Montgieux
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

double		vecnorm(t_coord_3d *v)
{
  double	res;

  res = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  return (res);
}

void		screen_vector(t_bunny_position *pixpos,
			      t_bunny_pixelarray *pix,
			      int eye_dist,
			      t_coord_3d *v)
{
  v->x = pixpos->x - pix->clipable.clip_width / 2;
  v->y = pix->clipable.clip_height / 2 - pixpos->y;
  v->z = eye_dist;
}

void		get_vector(t_coord_3d *v, t_intersection *inter,
			   t_light *light, int *j)
{
  *j = 0;
  v->x = light->pos.x - inter->pos.x;
  v->y = light->pos.y - inter->pos.y;
  v->z = light->pos.z - inter->pos.z;
}

void		update_screen(t_prog *prog)
{
  if (prog->map->light_mode == 1)
    {
      bunny_blit(&prog->win->buffer, &prog->pix->clipable, NULL);
      bunny_display(prog->win);
    }
}

void			draw(t_prog *prog,
			     int eye_dist,
			     t_coord_3d *eye_pos,
			     t_map *map)
{
  t_bunny_position	pixpos;
  t_coord_3d		v;
  t_color		color;

  pixpos.y = 0;
  while (pixpos.y < prog->pix->clipable.clip_height)
    {
      pixpos.x = 0;
      while (pixpos.x < prog->pix->clipable.clip_width)
	{
	  screen_vector(&pixpos, prog->pix, eye_dist, &v);
	  if (map->light_mode == 1 || (pixpos.y + pixpos.x) % 10 == 0)
	    {
	      rotation(prog, &v);
	      color.full = find_color(&v, eye_pos, map, -1);
	    }
	  tekpixel(prog->pix, &pixpos, &color);
	  pixpos.x = pixpos.x + 1;
	}
      update_screen(prog);
      pixpos.y = pixpos.y + 1;
    }
}
