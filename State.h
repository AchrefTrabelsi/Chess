#pragma once
#include "Definitions.h"
#include <thread>
namespace AT
{
	class State
	{
	public:
		void LoadNext()
		{
			nextstateloader = std::thread([](State* state) {state->loadnextstate(); },this);	
		}
		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;
		virtual void loadnextstate() = 0;
		virtual void init() = 0;
		void resume() {};
		void pause() {};
	protected:
		State* nextstate;
		std::thread nextstateloader;

	};

}