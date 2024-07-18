//
// StateManager.cpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#include "StateManager.hpp"

namespace si
{

void StateManager::update(f32 const delta)
{
  for (auto it = m_states.rbegin(); it != m_states.rend(); ++it)
  {
    if ((*it)->update(delta) == false)
      break;
  }
  applyPendingChanges();
}

void StateManager::draw() const
{
  for (auto it = m_states.begin(); it != m_states.end(); ++it)
    (*it)->draw();
}

void StateManager::requestStateChange(StateChange change, StateID id)
{
  m_pendingChanges.push_back({change, id});
}

void StateManager::applyPendingChanges()
{
  for (auto& [change, id] : m_pendingChanges)
  {
    switch(change)
    {
    case StateChange::Push: {
      pushState(id);
    } break;
    case StateChange::Pop: {
      popState();
    } break;
    case StateChange::Clear: {
      clear();
    } break;
    }
  }
  m_pendingChanges.clear();
}

void StateManager::pushState(StateID id)
{
  m_states.push_back(m_stateFactory[id](*this));
}

void StateManager::popState()
{
  State* state = m_states.back();
  delete state;
  m_states.pop_back();
}

void StateManager::clear()
{
  for (auto* state : m_states)
  {
    delete state;
  }
  m_states.clear();
}

} // namespace si
