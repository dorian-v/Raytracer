/*
** menu.c for  in /home/fourni_2/rendu/raytracer2
**
** Made by Quentin Fournier Montgieux
** Login   <fourni_2@epitech.net>
**
** Started on  Fri Oct 14 17:06:33 2016 Quentin Fournier Montgieux
** Last update Sun Oct 23 15:18:37 2016 dorian voravong
*/

#include "my.h"

t_bunny_response	menu_escape(t_bunny_event_state state,
				    t_bunny_keysym key, void *data)
{
  t_prog		*prog;

  prog = data;
  if (key == BKS_ESCAPE && state == GO_DOWN)
    {
      prog->sel_menu = 1;
      return (EXIT_ON_SUCCESS);
    }
  if (key == BKS_RETURN && state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  if (key == BKS_UP && state == GO_DOWN)
    {
      prog->sel_menu -= 1;
      if (prog->sel_menu < 0)
	prog->sel_menu = 1;
    }
  if (key == BKS_DOWN && state == GO_DOWN)
    prog->sel_menu = (prog->sel_menu + 1) % 2;
  return (GO_ON);
}

void		fill_color(t_prog *prog, t_bunny_position *pos)
{
  t_color	color;

  color.full = tekgetpixel(prog->menu, pos);
  if ((color.argb[2] - 8 > color.argb[0]
       && color.argb[2] - 8 > color.argb[1])
      && ((pos->y < prog->menu->clipable.clip_height / 2
	   && prog->sel_menu == 1)
	  || (pos->y >= prog->menu->clipable.clip_height / 2
	      && prog->sel_menu == 0)))
    color.full = 0x444444;
  tekpixel(prog->pix, pos, &color);
}

void			fill_pix(t_prog *prog)
{
  t_bunny_position	pos;

  pos.y = 0;
  while (pos.y < prog->menu->clipable.clip_height)
    {
      pos.x = 0;
      while (pos.x < prog->menu->clipable.clip_width)
	{
	  fill_color(prog, &pos);
	  pos.x += 1;
	}
      pos.y += 1;
    }
}

t_bunny_response	menu(void *data)
{
  t_prog		*prog;

  prog = data;
  fill_pix(prog);
  bunny_blit(&prog->win->buffer, &prog->pix->clipable, NULL);
  bunny_display(prog->win);
  return (GO_ON);
}

int			main_menu(t_prog *prog)
{
  prog->sel_menu = 0;
  bunny_set_loop_main_function(menu);
  bunny_set_key_response(menu_escape);
  bunny_loop(prog->win, 15, prog);
  return (prog->sel_menu);
}
