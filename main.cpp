#include "lock_free_queue.h"

#include <thread>

FXLIB::LockFreeQueue<int> free_lock_queue;
int main()
{
	std::thread t = std::thread([] {
		for (int i = 0;; ++i)
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
			}
		protected:
		private:
		};
		t _t;
		free_lock_queue.Process(_t);
	}
}