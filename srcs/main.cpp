/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:56:24 by gbaud             #+#    #+#             */
/*   Updated: 2021/05/30 04:37:14 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"

double calc_alpha(Term *terms) {
    return ((terms[1].getValue() * terms[1].getValue()) - (4 * terms[2].getValue() * terms[0].getValue()));
}

void reduce_poly(std::string left, std::string right, int max_exponent) {
    std::vector<std::string> tkns;
    Term *terms = new Term[max_exponent + 1];
    
    // LEFT
    tkns = split_sign(left); 
    for (std::vector<std::string>::iterator itr = tkns.begin(); itr != tkns.end(); itr++) {
        if ((*itr)[0] == '-')
            (*itr) = "-" + trim(trim_sign(*itr));
        else
            (*itr) = trim(trim_sign(*itr));
        int tmp_exp = 0;
        for (size_t i = 0; i < itr->length(); i++)
            if ((*itr)[i] == '^') {
                while ((*itr)[++i] == ' ');
                tmp_exp = stol(std::string(&(*itr)[i]));
                break;
            }
        terms[tmp_exp].setExp(tmp_exp);
        terms[tmp_exp].setValue(terms[tmp_exp].getValue() + stod(*itr));
    }
    
    // RIGHT
    tkns = split_sign(right);
    for (std::vector<std::string>::iterator itr = tkns.begin(); itr != tkns.end(); itr++) {
        if ((*itr)[0] == '-')
            (*itr) = "-" + trim(trim_sign(*itr));
        else
            (*itr) = trim(trim_sign(*itr));
        int tmp_exp = 0;
        for (size_t i = 0; i < itr->length(); i++)
            if ((*itr)[i] == '^') {
                while ((*itr)[++i] == ' ');
                tmp_exp = stol(std::string(&(*itr)[i]));
                break;
            }
        terms[tmp_exp].setExp(tmp_exp);
        terms[tmp_exp].setValue(terms[tmp_exp].getValue() + (stod(*itr) * -1));
    }
    
    std::cout << "\e[1;34m>>>>>\t";
    for (int i = 0; i <= max_exponent; i++)
        terms[i].debug();
    std::cout << "= 0\e[0m" << std::endl;

    std::cout << "\e[33;1mPolynomial degree: " << max_exponent << "\e[0m" << std::endl;
    
    if (max_exponent < 3) {
        if (max_exponent == 2) {
            if (!terms[2].getValue())
                std::cout << "\e[32;1mError: A can't be null\e[0m" << std::endl;
            else if (!terms[1].getValue())
                std::cout << "\e[32;1mError: B can't be null\e[0m" << std::endl;
            else if (!terms[0].getValue())
                std::cout << "\e[32;1mError: C can't be null\e[0m" << std::endl;
            else {
                double alpha = calc_alpha(terms);
                if (alpha > 0) {
                    double x1 = (-terms[1].getValue() - ft_sqrt(alpha)) / (2 * terms[2].getValue());
                    double x2 = (-terms[1].getValue() + ft_sqrt(alpha)) / (2 * terms[2].getValue());
                    std::cout   << "\e[32;1mDiscriminant is strictly positive, the two solutions are:" << std::endl
                                << "x1 = " << x1 << std::endl << "x2 = " << x2 << std::endl << "\e[0m";
                } else if (!alpha)
                    std::cout   << "Discriminant is equal to zero, the solution is:" << (-(terms[1].getValue() / (terms[2].getValue() * 2))) << std::endl << "\e[0m";
                else
                    std::cout << "\e[32;1mThere are no solutions." << std::endl;
            }
        } else if (max_exponent == 1)
            std::cout << "\e[32;1mThe solution is: " << ((-terms[0].getValue())/terms[1].getValue()) << std::endl << "\e[0m";
        else
            std::cout << "\e[32;1mContant solution is: " << terms[0].getValue() << std::endl << "\e[0m"; 
    } else
        std::cout << "\e[32;1mThe polynomial degree is stricly greater than 2, I can't solve." << std::endl << "\e[0m";
    delete[] terms;
}

int main(int ac, char **av) {
    
    if (ac != 2) {
        std::cerr << "Error args count invalid: ./ComputerV1 \"5 + 4 * X + X^2= X^2\"" << std::endl;
        return (1);
    }

    std::cout << "\e[31;1m═══════════════════════════════════════════\e[0m" << std::endl;

    std::vector<std::string> tkns = split(std::string(av[1]), "=");
    std::string left = tkns[0];
    std::string right = tkns[1];

    int max_exponent = 0;

    for (size_t i = 0; i < left.length(); i++)
        if (left[i] == '^') {
            while (left[++i] == ' ');
            if (stol(std::string(&left[i])) > max_exponent)
                max_exponent = stol(std::string(&left[i]));
        }
    for (size_t i = 0; i < right.length(); i++)
        if (right[i] == '^') {
            while (right[++i] == ' ');
            if (stol(std::string(&right[i])) > max_exponent)
                max_exponent = stol(std::string(&right[i]));
        }
    reduce_poly(left, right, max_exponent);
    return (0);
}