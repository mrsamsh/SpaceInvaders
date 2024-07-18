//
// StateClear.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "State.hpp"

#ifndef STATECLEAR_HPP_
#define STATECLEAR_HPP_

namespace si
{

class StateClear : public State
{
public:
  StateClear(StateManager& manager);
  virtual bool update(f32 const delta) override;
  virtual void draw() const override;
private:
  f32 m_accumulator;
};

} // namespace si

#endif // STATECLEAR_HPP_
