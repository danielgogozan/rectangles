#include <iostream> 
#include <string> 
#include <algorithm>  
#include <map>
#include <fstream>
#include <unordered_set>

using std::map;
using std::ifstream;
using std::string;
using std::unordered_set;

/*
we use a map in which an X axis coordinate is the key having an unordered set containing the associated Y axis coordinates
*/
map<int, unordered_set<int>> coordinates;


//we read from the file according to the specified format "(x1,y1), (x2,y2)" and so on
void readFromFile(string fileName) {
    ifstream f(fileName);
    string line = "";
    if (f.is_open())
    {
        getline(f, line);
        std::size_t bracket, numberFirstPos = 1;
        string c1 = ")";
        bracket = line.find(c1);

        while (bracket != std::string::npos) {
            string c2 = ",";
            std::size_t comma = line.find(c2,numberFirstPos);

            int x = stoi(line.substr(numberFirstPos, comma - numberFirstPos));
            int y = stoi(line.substr(comma + 1, bracket));

            coordinates[x].insert(y);
           
            numberFirstPos = bracket + 4;
            bracket = line.find(c1, numberFirstPos);
        }
        f.close();
    }
}


/*
we iterate the shortest set and count any point from it that is also in the other set
we calculate actually the lenght of the intersection set
*/
int intersection(unordered_set<int> set1, unordered_set<int> set2) {
    if(set1.size() > set2.size())
        return count_if(set2.begin(), set2.end(), [&](int x) {return set1.find(x) != set1.end();});
    else
        return count_if(set1.begin(), set1.end(), [&](int x) {return set2.find(x) != set2.end();});
}


/*
we iterate the dictionary and use a mathematical generalization which determines, 
based on the length of the intersection set, how many rectangles (that are parallel with the X, Y axes)
we can obtain with two coordinates (two keys in the dictionary) on the abscissa.

note: the reason it works is described in readme.docx file.
*/
int solve() {
    int totalRectangles = 0;

    map<int, unordered_set<int>>::iterator it1 = coordinates.begin();
    while( it1 != --coordinates.end() ) {
        map<int, unordered_set<int>>::iterator it2 = it1;

        for (it2 = ++it2; it2 != coordinates.end(); it2++) {
            int n = intersection(it1->second, it2->second);
            totalRectangles += n * (n - 1) / 2;
        }
        
        ++it1;
    }
    return totalRectangles;
}



int main()
{
    readFromFile("data.txt");
    std::cout << solve();


    return 0;
}
