/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:14:19 by gbaud             #+#    #+#             */
/*   Updated: 2022/01/16 21:03:50 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"

// Print error on the error output (stderr) and exit the program
void usage(std::string error) {
    std::cerr << "\033[31;1mError: " << error << std::endl;
    std::cerr << "\033[31;1mUsage: ./computor \"1 * X^0  + 1 * X^1 - 1 * X^2 = 1 * X^0\"\033[0m" << std::endl;
    exit(1);
}

// Remove whitespaces from the string
std::string remove_whitespace(std::string str) {
    std::string res;
    for (std::string::iterator itr = str.begin(); itr != str.end(); itr++)
        if (*itr != ' ' && *itr != '\n' && *itr != '\t' && *itr != '\r' && *itr != '\v')
            res += *itr;
    return (res);
}

// Sqrt function from scratch
double sqrt(double n) {
    double res = 1;
    double last_res = 0;
    while (res != last_res) {
        last_res = res;
        res = (res + n / res) / 2;
    }
    return (res);
}