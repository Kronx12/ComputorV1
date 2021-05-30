/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:57:29 by gbaud             #+#    #+#             */
/*   Updated: 2021/05/30 03:31:56 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream> 
#include <vector> 
#include <string> 

#include "Term.hpp"

std::vector<std::string> split(std::string str, std::string sep);
std::vector<std::string> split_sign(std::string str);
std::string trim(const std::string& str);
std::string trim_sign(const std::string& str);
double ft_sqrt(double X);

#endif
