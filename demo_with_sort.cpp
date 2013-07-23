#include <time.h> // for clock
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//  our data structs
struct range {
    unsigned int start;
    unsigned int end;

    bool operator < (const range& str) const
    {
        return (start < str.start);
    }
};

struct point {
    unsigned int value;
    int rangesHits;

    bool operator < (const point& str) const
    {
        return (value < str.value);
    }
};

//  function to check if point is in range
int markPoints(range r, vector<point>* p, int start){

    // iterate all the points beginning from start index
    for(int i=start; i < p->size(); i+=1){

        //cout << i << " value " << (*p)[i].value << " size " << p->size() << endl;
        //cout << r.start << endl;
        //cout << (*p)[i].value << endl;
        
        //  when we find the first point in the range...
        if((*p)[i].value >= r.start){

            for(int j=i; j < p->size(); j+=1){

                //  mark all the next points until we find the end
                (*p)[j].rangesHits += 1;

                //  when we find the end, return the start found for this range
                if((*p)[j].value == r.end){
                    return i;
                }
            }
            return i;
        }
        
    }

    return 0;
};

//  main
int main(int argc, char* const argv[]){

    vector<point> points;
    vector<range> ranges;

    int i=0;
    string line;
    ifstream infile;
    clock_t t1,t2;    
    
    infile.open("numbers.txt");
    //  read points
    while (getline(infile, line) && i < 100000) {
        
       istringstream iss(line);
       int a;
       if (!(iss >> a)) { break; } // error
    
	   points.push_back(point());
       points[i].value = a;
       points[i].rangesHits = 0;

       i+=1;
    }
    
    infile.close();
    infile.clear();

    i=0;
    infile.open("extents.txt");
    
    while (getline(infile, line) && i < 100000) {
        
        int a,b;

        istringstream iss(line);
        
        if (!(iss >> a >> b)) {
    		cout<< "ERROR" << endl;
    	} // error
    
        ranges.push_back(range());
        ranges[i].start = a;
        ranges[i].end = b;
        i+=1;

    }

    infile.close();
    infile.clear();

    cout << "Stored " << i << " ranges" << endl; 

    /** sorting **/
    sort(points.begin(), points.end());
    sort(ranges.begin(), ranges.end());

    t1=clock(); // first time capture

    int start = 0;
    for(int i=0; i<ranges.size(); i+=1){

        start = markPoints(ranges[i], &points, start);
    }

    t2=clock(); // we get the time now

    float difference= (((float)t2)-((float)t1)); // gives the time elapsed since t1 in milliseconds

    cout << difference/1000/1000 << " seconds" << endl;

    //  the result points vector is ready faster, but it's sorted

    return 0;
}


