
namespace bistro
{
    template <typename T>
    BigNum::BigNum(std::size_t base)
        : base_(base)
        , set_ = digits_t 
    {}

    template <typename T, typename Base>
    BigNum::BigNum(std::istream& in, const Base& b)
    {
        std::char token;
        std::char tmp = in >> token;
        indet_t n = 0;
        if (!b.is_digit(tmp))
            throw std::length_error(tmp);           //maybe deref char
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
    }

    template <typename T>
    BigNum::self_t BigNum::clone() const
    {
        
    }

    template <typename T>
    BigNum::index_t BigNum::get_num_digits() const
    {
          index_t l = base_.size();
          return l;
    }

    template <typename T>
    BigNum::digit_t BigNum::get_digit(index_t i) const
    {
        index_t n = get_num_digits();
        if (i > n)
            throw std::out_of_range(i);
        else
        {
            return base_[i];
        }
    }

    template <typename T>
    void BigNum::set_digit(index_t i, digit_t d)
    {
        if (d >= base_)
            throw std::invalid_argument(d);
        else
        {
            base_[i] = d;
            //strip or add 0
        }
    }

    template <typename T>
    bool BigNum::is_positive() const
    {
        if (sign_)
            return sign_;
        return !sign_;
    }

    template <typename T>
    void BigNum::set_positive(bool p)
    {
        sign_ = p;
    }


    template <typename Base>
    std::ostream& BigNum::print(std::ostream& out, const Base& b) const
    {
        for (auto rit = this.rbegin(); rit != this.rend(); ++rit)
            out << b.get_digit_representation(*rit); 
    }

    template <typename Base>
    bool BigNum::Boperator>(const self_t& other) const
    {
        if (this.get_num_digits() != other.get_num_digits())
            return false;
        if (this.sign_ != other.sign_)
            return false;

        auto rit = this.rbegin();
        auto rother = other.rbegin();
        for (; rit < this.rend() || rother < rother.rend; it++ ; rother++)
        {
            if (*rit > *rother)
                return true;
        }
        return false;
    }

    template <typename Base>
    bool BigNum::operator==(const self_t& other) const
    {
        if (this.get_num_digits() != other.get_num_digits())
            return false;
        if (this.sign_ != other.sign_)
            return false;

        auto rit = this.rbegin();
        auto rother = other.rbegin();
        for (; rit < this.rend() || rother < rother.rend; it++ ; rother++)
        {
            if (*rit != *rother)
                return false;
        }
        return true;
    }

    template <typename Base>
    explicit BigNum::operator bool() const
    {
        return this.size() != 0;
    }
};
