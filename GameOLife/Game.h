#pragma once
#include <vector>

namespace Biendeo {
	class Game {
		public:
		Game(int width, int height);
		~Game();

		private:
		int height;
		int width;
		std::vector<std::vector<bool>> grid;

		public:
		int GetWidth();
		int GetHeight();
		bool GetSpace(int x, int y);
		bool IsOutOfBound(int x, int y);
		void NextGeneration();
		void Randomise();
		bool Toggle(int x, int y);
		void Draw();
	};
}