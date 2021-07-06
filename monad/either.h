//
// Created by comrade77 on 06.07.2021.
//

#ifndef CPP_MONAD_EITHER_H
#define CPP_MONAD_EITHER_H

#include "left.h"
#include "right.h"

namespace monad {
    template<typename L, typename  R>
    class Either {
        union {
            L left_value;
            R right_value;
        };

        bool const isLeft = false;

        constexpr explicit Either(Left<L> const& l);

        constexpr explicit Either(Right<R> const& r);

        Either(Either<L, R> &&e) noexcept;

    public:
        virtual ~Either();
    };
}


#endif//CPP_MONAD_EITHER_H
