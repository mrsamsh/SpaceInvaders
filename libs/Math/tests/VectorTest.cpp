//
// vector_test.cpp
// ge4
//
// Created by Usama Alshughry 27.06.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Vector.hpp"

#include <iostream>

using namespace math;
using test_t = f64;

void test(bool x)
{
  if (!x) exit(-1);
}

int main()
{
  using vec2 = vec2T<test_t>;
  using vec3 = vec3T<test_t>;
  using vec4 = vec4T<test_t>;

  vec2::value_type x1 = 1.004;
  vec2::value_type y1 = -2.99334;
  vec2::value_type x2 = 100.2994;
  vec2::value_type y2 = -14.3001;
  vec2::value_type z1 = -0.0002;
  vec2::value_type z2 = 14567634;
  vec2::value_type w1 = 9.22;
  vec2::value_type w2 = M_PI;

  {
    vec2 v1(x1, y1);
    vec2 v2(x2, y2);

    test((v1+v2).x == x1+x2);
    test((v1+v2).y == y1+y2);

    test((v1-v2).x == x1-x2);
    test((v1-v2).y == y1-y2);

    test((v1*v2).x == x1*x2);
    test((v1*v2).y == y1*y2);

    test((v1/v2).x == x1/x2);
    test((v1/v2).y == y1/y2);

    test(v1 * x1 == vec2(x1 * x1, y1 * x1));
    test(v1 / x1 == vec2(x1 / x1, y1 / x1));

    test(v2 * x1 == vec2(x2 * x1, y2 * x1));

    {
      vec2::value_type scalar = 1 / x1;
      test(v2 / x1 == vec2(x2 * scalar, y2 * scalar));
      scalar = 1 / y1;
      test(v2 / y1 == vec2(x2 * scalar, y2 * scalar));
    }

    test(v1.length2() == x1 * x1 + y1 * y1);
    test(v1.length() == std::sqrt(x1 * x1 + y1 * y1));
    test(v2.length() == std::sqrt(x2 * x2 + y2 * y2));

    {
      vec2::value_type scalar = 1 / v1.length();
      test(v1.normalized() == vec2(v1.x * scalar, v1.y * scalar));
    }
    test(math::dotProduct(v1, v2) == x1 * x2 + y1 * y2);
  }

  {
    vec3 v1(x1, y1, z1);
    vec3 v2(x2, y2, z2);

    test((v1+v2).x == x1+x2);
    test((v1+v2).y == y1+y2);
    test((v1+v2).z == z1+z2);

    test((v1-v2).x == x1-x2);
    test((v1-v2).y == y1-y2);
    test((v1-v2).z == z1-z2);

    test((v1*v2).x == x1*x2);
    test((v1*v2).y == y1*y2);
    test((v1*v2).z == z1*z2);

    test((v1/v2).x == x1/x2);
    test((v1/v2).y == y1/y2);
    test((v1/v2).z == z1/z2);

    test(v1 * x1 == vec3(x1 * x1, y1 * x1, z1 * x1));
    {
      vec2::value_type scalar = 1 / x1;
      test(v1 / x1 == vec3(x1 * scalar, y1 * scalar, z1 * scalar));
    }

    test(v2 * x1 == vec3(x2 * x1, y2 * x1, z2 * x1));

    {
      vec2::value_type scalar = 1 / x1;
      test(v2 / x1 == vec3(x2 * scalar, y2 * scalar, z2 * scalar));
      scalar = 1 / y1;
      test(v2 / y1 == vec3(x2 * scalar, y2 * scalar, z2 * scalar));
    }

    test(v1.length2() == x1 * x1 + y1 * y1 + z1 * z1);
    test(v1.length() == std::sqrt(x1 * x1 + y1 * y1 + z1 * z1));
    test(v2.length() == std::sqrt(x2 * x2 + y2 * y2 + z2 * z2));

    {
      vec3::value_type scalar = 1 / v1.length();
      test(v1.normalized() == vec3(v1.x * scalar, v1.y * scalar, v1.z * scalar));
    }

    test(math::dotProduct(v1, v2) == x1 * x2 + y1 * y2 + z1 * z2);
  }

  {
    vec4 v1(x1, y1, z1, w1);
    vec4 v2(x2, y2, z2, w2);

    test((v1+v2).x == x1+x2);
    test((v1+v2).y == y1+y2);
    test((v1+v2).z == z1+z2);
    test((v1+v2).w == w1+w2);

    test((v1-v2).x == x1-x2);
    test((v1-v2).y == y1-y2);
    test((v1-v2).z == z1-z2);
    test((v1-v2).w == w1-w2);

    test((v1*v2).x == x1*x2);
    test((v1*v2).y == y1*y2);
    test((v1*v2).z == z1*z2);
    test((v1*v2).w == w1*w2);

    test((v1/v2).x == x1/x2);
    test((v1/v2).y == y1/y2);
    test((v1/v2).z == z1/z2);
    test((v1/v2).w == w1/w2);

    test(v1 * x1 == vec4(x1 * x1, y1 * x1, z1 * x1, w1 * x1));
    {
      vec4::value_type scalar = 1 / x1;
      test(v1 / x1 == vec4(x1 * scalar, y1 * scalar, z1 * scalar, w1 * scalar));
    }

    test(v2 * x1 == vec4(x2 * x1, y2 * x1, z2 * x1, w2 * x1));

    {
      vec4::value_type scalar = 1 / x1;
      test(v2 / x1 == vec4(x2 * scalar, y2 * scalar, z2 * scalar, w2 * scalar));
      scalar = 1 / y1;
      test(v2 / y1 == vec4(x2 * scalar, y2 * scalar, z2 * scalar, w2 * scalar));
    }

    test(v1.length2() == x1 * x1 + y1 * y1 + z1 * z1 + w1 * w1);
    test(v1.length() == std::sqrt(x1 * x1 + y1 * y1 + z1 * z1 + w1 * w1));
    test(v2.length() == std::sqrt(x2 * x2 + y2 * y2 + z2 * z2 + w2 * w2));

    {
      vec4::value_type scalar =  1 / v1.length();
      test(v1.normalized() == vec4(v1.x * scalar, v1.y * scalar, v1.z * scalar, v1.w * scalar));
    }

    test(math::dotProduct(v1, v2) == x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2);
  }
}
