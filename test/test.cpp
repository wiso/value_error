#include <cmath>

#include "gtest/gtest.h"

#include "../value_error.h"

TEST(ValueError, Construction) {
    ValueError(2.0, 0.1);
    ValueError(-2.0, 1.0);
}

TEST(BasicOperation, Sum)
{
    ValueError a(2.0, 0.1);
    ValueError b(3.0, 0.5);
    ValueError c = a + b;
    ASSERT_DOUBLE_EQ(c.value(), a.value() + b.value());
    ASSERT_DOUBLE_EQ(c.stat_error(), sqrt(a.stat_error() * a.stat_error() + b.stat_error() * b.stat_error()));
	
}
