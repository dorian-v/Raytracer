/*
** my.h for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sun Jul 17 15:05:56 2016 dorian voravong
** Last update Sun Oct 23 15:32:25 2016 dorian voravong
*/

#ifndef MY_H_
# define MY_H_

# include "lapin.h"

typedef struct	s_coord_3d
{
  double	x;
  double	y;
  double	z;
}		t_coord_3d;

typedef struct		s_shape
{
  int			type;
  t_coord_3d		pos;
  int			r;
  double		angle;
  t_color		col;
  double		brillance;
  double		x_rot;
  double		y_rot;
  double		z_rot;
  t_bunny_pixelarray	*tex;
  int			water;
}			t_shape;

typedef struct		s_light
{
  t_coord_3d		pos;
  t_color		col;
}			t_light;

typedef struct		s_map
{
  int			nb_shapes;
  int			nb_lights;
  int			light_mode;
  int			done;
  t_light		*light;
  t_shape		*shape;
  t_bunny_pixelarray	*font;
  double		dist_font;
  int			water;
}			t_map;

typedef struct		s_prog
{
  t_bunny_pixelarray	*pix;
  t_bunny_window	*win;
  t_map			*map;
  const bool		*k;
  t_coord_3d		eye_pos;
  double		x_angle;
  double		y_angle;
  double		z_angle;
  int			select;
  int			eye_dist;
  t_bunny_pixelarray	*menu;
  int			sel_menu;
}			t_prog;

typedef struct		s_col
{
  int			r;
  int			g;
  int			b;
}			t_col;

typedef struct		s_intersection
{
  t_col			col;
  t_color		base_col;
  t_coord_3d		pos;
  double		k;
  double		angle;
  double		brillance;
}			t_intersection;

typedef struct		s_alias
{
  t_bunny_position	pos;
  int			rgb[3];
  t_bunny_position	arr[4];
}			t_alias;

void			my_putstr_err(char *str);
void			free_all(t_prog *prog);
void			matrix_mult(int **m_a, int **m_b);
int			**transl_matrix();
int			**rot_matrix();
void			tekpixel(t_bunny_pixelarray *pix,
				 t_bunny_position *pos,
				 t_color *color);
void			tekray(const t_bunny_position *screen_info,
			       int *x, int *y, int *z);
double			vecnorm(t_coord_3d *v);
void			get_vector(t_coord_3d *v, t_intersection *inter,
				   t_light *light, int *j);
unsigned int		find_color(t_coord_3d *v, t_coord_3d *eye_pos,
				   t_map *map, int shape_nb);
void			draw(t_prog *prog,
			     int eye_dist,
			     t_coord_3d *eye_pos,
			     t_map *map);
int			load_map(char *file_path, t_map *map);
void			set_color(t_intersection *inter, int *i, double *k);
void			color_tab(unsigned int tab[8]);
void			color_average(t_intersection *inter, int nb_lights);
void			x_rotation(double angle, t_coord_3d *v);
void			y_rotation(double angle, t_coord_3d *v);
void			z_rotation(double angle, t_coord_3d *v);
void			rotation(t_prog *prog, t_coord_3d *v);
void			normal_vector(t_coord_3d *n, t_shape *shape,
				      t_intersection *inter);
void			camera_move(t_prog *prog);
void			camera_rotation(t_prog *prog);
void			object_rotation(t_prog *prog);
void			object_translation(t_prog *prog);
double			closest_solution(double a, double b, double d);
double			which_shape(t_coord_3d *v,
				    t_coord_3d *eye_pos, t_shape *shape);
double			cyl(t_coord_3d *v,
			    t_coord_3d *eye_pos, t_shape *sphere);
double			plane(t_coord_3d *v,
			      t_coord_3d *eye_pos, t_shape *sphere);
double			sphere(t_coord_3d *v,
			       t_coord_3d *eye_pos, t_shape *sphere);
double			cone(t_coord_3d *v,
			     t_coord_3d *eye_pos, t_shape *cone);
double			hyperb(t_coord_3d *v,
			       t_coord_3d *eye_pos, t_shape *cone);
double			curd(t_coord_3d *v, t_coord_3d *eye_pos,
			     t_shape *cone);
double			doublenap(t_coord_3d *v, t_coord_3d *eye_pos,
				  t_shape *cone);
double			cyl_hyperb(t_coord_3d *v, t_coord_3d *eye_pos,
				   t_shape *cylinder);
void			light(t_coord_3d *v, t_map *map,
			      t_intersection *inter, int a);
int			my_get_nbr(const char *str);
int			anti_alias(t_bunny_pixelarray *pix);
int			init_pix(t_bunny_pixelarray **pix_tab,
				 t_bunny_pixelarray *pix);
void			init_arr(t_alias *alias);
void			init_dir(t_bunny_position *dir);
void			fill_pix_with_tab(t_bunny_pixelarray **pix_tab,
					  t_bunny_pixelarray *pix,
					  t_alias *alias);
void			fill_sample(t_alias *alias,
				    t_bunny_pixelarray **pix_tab,
				    t_bunny_position *dir);
void			fill_average(t_bunny_pixelarray *pix,
				     int *rgb,
				     t_bunny_position *a_pos);
void			disp_colorf(t_bunny_pixelarray *pix,
				    t_alias *alias);
void			fill_arr(t_bunny_pixelarray *pix,
				 t_alias *alias,
				 t_bunny_position *dir);
unsigned int		tekgetpixel(t_bunny_pixelarray *pix,
				    t_bunny_position *pos);
unsigned int		reflexion_average(unsigned int col1,
					  unsigned int col2);
int			perlin(double x, double y,
			       double resolution, int opt);
t_bunny_pixelarray	*load_bmp(const char *file);
unsigned int		texture_mapping(t_coord_3d *pos_pix,
					t_shape *cyl);
int			get_tex(t_shape *shape, int water);
int			main_menu(t_prog *prog);

# define PERLIN_RES 50
# define REFLEXION 0.55

#endif /* !MY_H_ */
