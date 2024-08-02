//
// ResourcePath.mm
// SpaceInvaders
//
// Created by Usama Alshughry 02.08.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "ResourcePath.hpp"

#import <Foundation/Foundation.h>

namespace si
{

char const* GetResourcePath(std::string_view filename)
{
  static char buffer[512] = {0};
  @autoreleasepool
  {
    memset(buffer, 0, 512);
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *path = [NSString stringWithFormat:@"%@/%s", [bundle resourcePath], filename.data()];
    memcpy(buffer, [path UTF8String], [path length]);
  }
  return buffer;
}

} // namespace si
