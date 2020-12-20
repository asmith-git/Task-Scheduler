//MIT License
//
//Copyright(c) 2020 Adam G. Smith
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef ASMITH_SCHEDULER_SCHEDULER_EXAMPLE_HPP
#define ASMITH_SCHEDULER_SCHEDULER_EXAMPLE_HPP

#include <atomic>
#include <thread>
#include "asmith/TaskScheduler/Scheduler.hpp"

namespace asmith {

	class ExampleThread {
	private:
		enum : uint32_t {
			COMM_DISABLED,
			COMM_EXECUTE,
			COMM_EXIT
		};
		std::thread _thread;
		std::atomic_uint32_t _comm_flag;
		Scheduler& _scheduler;
	public:
		ExampleThread(Scheduler& scheduler);
		~ExampleThread();

		bool Start();
		bool Stop();
		bool Pause();
		bool Resume();
	};

	typedef Scheduler ExampleSchedulerUnthreaded;

	class ExampleSchedulerSingleThreaded final : public Scheduler {
	private:
		ExampleThread _thread;
	public:
		ExampleSchedulerSingleThreaded();
		virtual ~ExampleSchedulerSingleThreaded();
	};

	class ExampleSchedulerMultiThreaded final : public Scheduler {
	private:
		ExampleThread _threadA;
		ExampleThread _threadB;
		ExampleThread _threadC;
		ExampleThread _threadD;
	public:
		ExampleSchedulerMultiThreaded();
		virtual ~ExampleSchedulerMultiThreaded();
	};
}

#endif