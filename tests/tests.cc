#include <iostream>
#include <cstdint>
#include <sstream>
#include <memory>



#include <criterion/criterion.h>

#include "base.hh"
#include "bignum.hh"


using value_t = uint8_t;
using base_t = bistro::Base<value_t>;
using bignum_t = bistro::BigNum<value_t>;
using index_t = unsigned long long;

bignum_t a(10);
bignum_t b(10);

void(setup (void))
{
    a = bignum_t(10);
    b = bignum_t(10);
}

void teardown()
{

}

TestSuite(operations, .init = setup, .fini = teardown);

Test(operation, create_bignum)
{
    int test     = 0;
    size_t model = 0;
    index_t res = b.get_num_digits();
    cr_assert(res == model, "%ld != %ld", res, model);
}


Test(operation, insert_digit)
{
    int test     = 1;
    size_t model = 4;
    b.set_digit(3, 2);
    index_t res = b.get_num_digits();
    cr_assert(res == model, "%ld != %ld", res, model);
}



Test(operation, delete_digit)
{
    int test     = 2;
    size_t model = 0;
    b.set_digit(3, 2);
    b.set_digit(3, 0);
    index_t res = b.get_num_digits();
    cr_assert(res == model, "%ld != %ld", res, model);
}


Test(operation, add_small_digit)
{
    int test     = 3;
    size_t model = 5;
    a.set_digit(3, 2);
    b.set_digit(3, 3);
    auto x = bignum_t(10);
    x = a + b;
    unsigned d3 = x.get_digit(3);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}


Test(operation, add_digit_with_carried_value)
{
    int test     = 4;
    size_t model = 2;
    a.set_digit(3, 3);
    b.set_digit(3, 9);
    auto x = bignum_t(10);
    x = a + b;
    unsigned d3 = x.get_digit(3);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}


Test(operation, add_digit_with_carried_value_1)
{
    int test     = 5;
    size_t carried = 1;
    a.set_digit(3, 3);
    b.set_digit(3, 9);
    auto x = bignum_t(10);
    x = a + b;
    unsigned d3 = x.get_digit(4);
    cr_assert(d3 == carried, "%ld != %ld", d3, carried);
}

Test(operation, multiply_small_digit)
{
    int test     = 6;
    size_t model = 6;
    a.set_digit(3, 2);
    b.set_digit(3, 3);
    auto x = bignum_t(10);
    x = a * b;
    unsigned d3 = x.get_digit(5);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}


Test(operation, multiply_digit_with_carried_value)
{
    int test     = 7;
    size_t model = 2;
    a.set_digit(3, 3);
    b.set_digit(3, 4);
    auto x = bignum_t(10);
    x = a * b;
    unsigned d3 = x.get_digit(5);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}


Test(operation, multiply_digit_with_carried_value_1)
{
    int test     = 8;
    size_t carried = 1;
    a.set_digit(3, 3);
    b.set_digit(3, 4);
    auto x = bignum_t(10);
    x = a * b;
    unsigned d3 = x.get_digit(9);
    cr_assert(d3 == carried, "%ld != %ld", d3, carried);
}


Test(operation, test_add_equal)
{
    int test     = 9;
    size_t model = 7;
    a.set_digit(3, 3);
    b.set_digit(3, 4);
    a += b;
    unsigned d3 = a.get_digit(3);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}


Test(operation, test_add_equal_big)
{
    int test     = 10;
    size_t model = 4;
    a.set_digit(100000, 3);
    b.set_digit(10000, 4);
    a += b;
    unsigned d3 = a.get_digit(10000);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}

Test(operation, test_mult_equal)
{
    int test     = 11;
    size_t model = 2;
    a.set_digit(3, 3);
    b.set_digit(3, 4);
    a *= b;
    unsigned d3 = a.get_digit(7);
    cr_assert(d3 == model, "%ld != %ld", d3, model);
}

