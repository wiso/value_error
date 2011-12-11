#include <cmath>

#include "gtest/gtest.h"

#include "../value_error.h"

template<typename T>
T sum_square(T a, T b)
{
    return sqrt(a * a + b * b);
}

TEST(ValueError, Construction) {
    ValueError(2.0, 0.1);
    ValueError(-2.0, 1.0);
}

TEST(BasicOperation, Sum)
{
    ValueErrorTemplate<double> a(2.0, 0.1);
    ValueErrorTemplate<double> b(3.0, 0.5);
    ValueErrorTemplate<double> c = a + b;
    ASSERT_DOUBLE_EQ(c.value(), a.value() + b.value());
    ASSERT_DOUBLE_EQ(c.stat_error(), sum_square(a.stat_error(), b.stat_error()));
    c = a - b;
    ASSERT_DOUBLE_EQ(c.value(), a.value() - b.value());
    ASSERT_DOUBLE_EQ(c.stat_error(), sum_square(a.stat_error(), b.stat_error()));
}

TEST(BasicOperation, ScalarMult)
{
    ValueErrorTemplate<double> a(2.0, 0.1);
    ValueErrorTemplate<double> c = a * 3.;
    ASSERT_DOUBLE_EQ(c.value(), a.value() * 3.);
    ASSERT_DOUBLE_EQ(c.stat_error(), 3 * a.stat_error());

    c = a * (-2.);
    ASSERT_DOUBLE_EQ(c.value(), a.value() * (-2.));
    ASSERT_DOUBLE_EQ(c.stat_error(), 2 * a.stat_error());

    c = a / (-3.);
    ASSERT_DOUBLE_EQ(c.value(), a.value() / (-3.));
    ASSERT_DOUBLE_EQ(c.stat_error(), a.stat_error() / 3.);
}

TEST(BasicOperation, Mult)
{
    ValueErrorTemplate<double> a(2.0, 0.1);
    ValueErrorTemplate<double> b(-3.0, 0.5);
    ValueErrorTemplate<double> c = a * b;
    ASSERT_DOUBLE_EQ(c.value(), a.value() * b.value());
    ASSERT_DOUBLE_EQ(c.stat_error(), (sum_square(a.stat_error() / a.value(), b.stat_error() / b.value())) * fabs(c.value()));
    c = a / b;
    ASSERT_DOUBLE_EQ(c.value(), a.value() / b.value());
    ASSERT_DOUBLE_EQ(c.stat_error(), (sum_square(a.stat_error() / a.value(), b.stat_error() / b.value())) * fabs(c.value()));
}

TEST(OtherFunctions, Exp)
{
    ValueErrorTemplate<double> a(-2.0, 0.1);
    ValueErrorTemplate<double> c = exp(a);
    ASSERT_DOUBLE_EQ(c.value(), exp(a.value()));
    ASSERT_DOUBLE_EQ(c.stat_error(), fabs(exp(a.value())) * a.stat_error());
}

TEST(OtherFunctions, Log)
{
    ValueErrorTemplate<double> a(2.0, 0.1);
    ValueErrorTemplate<double> c = log(a);
    ASSERT_DOUBLE_EQ(c.value(), log(a.value()));
    ASSERT_DOUBLE_EQ(c.stat_error(), fabs(1. / a.value()) * a.stat_error());
}

TEST(OtherFunctions, Trigonometric)
{
    ValueErrorTemplate<double> a(2.0, 0.1);
    ValueErrorTemplate<double> c = sin(a);
    ASSERT_DOUBLE_EQ(c.value(), sin(a.value()));
    ASSERT_DOUBLE_EQ(c.stat_error(), fabs(cos(a.value()) * a.stat_error()));
    c = cos(a);
    ASSERT_DOUBLE_EQ(c.value(), cos(a.value()));
    ASSERT_DOUBLE_EQ(c.stat_error(), fabs(sin(a.value()) * a.stat_error()));
    c = tan(a);
    ASSERT_DOUBLE_EQ(c.value(), tan(a.value()));
    ASSERT_DOUBLE_EQ(c.stat_error(), fabs((1. + tan(a.value()) * tan(a.value())) * a.stat_error()));
}

