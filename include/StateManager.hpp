//
// StateManager.hpp
// SpaceInvaders
//
// Created by Usama Alshughry 13.07.2024.
// Copyright © 2024 Usama Alshughry. All rights reserved.
//

#ifndef STATEMANAGER_HPP_
#define STATEMANAGER_HPP_

#include "State.hpp"

#include <map>
#include <vector>
#include <deque>
#include <concepts>

namespace si
{

enum class StateChange { Push, Pop, Clear };

class StateManager
{
public:
  template <typename SomeState>
  requires (std::is_base_of_v<State, SomeState>)
  void registerState(StateID id)
  {
    if (m_stateFactory.find(id) == m_stateFactory.end())
    {
      m_stateFactory[id] = [](StateManager& manager) -> State* {
        return new SomeState(manager);
      };
    }
  }

  void update(f32 const delta);
  void draw() const;

  void requestStateChange(StateChange change, StateID id = StateID::None);

private:
  void pushState(StateID id);
  void popState();
  void clear();

  void applyPendingChanges();
  std::map<StateID, std::function<State*(StateManager&)>> m_stateFactory;
  std::vector<std::pair<StateChange, StateID>> m_pendingChanges;
  std::deque<State*> m_states;
};

} // namespace si

#endif // STATEMANAGER_HPP_
