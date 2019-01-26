#pragma once

#include "bignum.hh"

namespace bistro
{
    template <typename T>
    BigNum<T>::BigNum(std::size_t base)
    {
        base_ = base;
        set_ = digits_t();
        sign_ = true;
    }

    template <typename T>
    template <typename Base>
    BigNum<T>::BigNum(std::istream& in, const Base& b)
    {
        char token;
        char tmp = in.get();
        index_t n = 0;
        if (!b.is_digit(tmp))
            throw std::length_error("Not a digit");           //maybe deref char
        else
        {
            set_digit(n, token);
            n++;
            while (in >> token)
            {
                if (b.is_digit(token))
                {
                    set_digit(n, token);
                    n++; 
                }
            }
        }
        std::reverse(set_.begin(),set_.end()); 
    }

    template <typename T>
    typename BigNum<T>::self_t BigNum<T>::clone() const
    {
        self_t res(base_);
        res.set_ = set_;
        res.sign_ = sign_;
        return res;
    }

    template <typename T>
    typename BigNum<T>::index_t BigNum<T>::get_num_digits() const
    {
          index_t l = set_.size();
          return l;
    }

    template <typename T>
    typename BigNum<T>::digit_t BigNum<T>::get_digit(index_t i) const
    {
        index_t n = get_num_digits();
        if (i > n)
            throw std::out_of_range("Index out of range");
        else
        {
            return set_[i];
        }
    }

    template <typename T>
    void BigNum<T>::set_digit(index_t i, digit_t d)
    {
        if (d >= base_)
            throw std::invalid_argument("Invalide argument");
        else
        {
            while( i > set_.size())
            {
                set_.emplace_back(0);
            }
            set_[i] = d;
        }
    }

    template <typename T>
    bool BigNum<T>::is_positive() const
    {
        if (sign_)
            return sign_;
        return !sign_;
    }

    template <typename T>
    void BigNum<T>::set_positive(bool p)
    {
        sign_ = p;
    }

    template <typename T>
    template <typename Base>
    std::ostream& BigNum<T>::print(std::ostream& out, const Base& b) const
    {
        for (auto rit = set_.rbegin(); rit != set_.rend(); ++rit)
            out << b.get_digit_representation(*rit);
        return out; 
    }

    template <typename T>
    typename BigNum<T>::self_t BigNum<T>::operator+(const self_t& other) const
    {
        digits_t num1 = set_;
        digits_t num2 = other;
        digits_t result = digits_t();
        digit_t carried = 0;
        if (num1.size() < num2.size())
        {
            num1 = other;
            num2 = set_;
        }
        for (auto it1 = num1.begin(); it1 < num1.end(); it1++)
        {
            for (auto it2 = num2.begin(); it2 < num2.end(); it2++)
            {
                auto digit = it1 + it2 + carried;
                if (digit / base_ > 0)
                {
                    carried = digit % base_;
                    digit = digit / base_;
                }
                else
                    carried = 0;
            }
        }
    }

    template <typename T>
    bool BigNum<T>::operator>(const self_t& other) const
    {
        if (this.get_num_digits() != other.get_num_digits())
            return false;
        if (this.sign_ != other.sign_)
            return false;

        auto rit = this.rbegin();
        auto rother = other.rbegin();
        for (; rit < this.rend() || rother < rother.rend; rit++)
        {
            if (*rit > *rother)
                return true;
            rother++;
        }
        return false;
    }

    template <typename T>
    bool BigNum<T>::operator==(const self_t& other) const
    {
        if (this.get_num_digits() != other.get_num_digits())
            return false;
        if (this.sign_ != other.sign_)
            return false;

        auto rit = this.rbegin();
        auto rother = other.rbegin();
        for (; rit < this.rend() || rother < rother.rend; rit++)
        {
            if (*rit != *rother)
                return false;
            rother++;
        }
        return true;
    }

    template <typename T>
    BigNum<T>::operator bool() const
    {
        return this.size() != 0;
    }
}
