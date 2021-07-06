//
// Created by comrade77 on 06.07.2021.
//

#ifndef CPP_MONAD_EITHER_H
#define CPP_MONAD_EITHER_H

#include "left.h"
#include "right.h"

namespace monad {
    template<typename L, typename R>
    class Either {
    public:
        union {
            L left_value;
            R right_value;
        };

        bool const isLeft = false;

        constexpr explicit Either(Left<L> const &l) : left_value{l.value}, isLeft{true} {};

        constexpr explicit Either(Right<R> const &r) : right_value{r.value}, isLeft{false} {};

        explicit Either(Left<L> &&l) : left_value{std::forward<L>(l.value)}, isLeft{true} {};

        explicit Either(Right<R> &&r) : right_value{std::forward<R>(r.value)}, isLeft{false} {};

        constexpr Either(Either<L, R> const &either) : isLeft(either.isLeft) {
            if (isLeft) {
                new (&left_value) L(either.left_value);
            } else {
                new (&right_value) R(either.right_value);
            }
        }

        virtual ~Either() {
            if (isLeft) {
                left_value.~L();
            } else {
                right_value.~R();
            }
        }
    };
}// namespace monad


#endif//CPP_MONAD_EITHER_H
