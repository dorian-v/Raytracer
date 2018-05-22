/*
** multi_sample.c for  in /home/fourni_2/rendu/raytracer2
**
** Made by Quentin Fournier Montgieux
** Login   <fourni_2@epitech.net>
**
** Started on  Sun Oct  9 15:47:11 2016 Quentin Fournier Montgieux
** Last update Sun Oct 23 14:57:22 2016 dorian voravong
*/

#include "my.h"

void			fill_pix_with_tab(t_bunny_pixelarray **pix_tab,
					  t_bunny_pixelarray *pix,
					  t_alias *alias)
{
  int			i;

  alias->pos.y = 0;
  while (alias->pos.y < pix->clipable.clip_height)
    {
      alias->pos.x = 0;
      while (alias->pos.x < pix->clipable.clip_width)
	{
	  alias->rgb[0] = 0;
	  alias->rgb[1] = 0;
	  alias->rgb[2] = 0;
	  i = 0;
	  while (i < 4)
	    {
	      fill_average(pix_tab[i], alias->rgb, &alias->pos);
	      i += 1;
	    }
	  disp_colorf(pix, alias);
	  alias->pos.x += 1;
	}
      alias->pos.y += 1;
    }
}

void			do_alias(t_bunny_pixelarray *pix,
				 t_alias *alias,
				 t_bunny_position *dir)
{
  alias->pos.y = (pix->clipable.clip_height - 1) * (dir->y == -1);
  while (alias->pos.y * dir->y < (pix->clipable.clip_height - 1)
	 * (dir->y == 1))
    {
      alias->pos.x = (pix->clipable.clip_width - 1) * (dir->x == -1);
      while (alias->pos.x * dir->x < (pix->clipable.clip_width - 1)
	     * (dir->x == 1))
	{
	  alias->rgb[0] = 0;
	  alias->rgb[1] = 0;
	  alias->rgb[2] = 0;
	  fill_arr(pix, alias, dir);
	  disp_colorf(pix, alias);
	  alias->pos.x += dir->x;
	}
      alias->pos.y += dir->y;
    }
}

void			fill_sample(t_alias *alias,
				    t_bunny_pixelarray **pix_tab,
				    t_bunny_position *dir)
{
  int			i;

  i = 0;
  while (i < 4)
    {
      do_alias(pix_tab[i], alias, &dir[i]);
      i += 1;
    }
}
