/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 18:00:44 by gbaud             #+#    #+#             */
/*   Updated: 2021/05/29 20:44:48 by gbaud            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_HPP
#define TERM_HPP

#include "global.hpp"

class Term {
    private:
        int _exp;
        double _value;

    public:
        Term();
        Term(const Term &);
        ~Term();
        Term &operator=(const Term &);

        void setExp(int);
        void setValue(double);

        int getExp();
        double getValue();

        void debug();
};

#endif