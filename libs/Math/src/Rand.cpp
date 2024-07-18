//
// Rand.cpp
// ge4
//
// Created by Usama Alshughry 27.06.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "Rand.hpp"

namespace math
{

std::random_device rng::rd;
std::mt19937 rng::gen(rd());

} // namespace math
