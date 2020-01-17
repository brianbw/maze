
// disjointSets Header
using namespace std;

class disjointSets
{
	public: 	
		disjointSets(int = 10);
		~disjointSets();

		void printSets() const;
		
		int entries() const;
		int setUnion(int, int);
		int setFind(int);

	private: 
		int setSize;
		int currSet;
		int *links;
		int *ranks;

		static constexpr int MIN_SIZE = 10;
};	