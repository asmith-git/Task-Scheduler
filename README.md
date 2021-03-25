# Task-Scheduler
This C++ library provides code for scheduling and parallel execution of tasks.
This is an improved version of my older [multithread-task](https://github.com/asmith-git/multithread-task) project, which itself is a port of the task management system in a game engine I wrote a number of years ago.


## Usage Examples
### Creating a Task
If none of the optional extensions are enabled, then creating a custom Task is easy. All we need to do is override the OnExecution function with our custom behaviour.
```cpp
// This task prints a message to std::cout, fairly simple
class MyTask final : public asmith::Task {
private:
	std::string _message;
protected:
	void OnExecution() final {
		std::cout << _message << std::endl;
	}
public:
	MyTask(std::string message) :
		Task(),
		_message(std::move(message))
	{}

	virtual ~MyTask() {

	}

};
```
### Scheduling Tasks
Now we have a task to run, we can look at how scheduling works.
```cpp
int main{

	// First we need to create the task scheduler that will run tasks
	asmith::ExampleSchedulerSingleThreaded scheduler;

	{
		// Now let's make some tasks
		MyTask task1("Hello World!");
		MyTask task2("This is another task");

		// We can send the tasks to the scheduler and they will run in parallel
		scheduler.Schedule(task1);
		scheduler.Schedule(task2);

		// We can do something else on the thread now
    		std::cout << "This is parallel with tasks" << std::endl;

		// Now let's wait for the tasks to finish executing
		task1.Wait();
		task2.Wait();
    
    		std::cout << "All tasks complete" << std::endl;
	}
}
```
### Simplifying The Code
If we don't mind adding a small overhead to task execution then we can simplify it so that we don't need to write a whole class. We can instead use TaskFunctional to pass a std::function, lambda or a C function pointer into the scheduler.
```cpp
int main{

	// First we need to create the task scheduler that will run tasks
	asmith::ExampleSchedulerSingleThreaded scheduler;

	{
		// Use a more friendly name
		typedef asmith::TaskFunctional<std::function<void()>> EasyTask;

		// We can program the tasks to do anything we want now, but these ones will
		// do the same thing as MyTask
		EasyTask task1([]()->void { std::cout << "Hello World!" << std::endl; });
		EasyTask task2([]()->void { std::cout << "This is another task" << std::endl; });

		// Sending task to the scheduler works the same for all tasks
		scheduler.Schedule(task1);
		scheduler.Schedule(task2);
    
    		std::cout << "This is parallel with tasks" << std::endl;
    
		task1.Wait();
		task2.Wait();
    
    		std::cout << "All tasks complete" << std::endl;
	}
}
```
