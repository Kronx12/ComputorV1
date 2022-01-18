/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:28:29 by gbaud             #+#    #+#             */
/*   Updated: 2022/01/17 17:03:42 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Term.hpp"

Term::Term() : _coef(0), _exp(0) {}
Term::Term(Term const &src) : _coef(src.getCoef()), _exp(src.getExp()) {}
Term::Term(double coef, double exp) : _coef(coef), _exp(exp) {}
Term &Term::operator=(Term const &rhs) {
    if (this != &rhs) {
        this->_coef = rhs.getCoef();
        this->_exp = rhs.getExp();
    }
    return *this;
}

void Term::debug() {
    std::cout << "Term = coef(" << _coef << ") exp(" << _exp << ")" << std::endl;
}

double Term::getCoef() { return (_coef); }
double Term::getExp() { return (_exp); }

double Term::getCoef() const { return (_coef); }
double Term::getExp() const { return (_exp); }

double Term::addCoef(double coef) { return (_coef += coef); }

double Term::setCoef(double coef) { return (_coef = coef); }

Term::~Term() {}