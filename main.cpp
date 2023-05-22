#include "lock_free_queue.h"

#include <thread>
#include <iostream>

FXLIB::LockFreeQueue<int> free_lock_queue;
int main()
{
	std::thread t = std::thread([] {
		auto t1 = std::chrono::system_clock::now();
		for (int i = 0; i < 10000000; ++i)
		{

			class t : public FXLIB::LockFreeQueue<int>::InitNode
			{
			public:
				t(int i)
					: _i(i)
				{
				}
				void operator ()(int& refNode)
				{
					refNode = _i;
				}
			protected:
			private:
				int _i;
			};
			t _t(i);
			free_lock_queue.Push(_t);
		}
		auto t2 = std::chrono::system_clock::now();

		unsigned long long qwt1 = std::chrono::duration_cast<std::chrono::microseconds>(
			(t2-t1)).count();

		std::cout << qwt1 << "\n";
		}
	);

	t.detach();

	for (;;)
	{
		class t : public FXLIB::LockFreeQueue<int>::ProcessNode
		{
		public:
			t()
			{
			}
			void operator ()(int& refNode)
			{
				//std::cout << refNode << "\n";
			}
		protected:
		private:
		};
		t _t;
		free_lock_queue.Process(_t);
	}
}
