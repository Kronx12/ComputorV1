/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 18:00:27 by gbaud             #+#    #+#             */
/*   Updated: 2021/05/29 20:45:37 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Term.hpp"

Term::Term()
    : _exp(0), _value(0) {}
    
Term::Term(const Term &other)
    : _exp(other._exp), _value(other._value) {}
    
Term &Term::operator=(const Term &other) {
    if (this == &other) return (*this);
    this->~Term();
    this->setExp(other._exp);
    this->setValue(other._value);
    return (*this);
}

void Term::setExp(int exp) { this->_exp = exp; }
void Term::setValue(double value) { this->_value = value; }
int Term::getExp() { return (this->_exp); }
double Term::getValue() { return (this->_value); }

void Term::debug() {
    if (_exp > 0) {
        if (_value >= 0)
            std::cout << "+ " << _value;
        else
            std::cout << "- " << _value * -1;
    } else
        std::cout << _value;
    std::cout << " * X^" << _exp << " ";
}

Term::~Term() {}