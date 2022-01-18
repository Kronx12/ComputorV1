/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:11:50 by gbaud             #+#    #+#             */
/*   Updated: 2022/01/17 17:44:43 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"

std::vector<Term> extract_from_string(std::string str) {
    std::vector<Term> res_vector;
    std::regex const term_pattern { "([+-]?[0-9]+(?:\\.[0-9]+)?)\\*X\\^([+-]?[0-9]+(?:\\.[0-9]+)?)" };
    std::smatch res;
    int match_count = 0;
    
    std::string copy = str;
    
    if (str == "0")
        return (res_vector);

    std::string::const_iterator start(str.cbegin());
    while (regex_search(start, str.cend(), res, term_pattern)) {
        double coef = std::stod(res[1]);
        double exp = std::stod(res[2]);
        bool found = false;
        for (std::vector<Term>::iterator itr = res_vector.begin(); itr != res_vector.end(); itr++)
            if (itr->getExp() == exp) {
                itr->addCoef(coef);
                found = true;
            }
        if (!found) {
            res_vector.push_back(Term(coef, exp));
            match_count++;
        }
        // remove all match from copy
        copy.erase(res.position(), res.length());
        start = res.suffix().first;
    }
    if (copy != "" || !match_count)
        usage("Syntax error !");
    return (res_vector);
}

int main(int argc, char **argv) {
    std::string input;
    
    // Check arguments
    if (argc == 1)
        getline(std::cin, input);
    else if (argc == 2)
        input = argv[1];
    else
        usage("Missing arguments !");

    // Clear whitespace
    input = remove_whitespace(input);

    // Check if the input is valid
    std::regex const equal_pattern { "^.+=.+$" };
    if (!std::regex_match(input, equal_pattern))
        usage("Input must be and equation !");
    
    // Split
    std::string lhs = input.substr(0, input.find('='));
    std::string rhs = input.substr(input.find('=') + 1);

    // Extract terms from equation
    std::vector<Term> lhs_terms = extract_from_string(lhs);
    std::vector<Term> rhs_terms = extract_from_string(rhs);
        
    // Merge terms
    for (std::vector<Term>::iterator itr = lhs_terms.begin(); itr != lhs_terms.end(); itr++)
        for (std::vector<Term>::iterator itr2 = rhs_terms.begin(); itr2 != rhs_terms.end(); itr2++) {
            if (itr->getExp() == itr2->getExp()) {
                itr->addCoef(itr2->getCoef() * -1);
                rhs_terms.erase(itr2);
                break;
            }
        }
    // Invert the coefficients of the rhs
    for (std::vector<Term>::iterator itr = rhs_terms.begin(); itr != rhs_terms.end(); itr++)
        itr->setCoef(itr->getCoef() * -1);
    lhs_terms.insert(lhs_terms.end(), rhs_terms.begin(), rhs_terms.end());

    // Sort terms
    std::sort(lhs_terms.begin(), lhs_terms.end(), [](Term const &a, Term const &b) { return (a.getExp() < b.getExp()); });
    
    // Print reduced form
    bool is_first = true;
    std::cout << BLUE << "Reduced form: ";
    for (std::vector<Term>::iterator itr = lhs_terms.begin(); itr != lhs_terms.end(); itr++) {
        std::cout << (itr->getCoef() < 0 ? ((!is_first) ? "- " : "-") : ((!is_first) ? "+ " : "")) << std::abs(itr->getCoef()) << " * X^" << itr->getExp() << " ";
        is_first = false;
    }
    std::cout << "= 0" << RESET << std::endl;
    
    // Get polynomial degree
    double polynomial_degree = std::max_element(lhs_terms.begin(), lhs_terms.end(), [](Term const &a, Term const &b) { return (a.getExp() < b.getExp()); })->getExp();
    std::cout << YELLOW << "Polynomial degree: " << polynomial_degree << RESET << std::endl;
    
    if (polynomial_degree == 0 && lhs_terms.size() == 1) {
        // calcule the result (ax = 0)
        double a = lhs_terms[0].getCoef();
        
        if (a == 0)
            // All are solutions
            std::cout << GREEN << "All reals are solutions" << RESET << std::endl;
        else if (a != 0)
            // No solution
            std::cout << RED << "No solution" << RESET << std::endl;
    } else if (polynomial_degree == 1 && lhs_terms.size() == 2) {
        // calcule the result (ax + b = 0)
        double a = lhs_terms[1].getCoef();
        double b = lhs_terms[0].getCoef();
        
        if (a == 0 && b != 0)
            // No solution
            std::cout << RED << "No solutions" << RESET << std::endl;
        else if (a == 0 && b == 0)
            // All are solution
            std::cout << GREEN << "All reals are solutions" << RESET << std::endl;
        else {
            // One solution
            std::cout << BLUE << "The solution is:" << std::endl;
            std::cout << -b / a << RESET << std::endl;
        }
    } else if (polynomial_degree == 2 && lhs_terms.size() == 3) {
        // calcule the result (ax^2 + bx + c = 0)
        double a = lhs_terms[2].getCoef();
        double b = lhs_terms[1].getCoef();
        double c = lhs_terms[0].getCoef();
        
        double delta = b * b - 4 * a * c;
        if (a == 0)
            // No solution
            std::cout << RED << "A=0, the equation is not quadratic" << RESET << std::endl;
        else if (delta < 0) {
            // -b/2a + i * sqrt(-delta) / 2a
            // -b/2a - i * sqrt(-delta) / 2a
            std::cout << BLUE << "Discriminant is strictly negative, the two solutions are:" << std::endl;
            std::cout << -b / (2 * a) << " + " << sqrt(-delta) / (2 * a) << " * i" << std::endl;
            std::cout << -b / (2 * a) << " - " << sqrt(-delta) / (2 * a) << " * i" << RESET << std::endl;
        } else if (delta == 0) {
            // One solution
            std::cout << BLUE << "Discriminant is equal to zero, the solution is:" << std::endl;
            std::cout << -b / (2 * a) << RESET << std::endl;
        } else {
            // Two solutions
            std::cout << BLUE << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout << (-b - sqrt(delta)) / (2 * a) << std::endl;
            std::cout << (-b + sqrt(delta)) / (2 * a) << RESET << std::endl;
        }
    } else if (polynomial_degree > 2)
        std::cout << RED << "The polynomial degree is stricly greater than 2, I can't solve."<< RESET << std::endl;
    else if (polynomial_degree < 0)
        std::cout << RED << "The polynomial degree is stricly less than 0, I can't solve."<< RESET << std::endl;
    else
        std::cout << RED << "The polynomial degree is not a round number or it is negative number, I can't solve."<< RESET << std::endl;
    return (0);
}