//
// StateGameOver.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 14.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef STATEGAMEOVER_HPP_
#define STATEGAMEOVER_HPP_

#include "State.hpp"

namespace si
{

class StateGameOver : public State
{
public:
  StateGameOver(StateManager& manager);
  virtual bool update(f32 const delta) override;
  virtual void draw() const override;
private:
  f32 m_accumulator = 0;
};

} // namespace si

#endif // STATEGAMEOVER_HPP_
