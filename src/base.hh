#pragma once

#include <cstdint>
#include <initializer_list>
#include <map>


namespace bistro
{
    /**
    ** Base class.
    **
    ** This class represents a numerical base, along with the means to convert
    ** single digits to and from textual representation.
    **
    ** A valid representation type (for \a Char) has the following properties:
    **   - it can be copied.
    **   - it can be output (with \c operator<< )
    **   - it can be compared to itself (with \c operator== )
    **   - it can be compared to a \c char (with \c operator== )
    **   - it provides a \c hash functor.
    **/
    template <typename Value = uint8_t, typename Char = char>
    class Base
    {
    public:
        /// A digit in textual representation.
        using char_t = Char;

        /// A digit in "value" representation.
        using value_t = Value;

        /// Default constructor.
        Base()
        {
            list_ = std::map<value_t, char_t>();
        }

        /// Construct a base from an initializer list.
        Base(std::initializer_list<char_t> list)
        {
            for (auto it = list.begin(); it < list.end(); it++)
                add_digit(*it);
            //throw "Not implemented";
        }

        /// Get the numerical base represented.
        size_t get_base_num() const
        {
            return list_.size();
        }

        /**
        ** Add a the representation of a digit.
        **
        ** This will match the representation \a repr of the digit with the
        ** smallest unmatched value, thus increasing the size of the base by 1.
        **
        ** Throws invalid_argument if the representation is reserved (for an
        ** operator) or already matched).
        **/
        void add_digit(char_t repr)
        {
            if (is_operator(repr) || is_digit(repr))
                throw std::invalid_argument("Not a valid representation");
            else
            {
                list_.insert(std::pair<value_t, char_t>(value_,repr));
                value_++;
            }
        }

        /// Check wether there is a match for the character representation \a c.
        bool is_digit(char_t c) const
        {
            for (auto it = list_.begin(); it != list_.end(); it++)
            {
                if (c == it->second)
                    return true;
            }
            return false;
        }

        /**
        ** Check wether the character representation \a c is reserved for an
        ** operator.
        **/
        static bool is_operator(char_t c)
        {
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%'
                || c == '=')
                return true;
            return false;
        }

        /**
        ** Get the representation for the value \a i.
        **
        ** \throw std::out_of_range if the value is not in the base.
        **/
        char_t get_digit_representation(value_t i) const
        {
            if (list_.find(i) == list_.end())
                throw std::out_of_range("Out of range");
            else
            {
                char_t iterator = list_.find(i)->second;
                return iterator;
            }
        }

        /**
        ** Get the value for the representation \a i.
        **
        ** \throw std::out_of_range if the representation is not in the base.
        **/
        value_t get_char_value(char_t r) const
        {
            for (auto it = list_.begin(); it != list_.end(); it++)
            {
                if (r == it->second)
                    return it->first;
            }
            throw std::out_of_range("out of range");
        }

    private:
        std::map<value_t, char_t> list_;
        value_t value_ = 0;
    };

}
