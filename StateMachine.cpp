#include "StateMachine.h"
namespace AT
{
	void StateMachine::AddState(StateRef state, bool replacing)
	{
		_Adding = true;
		_newState = std::move(state);
		_replacing = replacing;
	}

	void StateMachine::RemoveState()
	{
		_Removing = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		if (!_States.empty() && _Removing)
		{
			_States.pop();
			if (!_States.empty())
			{
				_States.top()->resume();
			}
			_Removing = false;

		}
		if (_Adding)
		{
			if (!_States.empty())
			{
				if(_replacing)
					{
						_States.pop();
					}
				else
				{
					_States.top()->pause();
				}
			}
			_States.push(std::move(_newState));
			_States.top()->init();
			_Adding = false;

		}

	}

	StateRef& StateMachine::CurrentState()
	{
		return _States.top();
	}
}