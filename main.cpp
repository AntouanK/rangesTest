#include <time.h> // for clock
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
/***************/
// The partition function
int partition(int* input, int p, int r)
{
    int pivot = input[r];

    while ( p < r )
    {
        while ( input[p] < pivot )
            p++;

        while ( input[r] > pivot )
            r--;

        if ( input[p] == input[r] )
            p++;
        else if ( p < r )
        {
            int tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;
        }
    }

    return r;
}

// The quicksort recursive function
void quicksort(int* input, int p, int r)
{
    if ( p < r )
    {
        int j = partition(input, p, r);        
        quicksort(input, p, j-1);
        quicksort(input, j+1, r);
    }
}
/************************/

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
int markPoints(range r, vector<point> p, int start=0){

    // iterate all the points beginning from start index
    for(int i=start; i < p.size(); i+=1){
        
        //  when we find the first point in the range...
        if(p[i].value == r.start){

            for(int j=i; j < p.size(); j+=1){

                //  mark all the next points until we find the end
                p[j].rangesHits += 1;

                //  when we find the end, return the start found for this range
                if(p[j].value == r.end){
                    return i;
                }
            }
        }

        return i;
    }

    return 0;
};

int main()
{
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
    
       //cout << a << endl;
	   points.push_back(point());
       points[i].value = a;
       points[i].rangesHits = 0;

       i+=1;
    }
    
    infile.close();
    infile.clear();

    i = 0;
    infile.open("extents.txt");
    
    while (getline(infile, line) && i < 100000) {
        
        int a,b;

        istringstream iss(line);
        
        if (!(iss >> a >> b)) {
    		cout<< "ERROR" << endl;
    	} // error
    
        //cout << a << b << endl;
        ranges.push_back(range());
        ranges[i].start = a;
        ranges[i].end = b;
        i+=1;

    }

    infile.close();
    infile.clear();

    cout << "Stored " << i << " ranges" << endl; 

    /** sorting **/
    sort(points.begin(), points.end() );
    sort(ranges.begin(), ranges.end() );

    t1=clock(); // first time capture

    int start = 0;
    for(int i=0; i<ranges.size(); i+=1){

        start = markPoints(ranges[i], points, start);
    }

    t2=clock(); // we get the time now

    float difference= (((float)t2)-((float)t1)); // gives the time elapsed since t1 in milliseconds

    cout << difference/1000 << " seconds" << endl;

    // i = 0;
    // while (i<1000){
    //     cout << points.at(i).value << endl;
    //     i+=1;
    // }
    return 0;
}


