/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:29:26 by mmoreira          #+#    #+#             */
/*   Updated: 2022/02/17 22:24:09 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_mundo(t_mundo *mundo)
{
	t_list	*lst;

	lst = mundo->rots;
	while (lst)
	{
		ft_lstclear((t_list **)&lst->vol, free);
		lst = lst->next;
	}
	ft_lstclear(&mundo->rots, free);
	ft_lstclear(&mundo->cams, free);
	ft_lstclear(&mundo->lamps, free);
	ft_lstclear(&mundo->objs, free);
}

static void	set_mundo(t_mundo *mundo)
{
	mundo->rsl[2] = 0;
	mundo->a = 0;
	mundo->c = 0;
	mundo->cams = NULL;
	mundo->rt = 0;
	mundo->rots = NULL;
	mundo->l = 0;
	mundo->lamps = NULL;
	mundo->o = 0;
	mundo->objs = NULL;
}

static int	check_args(int n, char **str)
{
	int	i;

	i = 0;
	if (n < 2 || n > 3)
		return (0);
	if (n == 3 && ft_strncmp(*(str + 2), "--save", ft_strlen(*(str + 2))))
		return (0);
	while (*(*(str + 1) + i) != '\0')
		i++;
	if (*(*(str + 1) + i - 1) == 't')
		if (*(*(str + 1) + i - 2) == 'r')
			if (*(*(str + 1) + i - 3) == '.')
				return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mundo	mundo;

	set_mundo(&mundo);
	if (!(check_args(argc, argv)))
	{
		ft_printf("Error\nDeu merda nos argumentos do programa\n");
		return (-1);
	}
	if (!(make_mundo(*(argv + 1), &mundo)))
	{
		ft_printf("Error\nDeu merda na formatação do .rt\n");
		free_mundo(&mundo);
		return (-1);
	}
	if (!(check_mundo(&mundo)))
	{
		ft_printf("Deu merda nos valores dos elementos\n");
		free_mundo(&mundo);
		return (-1);
	}
	init_render(argc, &mundo);
	return (0);
}
