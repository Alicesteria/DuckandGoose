#include "Containers.h"
#pragma once

/*
* How to use the System Interface
* 1) When creating your core system, your class will be within the namespace of Framework, and within it your
* class will inhterit the ISystem interface.
* 2) From there you can use the 
*/


namespace Framework
{
	class ISystem
	{
		public:

		///Systems can receive all message send to the Core. 
		///See Message.h for details.
		/// -------------------------------------------------------------------------------
		//virtual void SendMessage(Message* message) { UNREFERENCED_PARAMETER(message); };

		///All systems are updated every game frame.
		virtual void Update(float timeslice) = 0;

		///All systems provide a string name for debugging.
		virtual std::string GetName() = 0;

		///Initialize the system.
		virtual void Initialize() {};

		///All systems need a virtual destructor to have their destructor called 
		virtual ~ISystem() {}
	};
}