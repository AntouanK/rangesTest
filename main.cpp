#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    unsigned int points [100000],
        rangeA [100000],
        rangeB [100000],
        i=0;
    string line;
    ifstream infile;
    //ifstream infile2("extents.txt");
    
    infile.open("numbers.txt");
    //  read points
    while (getline(infile, line) && i < 100000) {
        
       istringstream iss(line);
       int a;
       if (!(iss >> a)) { break; } // error
    
       //cout << a << endl;
	   points[i] = a;
       i+=1;
    }
    
    infile.close();
    infile.clear();

    i = 0;
    infile.open("extents.txt");
    
    while (getline(infile, line) && i < 100000) {
        
        istringstream iss(line);
        int a,b;
        if (!(iss >> a >> b)) {
    		cout<< "ERROR" << endl;
    	} // error
    
        //cout << a << b << endl;
        rangeA[i] = a;
        rangeB[i] = b;
        i+=1;

    }

    infile.close();
    infile.clear();

    cout << "Stored " << i << " ranges" << endl; 

    i = 0;
    while (i<10){
        cout << points[i] << endl;
        cout << rangeA[i] << endl;
        cout << rangeB[i] << endl;
        i+=1;
    }
    return 0;
}


