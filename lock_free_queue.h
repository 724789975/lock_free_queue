#ifndef __LOCK_FREE_QUEUE_H__
#define __LOCK_FREE_QUEUE_H__

namespace FXLIB
{
	template<typename Node>
	class LockFreeQueue
	{
	public:
		class InitNode
		{
		public:
			virtual ~InitNode() {}
			virtual void operator ()(Node& refNode)
			{
			}
		};

		class ProcessNode
		{
		public:
			virtual ~ProcessNode() {}
			virtual void operator ()(Node& refNode)
			{
			}
		};

		LockFreeQueue()
		{
			m_pHead = m_pTail = new LockFreeNode();
			m_pTail->m_bProcessed = true;
			m_pTail->m_pNext = 0;
		}

		void Push(InitNode& funInit)
		{
			LockFreeNode* pNode = new LockFreeNode();
			pNode->m_bProcessed = false;
			pNode->m_pNext = 0;
			funInit(pNode->m_oNode);

			LockFreeNode* pTail = m_pTail;
			m_pTail = pNode;
			pTail->m_pNext = pNode;
		}

		void Process(ProcessNode& funProcess)
		{
			while (LockFreeNode* pNode = m_pHead->m_pNext)
			{
				pNode->m_bProcessed = true;
				delete m_pHead;
				m_pHead = pNode;

				funProcess(pNode->m_oNode);
			}
		}
	private:
		class LockFreeNode
		{
			friend class LockFreeQueue;
			LockFreeNode* m_pNext;
			Node m_oNode;
			bool m_bProcessed;
		};

		long m_qwPrd1[7];
		LockFreeNode* m_pHead;
		long m_qwPrd2[7];
		LockFreeNode* m_pTail;
		long m_qwPrd3[7];
	};
};


#endif	//__LOCK_FREE_QUEUE_H__

