#include <time.h> // for clock
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <vector>
#include <map>

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
int calcRangeHits(point* p, map<unsigned int, int>* weightsMap){

    int counter = 0;

    for (std::map<unsigned int,int>::iterator it=weightsMap->begin(); it!=weightsMap->end(); ++it){

        if(it->first == p->value){
            return counter + it->second;
        } else {
            counter += it->second;
        }
    }
        
    return counter;
}

void mergeRanges(vector<range>* v, map<unsigned int, int>* map){

    for(int i=0; i < v->size(); i+=1){

        int start = (*v)[i].start,
            end = (*v)[i].end;
        std::map<unsigned int, int>::iterator it;
        it = map->find(start);

        if(it == map->end()){
            (*map)[start] = 1;
        } else {
            (*map)[start] = it->second + 1;
        }
        
        it = map->find(end);
        if(it == map->end()){
            (*map)[end+1] = -1;
        } else {
            (*map)[end+1] = it->second - 1;
        }

        //(*map)[((*v)[i].end+1)] = map->find(((*v)[i].end+1)) - 1;
    }

    /*
    for (std::map<unsigned int,int>::iterator it=map->begin(); it!=map->end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    */
}

//  main
int main(int argc, char* const argv[]){

    vector<point> points;
    vector<range> ranges;
    map<unsigned int, int> weightRanges;

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

    t1=clock(); // first time capture

    //  merge ranges into a weighted map
    cout << "merging ranges...  ";
    mergeRanges(&ranges, &weightRanges);
    cout << "done" << endl;

    cout << "calculating hits for " << points.size() << " points ... " << endl;
    for(int k=0; k<points.size(); k+=1){

        points[k].rangesHits = calcRangeHits(&points[k], &weightRanges);

        // if(k%1000==0){
        //     cout << k << " " << points[k].rangesHits << endl;
        // }
        
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
