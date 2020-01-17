
// mazeGenerator Header
using namespace std;

class mazeGenerator
{
	public: 	
		mazeGenerator();
		~mazeGenerator();

		bool setSize(int, int);
		bool printMazeData(const string) const;
		bool getArguments(int, char *[], int&, int&, string&, bool&);

		void getSize(int&, int&) const;
		void generate();
		void printMazeText() const;

	private: 
		int rows;
		int cols;
		int **walls;

		static constexpr int MIN_ROWS = 5;
		static constexpr int MIN_COLS = 5;
		static constexpr int MAX_ROWS = 100000;
		static constexpr int MAX_COLS = 100000;

		void randomize(); 
};	