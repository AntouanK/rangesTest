#include <time.h> // for clock
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

//  our data structs
struct range {
    unsigned int start;
    unsigned int end;
};

struct point {
    unsigned int value;
    int rangesHits;
};


//  function to check if point is in range
bool isInRange(point p, range r){	//	TODO, pass by reference or pointers maybe?

    return (p.value >= r.start && p.value <= r.end);
}

//  main
int main(int argc, char* const argv[]){

    vector<point> points;
    vector<range> ranges;

    int i=0;
    string line;
    ifstream infile;
    clock_t t1,t2;    

    //  open numbers file    
    infile.open("numbers.txt");
    //  read points
    while (getline(infile, line) && i < 100000) {
        
        istringstream iss(line);
        int a;
        if (!(iss >> a)) {
            cout << "ERROR" << endl;
        } // error
        
	    points.push_back(point());
        points[i].value = a;
        points[i].rangesHits = 0;

        i+=1;
    }
    
    infile.close();
    infile.clear();

    //  open extents file
    i=0;
    infile.open("extents.txt");
    //  read ranges
    while (getline(infile, line) && i < 100000) {

        int a,b;

        istringstream iss(line);

        if (!(iss >> a >> b)) {
        	cout << "ERROR" << endl;
        } // error

        ranges.push_back(range());
        ranges[i].start = a;
        ranges[i].end = b;
        i+=1;
    }

    infile.close();
    infile.clear();

    cout << "calculating range hits for each point..." << endl;

    t1=clock(); // first time capture

    for(int i=0; i<points.size(); i+=1){

        for(int j=0; j<ranges.size(); j+=1){
            
            if(isInRange(points[i], ranges[j])){
                points[i].rangesHits += 1;
            }
        }
    }

    t2=clock(); // we get the time now

    float difference= (((float)t2)-((float)t1)); // gives the time elapsed since t1 in milliseconds

    cout << "hits found in " << difference/1000/1000 << " seconds" << endl;
    
    if( argc > 2 && strcmp(argv[1], "-o")==0){
        fstream outputFile;

        cout << "writing results to " << argv[2] << endl;
        outputFile.open(argv[2]);

        if(!outputFile.is_open()){
            outputFile.open(argv[2], ios_base::in | ios_base::out | ios_base::trunc);
        }
        for(int i=0; i<points.size(); i+=1){
            outputFile << points[i].rangesHits << endl;
        }
        outputFile.close();

    }
    //  the result points vector is ready faster, but it's sorted

    return 0;
}
