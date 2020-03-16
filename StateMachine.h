#pragma once
#include "State.h"
#include <memory>
#include <stack>
namespace AT
{
	typedef std::unique_ptr<State> StateRef;
	class StateMachine
	{
	public:
		void AddState(StateRef state,bool replacing = true);
		void RemoveState();
		void ProcessStateChanges();
		StateRef& CurrentState();
	private:
		std::stack <StateRef> _States;
		StateRef _newState;
		bool _Adding;
		bool _Removing;
		bool _replacing;
	};

}