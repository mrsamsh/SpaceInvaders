//
// ResourcePath.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 02.08.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef RESOURCEPATH_HPP_
#define RESOURCEPATH_HPP_

#include <string>
#include <string_view>

namespace si
{

char const* GetResourcePath(std::string_view filename);

} // namespace si

#endif // RESOURCEPATH_HPP_
