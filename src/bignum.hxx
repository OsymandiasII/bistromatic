
namespace bistro
{
    template <typename T>
    BigNum::BigNum(std::size_t base)
        : base_(base)
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
        
    }

    template <typename T>
    bool BigNum::is_positive() const
    {
        
    }

    template <typename T>
    void BigNum::set_positive(bool p)
    {
        
    }

    template <typename Base>
    std::ostream& print(std::ostream& out, const Base& b) const
    {
        
    }
};
