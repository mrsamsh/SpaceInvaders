//
// StateGamePause.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 09.05.2026.
// Copyright © 2026 Usama Alshughry. All rights reserved.
//

#ifndef STATEGAMEPAUSE_HPP_
#define STATEGAMEPAUSE_HPP_

#include "State.hpp"

namespace si
{

class StateGamePause : public State
{
public:
  StateGamePause(StateManager& manager);
  virtual bool update(f32 const delta) override;
  virtual void draw() const override;
private:
};

} // namespace si

#endif // STATEGAMEPAUSE_HPP_
