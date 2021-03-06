/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmann <lmann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:05:09 by lmann             #+#    #+#             */
/*   Updated: 2022/03/25 14:33:20 by lmann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(int dc)
{
	if (ft_isdigit(dc) != 0 || ft_isalpha(dc) != 0)
		return (1);
	return (0);
}
