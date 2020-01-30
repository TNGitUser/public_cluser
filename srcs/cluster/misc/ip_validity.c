/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_validity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:33:31 by lucmarti          #+#    #+#             */
/*   Updated: 2020/01/28 12:33:35 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	is_ip_valid(char *ip)
{
	struct sockaddr_in	addr;
	int					res;

	res = inet_pton(AF_INET, ip, &(addr.sin_addr));
	return (res != 0);
}
