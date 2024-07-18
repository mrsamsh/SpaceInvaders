//
// State.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef STATE_HPP_
#define STATE_HPP_

#include "MyTypes.hpp"

namespace si
{

class StateManager;

enum class StateID
{
  Start,
  Game,
  Clear,
  Pause,
  GameOver,
  None
};

class State
{
public:
  State(StateManager& manager, StateID id)
  : m_manager{manager}
  , m_id{id} { }

  virtual bool update(f32 const delta) = 0;
  virtual void draw() const = 0;

  StateID getId() const
  {
    return m_id;
  }

  virtual ~State() { }

protected:
  StateManager& m_manager;
  StateID m_id;
};

} // namespace si

#endif // STATE_HPP_
