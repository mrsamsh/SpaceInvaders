//
// StateStart.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef STATESTART_HPP_
#define STATESTART_HPP_

#include "State.hpp"

namespace si
{

class StateStart : public State
{
public:
  StateStart(StateManager& manager);
  virtual bool update(f32 const delta) override;
  virtual void draw() const override;
};

} // namespace si

#endif // STATESTART_HPP_
