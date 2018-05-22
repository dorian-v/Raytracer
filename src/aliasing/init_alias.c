/*
** fill_multisample.c for  in /home/fourni_2/rendu/raytracer2
**
** Made by Quentin Fournier Montgieux
** Login   <fourni_2@epitech.net>
**
** Started on  Sun Oct  9 15:32:08 2016 Quentin Fournier Montgieux
** Last update Sun Oct 23 14:55:54 2016 dorian voravong
*/

#include "my.h"

void			fill_init_pix(t_bunny_pixelarray *pix_fill,
				      t_bunny_pixelarray *pix)
{
  t_bunny_position	pos;
  t_color		color;

  pos.y = 0;
  while (pos.y < pix->clipable.clip_height)
    {
      pos.x = 0;
      while (pos.x < pix->clipable.clip_width)
	{
	  color.full = tekgetpixel(pix, &pos);
	  tekpixel(pix_fill, &pos, &color);
	  pos.x += 1;
	}
      pos.y += 1;
    }
}

int			init_pix(t_bunny_pixelarray **pix_tab,
				 t_bunny_pixelarray *pix)
{
  int			i;

  i = 0;
  while (i < 4)
    {
      if ((pix_tab[i] =
	   bunny_new_pixelarray(pix->clipable.clip_width,
				pix->clipable.clip_height)) == NULL)
	return (1);
      fill_init_pix(pix_tab[i], pix);
      i += 1;
    }
  return (0);
}

void			init_arr(t_alias *alias)
{
  alias->arr[0].x = 0;
  alias->arr[0].y = 0;
  alias->arr[1].x = 1;
  alias->arr[1].y = 0;
  alias->arr[2].x = 0;
  alias->arr[2].y = 1;
  alias->arr[3].x = 1;
  alias->arr[3].y = 1;
}

void			init_dir(t_bunny_position *dir)
{
  dir[0].x = 1;
  dir[0].y = 1;
  dir[1].x = -1;
  dir[1].y = 1;
  dir[2].x = -1;
  dir[2].y = -1;
  dir[3].x = 1;
  dir[3].y = -1;
}
