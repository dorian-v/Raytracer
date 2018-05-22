/*
** usual_alias.c for  in /home/fourni_2/rendu/raytracer2
**
** Made by Quentin Fournier Montgieux
** Login   <fourni_2@epitech.net>
**
** Started on  Sun Oct  9 15:51:34 2016 Quentin Fournier Montgieux
** Last update Sun Oct 23 14:57:44 2016 dorian voravong
*/

#include "my.h"

void			fill_average(t_bunny_pixelarray *pix,
				     int *rgb,
				     t_bunny_position *a_pos)
{
  t_color		colors;

  colors.full = tekgetpixel(pix, a_pos);
  rgb[0] += colors.argb[0];
  rgb[1] += colors.argb[1];
  rgb[2] += colors.argb[2];
}

void			disp_colorf(t_bunny_pixelarray *pix,
				    t_alias *alias)
{
  t_color		colorf;

  alias->rgb[0] /= 4;
  alias->rgb[1] /= 4;
  alias->rgb[2] /= 4;
  colorf.argb[0] = alias->rgb[0];
  colorf.argb[1] = alias->rgb[1];
  colorf.argb[2] = alias->rgb[2];
  tekpixel(pix, &alias->pos, &colorf);
}

void			fill_arr(t_bunny_pixelarray *pix,
				 t_alias *alias,
				 t_bunny_position *dir)
{
  t_bunny_position	a_pos;
  int			i;

  i = 0;
  while (i < 4)
    {
      a_pos.x = alias->pos.x + dir->x * alias->arr[i].x;
      a_pos.y = alias->pos.y + dir->y * alias->arr[i].y;
      fill_average(pix, alias->rgb, &a_pos);
      i += 1;
    }
}
