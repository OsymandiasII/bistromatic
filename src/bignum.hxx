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
        sign_ = true;
        base_ = b.get_base_num();
        index_t n = 0;
        if (!b.is_digit(tmp))
            throw std::length_error("Not a digit");
        else
        {
            set_digit(n, b.get_char_value(tmp));
            n++;
            while (in >> token)
            {
                if (!b.is_digit(token))
                    break;
                set_digit(n, b.get_char_value(token));
                n++; 
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
        if (i >= n)
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
            while( i >= set_.size())
            {
                set_.emplace_back(0);
            }
            set_[i] = d;
            auto n = set_.size() - 1;
            size_t x = 0;
            while(set_[n] == 0 && n > 0)
            {
                x++;
                n--; 
            }
            if (x > 0)
                set_.resize(set_.size() - x);
            if (set_.size() == 1 && set_[0] == 0)
                set_.resize(0);
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
        for (auto rit = set_.rbegin(); rit != set_.rend(); rit++)
            out << b.get_digit_representation(*rit);
        return out; 
    }

    template <typename T>
    typename BigNum<T>::self_t BigNum<T>::operator+(const self_t& other) const
    {
        digits_t result = digits_t();
        digit_t carried = 0;
        index_t l = set_.size();
        auto digit = 0;
        if (set_.size() < other.set_.size())
            l = other.set_.size();
        for (index_t a = 0; a < l; a++)
        {
            if (a >= set_.size())
                digit = other.set_[a] + carried;
            else if (a >= other.set_.size())
                digit = set_[a] + carried;
            else
                digit = other.set_[a] + set_[a] + carried;
            if (digit / base_ > 0)
            {
                carried = digit / base_;
                digit = digit % base_;
            }
            else
                carried = 0;
            result.emplace_back(0);
            result[a] = digit;
        }
        if (carried != 0)
        {
            result.emplace_back(0);
            result[result.size() - 1] = carried;
        }
        auto res =  BigNum(base_);
        if (!sign_ && !other.sign_)
            res.set_positive(false);
        index_t i = 0;
        for (auto it = result.begin(); it < result.end(); it++)
        {
            res.set_digit(i, *it);
            i++;
        }
        return res;
    }

    template <typename T>
    typename BigNum<T>::self_t& BigNum<T>::operator+=(const self_t& other)
    {
        digit_t carried = 0;
        while (set_.size() < other.set_.size())
            set_.emplace_back(0);
        auto digit = 0;
        index_t l = set_.size();
        for (index_t a = 0; a < l; a++)
        {
            set_[a] = other.set_[a] + set_[a] + carried;
            if (digit / base_ > 0)
            {
                carried = digit / base_;
                set_[a] = digit % base_;
                
            }
            else
                carried = 0;
        }
        if (carried != 0)
        {
            set_.emplace_back(0);
            set_[set_.size() - 1] = carried;
        }
        return *this;
    }
    
    template <typename T>
    typename BigNum<T>::self_t BigNum<T>::operator*(const self_t& other) const
    {
        auto res =  BigNum(base_);
        digits_t result = digits_t();
        digit_t carried = 0;
        auto digit = 0;
        auto num1 = other.clone();
        auto num2 = this->clone();
        if (set_.size() < other.set_.size())
        {
            num1 = this->clone();
            num2 =  other.clone();
        }
        index_t run  = 0;
        for (auto it1 = num1.set_.begin() ; it1 != num1.set_.end(); it1++)
        {
            auto tmp_res =  BigNum(base_);
            digits_t tmp = digits_t();
            digit_t mul = *it1;
            index_t a = 0;
            for (auto it2 = num2.set_.begin() ; it2 != num2.set_.end(); it2++)
            {
                digit_t mul2 = *it2;
                for (index_t j = 0; j < run ; j++)
                {
                    tmp.emplace_back(0);
                    a++;
                }
                digit = mul * mul2 + carried;
                if (digit / base_ > 0)
                {
                    carried = digit / base_;
                    digit = digit % base_;
                }
                else
                    carried = 0;
                tmp.emplace_back(0);
                tmp[a] = digit;
                a++;
            }
            if (carried != 0)
            {
                tmp.emplace_back(0);
                tmp[tmp.size() - 1] = (carried);
            }
            run++;
            if (!sign_ && !other.sign_)
                res.set_positive(false);
            index_t i = 0;
            for (auto it = result.begin(); it != result.end(); it++)
            {
                res.set_digit(i, *it);
                i++;
            }
            i = 0;
            for (auto it = tmp.begin(); it != tmp.end(); it++)
            {
                tmp_res.set_digit(i, *it);
                i++;
            }
            res += tmp_res;
        }
        return res;
    }


    template <typename T>
    typename BigNum<T>::self_t& BigNum<T>::operator*=(const self_t& other)
    {
        auto res =  BigNum(base_);
        digits_t result = digits_t();
        digit_t carried = 0;
        auto digit = 0;
        auto num1 = this->clone();
        auto num2 =  other.clone();
        index_t run  = 0;
        for (auto it1 = num1.set_.begin() ; it1 != num1.set_.end(); it1++)
        {
            auto tmp_res =  BigNum(base_);
            digits_t tmp = digits_t();
            digit_t mul = *it1;
            index_t a = 0;
            for (auto it2 = num2.set_.begin() ; it2 != num2.set_.end(); it2++)
            {
                digit_t mul2 = *it2;
                for (index_t j = 0; j < run ; j++)
                {
                    tmp.emplace_back(0);
                    a++;
                }
                digit = mul * mul2 + carried;
                if (digit / base_ > 0)
                {
                    carried = digit / base_;
                    digit = digit % base_;
                }
                else
                    carried = 0;
                tmp.emplace_back(0);
                tmp[a] = digit;
                a++;
            }
            if (carried != 0)
            {
                tmp.emplace_back(0);
                tmp[tmp.size() - 1] = (carried);
            }
            run++;
            index_t i = 0;
            for (auto it = set_.begin(); it != set_.end(); it++)
            {
                this->set_digit(i, *it);
                i++;
            }
            i = 0;
            for (auto it = tmp.begin(); it != tmp.end(); it++)
            {
                tmp_res.set_digit(i, *it);
                i++;
            }
            *this += tmp_res;
        }
        return *this;
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
