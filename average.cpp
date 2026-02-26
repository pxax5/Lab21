#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    double sum = 0.0;
    int count = argc - 1 ;
    double a;
    
    for (int i = 1; i < argc; i++)
    {
        a = atof(argv[i]);
        sum += a;
    }

    double avg = sum / count;
    
    cout << "---------------------------------" << endl ;
    cout << "Average of " << count << " numbers = " << avg << endl;
    cout << "---------------------------------" << endl ;

}