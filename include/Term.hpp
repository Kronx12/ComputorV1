/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:30:23 by gbaud             #+#    #+#             */
/*   Updated: 2022/01/17 17:03:23 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_CPP
#define TERM_CPP

#include <iostream>
#include <iomanip>

class Term {
    public:
        Term();
        Term(Term const &);
        Term(double, double);        
        Term &operator=(Term const &);
        
        void debug();
        
        double getCoef();
        double getExp();
        double getCoef() const;
        double getExp() const;
        
        double addCoef(double coef);
        
        double setCoef(double coef);

        ~Term();
        
    private:
        double _coef;
        double _exp;
};

#endif