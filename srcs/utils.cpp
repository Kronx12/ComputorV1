/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:20:04 by gbaud             #+#    #+#             */
/*   Updated: 2021/05/30 03:31:45 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"

std::vector<std::string> split(std::string str, std::string sep) {
    std::vector<std::string> vec;
    
    while (str.find(sep) != std::string::npos) {
        vec.push_back(trim(str.substr(0, str.find(sep))));
        str.erase(0, str.find(sep) + sep.length());
    }
    if (str.length())
        vec.push_back(trim(str));
    return (vec);
}

std::vector<std::string> split_sign(std::string str) {
    std::vector<std::string> vec;
    
    while (str.find_first_of("+-", 1) != std::string::npos) {
        std::string tmp = str.substr(0, str.find_first_of("+-", 1));
        vec.push_back(tmp);
        str.erase(0, str.find_first_of("+-", 1));
    }
    if (str.length())
        vec.push_back(trim(str));
    return (vec);
}

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return (str);
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::string trim_sign(const std::string& str)
{
    size_t first = str.find_first_not_of("+-");
    if (std::string::npos == first)
        return (str);
    size_t last = str.find_last_not_of("+-");
    return str.substr(first, (last - first + 1));
}

double ft_sqrt(double X) {
    double A, B, M, XN;
    if (X == 0.0)
        return (0.0);
    else {
        M = 1.0;
        XN = X;
        while (XN >= 2.0) {
            XN = 0.25 * XN;
            M = 2.0 * M;
        }
        while (XN < 0.5) {
            XN = 4.0 * XN;
            M = 0.5 * M;
        }
        A = XN;
        B = 1.0 - XN;
        do {
            A = A * (1.0 + 0.5 * B);
            B = 0.25 * (3.0 + B) * B * B;
        } while(B >= 1.0E-15);
        return A * M;
    }
}
