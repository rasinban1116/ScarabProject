#pragma once
#include "stdafx.h"

namespace basecross {
	class GameManager {
		static GameManager* GM;

		int m_getunkonum;

		GameManager() {
		}
		~GameManager();
	public:
		static GameManager* GetInstance();
		void UnkoNumUp() {
			m_getunkonum++;
		}
		int GetUnkoNum() {
			return m_getunkonum;
		}
		void UnkoNumReSet() {
			m_getunkonum = 0;
		}
	};
}
