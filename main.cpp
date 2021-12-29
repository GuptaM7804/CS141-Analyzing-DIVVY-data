//Author: Manav Gupta
//UIC
//Project 4

#include <iostream>
#include <string>
#include <fstream> 
#include <iomanip>
#include <cmath>
#include <string.h>

using namespace std;

// create structs of Station and Bike, for work efficiency with the input files
struct Station // contains station id, available capacity of bikes in the stations, 
    // latitude and longitude of the station, and the name of the station, as variables in the struct
{
    string StationId;
    int    Capacity;
    double Latitude;
    double Longitude;
    string Name;
};

struct Bike // contains the trip id and bike id of the trip, the station the trip started and ended at, the duration of the trip,
    // and the starting time of the trip, as variables in the struct
{
    string TripId;
    string BikeId;
    string sStationId;
    string eStationId;
    int    Duration;
    string Start;
};


Station* inputStations(string filename, int& NumStations); // inputs data from given file into a dynamically allocated array of struct, returns value of NumStations as well
Bike* inputBikes(string filename, int& NumBikes); // inputs data from given file into a dynamically allocated array of struct, returns value of NumBikes as well
void eraser(int NumStations, Station stations[]); // removes space before the name variable in array of struct stations
void outputStats(int NumStations, Station stations[], int NumBikes); // outputs the stat function
int durations(int NumBikes, Bike bikes[], int duration); // returns the number of trips that occured in preset time periods
void outputDurations(int NumBikes, Bike bikes[]); // outputs the durations function
int starting(int NumBikes, Bike bikes[]); // checks if how many trips have occured by the hour
void outputStarting(int NumBikes, Bike bikes[]); // outputs the startint function
double distBetween2Points(double lat1, double long1, double lat2, double long2); // calculates the distance-given by instructor
string* NearMeNames(Station stations[], int NumStations, double lat, double lon, double dist); // returns an array of string of names of station that are in a given distance
string* NearMeId(Station stations[], int NumStations, double lat, double lon, double dist); // returns an array of string of IDs of stations that are in a given distance
double* NearMeDist(Station stations[], int NumStations, double lat, double lon, double dist); // returns an array of numbers of distances of stations from user input location
void sortByDist(int NumStations, Station stations[], int count, double distArr[], string arr[], string idArr[]); // sorts all above arrays in ascending order of distance
void outputNearme(int NumStations, Station stations[], int lat, int lon, int dist); // outputs the nearme function
void sortByName(Station stations[], int NumStations); // sorts array of station struct by name
int tripsPerStation(int NumStations, Station stations[], Bike bikes[], int NumBikes); // returns the number of trips at a station
void outputStations(int NumStations, Station stations[], Bike bikes[], int NumBikes); // outputs the stations function
void outputFind(int NumStations, Station stations[], Bike bikes[], int NumBikes, string input); // outputs the find function
int stringToInt(string time); // returns any time in (hh:mm) format as an integer (hhmm)
int search(int NumBikes, Bike bikes[], string first, string last); // returns the number of trips that occured in a given time period
int durationsTrips(int NumBikes, Bike bikes[], string first, string last); // returns the average duration of all trips that occured in a given time period
string function(int NumBikes, Bike bikes[], Station stations[], int NumStations, string first, string last, int i); // returns name of the station that the bike started trips at
string* names(int NumBikes, Bike bikes[], Station stations[], int NumStations, string first, string last); // returns an array of string of names of stations that trips occured 
// at in a given period of time
void outputTrips(int NumBikes, Bike bikes[], Station stations[], int NumStations, string first, string last); // outputs the trips function


Station* inputStations(string filename, int& NumStations)
{
    ifstream infile;
    
    infile.open(filename); // open the file
    
    if (!infile.good())
        return nullptr; // returns nullptr if file is unable to open
    
    infile >> NumStations; // first word in file is integer of the number of lines in the file
    
    Station* stations; // create dynamic array of struct
    stations = new Station[NumStations];
    
    for (int i = 0; i < NumStations; i++)
    {
        infile >> stations[i].StationId; // input each struct variable from file into dynamic array of struct
        infile >> stations[i].Capacity;
        infile >> stations[i].Latitude;
        infile >> stations[i].Longitude;
        getline(infile, stations[i].Name);
    }
    return stations; // returns the array
}

Bike* inputBikes(string filename2, int& NumBikes) // same as above
{
    ifstream infile;
    
    infile.open(filename2);
    
    if (!infile.good())
        return nullptr;
    
    infile >> NumBikes;
    
    Bike* bikes;
    bikes = new Bike[NumBikes];
    
    for (int i = 0; i < NumBikes; i++)
    {
        infile >> bikes[i].TripId;
        infile >> bikes[i].BikeId;
        infile >> bikes[i].sStationId;
        infile >> bikes[i].eStationId;
        infile >> bikes[i].Duration;
        infile >> bikes[i].Start;
    }
    return bikes;
}

void eraser(int NumStations, Station stations[])
{
    for (int i = 0; i < NumStations; i++)
    {
        stations[i].Name.erase(0,1); // erases the indent/space before the name variable in the dynamic struct of station (due to the getline function used for name)
    }
}

void outputStats(int NumStations, Station stations[], int NumBikes)
{
    cout << "  stations: " << NumStations << endl; 
    cout << "  trips: " << NumBikes << endl;
    int count = 0;
    for (int i = 0; i < NumStations; i++)
    {
        count += stations[i].Capacity; // calculates total capacity accross all stations
    }
    cout << "  total bike capacity: " << count << endl;
}

int durations(int NumBikes, Bike bikes[], int after, int before)
{
    int count = 0;
    for (int i = 0; i < NumBikes; i++)
    {
        if (bikes[i].Duration > after && bikes[i].Duration <= before) // if duration is greater than the 'after' value, and if it is less than or equal to the 'before' value
        {
            count++; // count = count + 1
        }
    }
    return count;
}

void outputDurations(int NumBikes, Bike bikes[])
{
    int after = 0;
    int before = 30*60;
    int count = durations(NumBikes, bikes, after, before); // runs the function to see how many bikes travelled between this time
    cout << "  trips <= 30 mins: " << count << endl;
    after = 30*60;
    before = 60*60;
    count = durations(NumBikes, bikes, after, before);
    cout << "  trips 30..60 mins: " << count << endl;
    after = 60*60;
    before = 120*60;
    count = durations(NumBikes, bikes, after, before);
    cout << "  trips 1-2 hours: " << count << endl;
    after = 120*60;
    before = 300*60;
    count = durations(NumBikes, bikes, after, before);
    cout << "  trips 2-5 hours: " << count << endl;
    after = 300*60;
    before = 1440*60;
    count = durations(NumBikes, bikes, after, before);
    cout << "  trips > 5 hours: " << count << endl;
}

int starting(int NumBikes, Bike bikes[], string gg)
{
    int count = 0;
    for (int i = 0; i < NumBikes; i++)
    {
        int pos = bikes[i].Start.find(":"); // assigns pos with position of ":" in a string
        if (bikes[i].Start.substr(0, pos) == gg) // gets substring from 0 to pos (characters before :) and checks if it is equal to variable gg
        {
            count++; // if yes, then count = count + 1
        }
    }
    return count;
}

void outputStarting(int NumBikes, Bike bikes[])
{
    for (int i = 0; i < 24; i++)
    {
        int count = starting(NumBikes, bikes, to_string(i)); // assigns count to function value
        cout << "  " << i << ": " << count << endl;
    }
}

//
// distBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2).  Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west.  Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
// Originally written by: Prof. Hummel, U. of Illinois, Chicago, Spring 2021
// Reference: http://www8.nau.edu/cvm/latlon_formula.html
//
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}

int counter(int NumStations, Station stations[], double lat, double lon, double dist)
{
    int count = 0;
    
    for (int i = 0; i < NumStations; i++)
    {
        double distance = distBetween2Points(lat, lon, stations[i].Latitude, stations[i].Longitude); // assigns distance from user input position of stations to distance
        if (dist >= distance)
        {
            count ++; // increase count by 1 if user input distance is greater than or equal to stations distance
        }
    }
    return count;
}

string* NearMeNames(Station stations[], int NumStations, double lat, double lon, double dist)
{
    int count = counter(NumStations, stations, lat, lon, dist);
    
    string* arr; // create dynamically allocated array of string
    arr = new string[count];
    int x = 0;
    for (int i = 0; i < NumStations; i++)
    {
        double distance = distBetween2Points(lat, lon, stations[i].Latitude, stations[i].Longitude); // same as above
        if (dist >= distance)
        {
            arr[x] = stations[i].Name; // assigns station name in condition to an element in the array
            x++;
        }
    }
    return arr;
}

string* NearMeId(Station stations[], int NumStations, double lat, double lon, double dist)
{
    int count = counter(NumStations, stations, lat, lon, dist);
    
    string* arr;
    arr = NearMeNames(stations, NumStations, lat, lon, dist); // create string, assign it to dynamic array from function above
    string* idArr; // create string array of id
    idArr = new string[count];
    int x = 0;
    for (int i = 0; i < NumStations; i++)
    {
        if (arr[x] == stations[i].Name)
        {
            idArr[x] = stations[i].StationId; // if name in array of names is equal to name in struct array of station, assign id of the element to element in id array
            x++;
        }
    }
    return idArr;
}

double* NearMeDist(Station stations[], int NumStations, double lat, double lon, double dist)
{
    int count = counter(NumStations, stations, lat, lon, dist); // same as above but for distance rather than names
    
    int x = 0;
    
    double* distArr;
    distArr = new double[count];
    for (int i = 0; i < NumStations; i++)
    {
        double distance = distBetween2Points(lat, lon, stations[i].Latitude, stations[i].Longitude);
        if (dist >= distance)
        {
            distArr[x] = distance;
            x++;
        }
    }
    return distArr;
}

void sortByDist(int NumStations, Station stations[], int count, double distArr[], string arr[], string idArr[])
{
    for (int i = 0; i < count-1; i++)
    {
        int minIndex = i;
        
        for (int j = i+1; j < count; j++)
        {
            if (fabs(distArr[j]) < fabs(distArr[minIndex])) // if distance on element j is less than distance on element minIndex
            {
                minIndex = j; 
            }
        }
        // sort all these arrays in ascending order
        double distTemp = distArr[i];
        distArr[i] = distArr[minIndex];
        distArr[minIndex] = distTemp;
        
        string temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        
        string idTemp = idArr[i];
        idArr[i] = idArr[minIndex];
        idArr[minIndex] = idTemp;
    }
}

void outputNearme(int NumStations, Station stations[], double lat, double lon, double dist)
{
    int count = counter(NumStations, stations, lat, lon, dist);
    if (count == 0) // if no station in user inputted location, not found is outputted
    {
        cout << "  none found" << endl;
    }
    
    else
    {
        double* distArr;
        distArr = NearMeDist(stations, NumStations, lat, lon, dist);
        string* arr;
        arr = NearMeNames(stations, NumStations, lat, lon, dist);
        string* idArr;
        idArr = NearMeId(stations, NumStations, lat, lon, dist);

        sortByDist(NumStations, stations, count, distArr, arr, idArr);

        cout << "  The following stations are within " << dist << " miles of (" << lat << ", " << lon << "):" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "  station " << idArr[i] << " (" << arr[i] << "): " << std::setprecision(7) << distArr[i] << " miles" << endl;
        }
        // delete all dynamic arrays
        delete []arr;
        delete []distArr;
        delete []idArr;
    }
    
}

void sortByName(Station stations[], int NumStations) // same as sorting function above but for names
{
    for (int i = 0; i < NumStations-1; i++)
    {
        int minIndex = i;

        for (int j = i+1; j < NumStations; j++)
        {
            if (stations[j].Name < stations[minIndex].Name)
            {
                minIndex = j;
            }
        }

        Station temp = stations[i];
        stations[i] = stations[minIndex];
        stations[minIndex] = temp;
    }
}

int tripsPerStation(int NumStations, Station stations[], Bike bikes[], int NumBikes, int i)
{
    int count = 0;
    for (int j = 0; j < NumBikes; j++)
    {
        if (stations[i].StationId == bikes[j].sStationId || stations[i].StationId == bikes[j].eStationId) // if a bike trips starting or ending id of station are equal to
            // a given station id...
        {
            if (bikes[j].sStationId != bikes[j].eStationId) // if the same bike trip doesn't start and stop at the same station...
            {
                count++; // count = coutn + 1
            }
        }
    }
    return count;
}

void outputStations(int NumStations, Station stations[], Bike bikes[], int NumBikes)
{
    for (int i = 0; i < NumStations; i++)
    {
        // couts all values required by function
        int count = tripsPerStation(NumStations, stations, bikes, NumBikes, i);
        cout << "  " << stations[i].Name << " (" 
            << stations[i].StationId << ") @ (" 
            << stations[i].Latitude << ", " 
            << stations[i].Longitude << "), " 
            << stations[i].Capacity << " capacity," 
            << count << " trips" << endl;
    }
}

int search2(int NumStations, Station stations[], Bike bikes[], int NumBikes, string input)
{
    for (int i = 0; i < NumStations; i++)
    {
        if (stations[i].Name.find(input) != string::npos)
        {
            return 2;
        }
    }
    return -1;
}

void outputFind(int NumStations, Station stations[], Bike bikes[], int NumBikes, string input)
{
    if (search2(NumStations, stations, bikes, NumBikes, input) == -1)
    { 
        cout << "  none found" << endl;
    }
    else 
    {
        for (int i = 0; i < NumStations; i++)
        {
            if (stations[i].Name.find(input) != string::npos) // if user input is not equal to not found (ie: if it is found)
            {
                // cout all statements required by function
                int count = tripsPerStation(NumStations, stations, bikes, NumBikes, i);
                cout << "  " << stations[i].Name << " (" 
                    << stations[i].StationId << ") @ (" 
                    << stations[i].Latitude << ", " 
                    << stations[i].Longitude << "), " 
                    << stations[i].Capacity << " capacity," 
                    << count << " trips" << endl;
            }
        }
    }
}

int stringToInt(string time)
{
    int last = time.length(); // assign last to the last index of string
    int pos = time.find(":"); // assign pos to index of ":"
    string hour = time.substr(0, pos); // assign hour to the characters between 0 and pos (characters before ":")
    string minute = time.substr(pos+1, last); // assign minute to characters after ":" and before last index of string (after ":")
    string timex = hour + minute; // assign timex with hour + minute (format :: hhmm)
        
    return stoi(timex); // return int value of the string ("hhmm" to hhmm)
}

int search(int NumBikes, Bike bikes[], string first, string last)
{
    int count = 0;
    if (stringToInt(first) < stringToInt(last))
    {
        for (int i = 0; i < NumBikes; i++)
        {
            if (stringToInt(bikes[i].Start) >= stringToInt(first) && stringToInt(bikes[i].Start) <= stringToInt(last)) // if bike duration is between the user inputted values
            {
                count ++; // cout = cout + 1
            }
        }
    }
    else if (stringToInt(first) > stringToInt(last))
    {
        for (int i = 0; i < NumBikes; i++)
        {
            if ((stringToInt(bikes[i].Start) >= stringToInt(first) && stringToInt(bikes[i].Start) <= 2359)
                || (stringToInt(bikes[i].Start) >= 0 && stringToInt(bikes[i].Start) <= stringToInt(last))) // if bike duration is between the user inputted values
            {
                count ++; // cout = cout + 1
            }
        }
    }
    return count;
}

int durationsTrips(int NumBikes, Bike bikes[], string first, string last)
{
    int count = search(NumBikes, bikes, first, last);
    int duration = 0;
    
    if (stringToInt(first) < stringToInt(last))
    {
        for (int i = 0; i < NumBikes; i++)
        {
            if (stringToInt(bikes[i].Start) >= stringToInt(first) && stringToInt(bikes[i].Start) <= stringToInt(last)) // same as above
            {
                duration += bikes[i].Duration; // add durations of the bike trips in the given time
            }
        }
    }
    else if (stringToInt(first) > stringToInt(last))
    {
        for (int i = 0; i < NumBikes; i++)
        {
            if ((stringToInt(bikes[i].Start) >= stringToInt(first) && stringToInt(bikes[i].Start) <= 2359)
                || (stringToInt(bikes[i].Start) >= 0 && stringToInt(bikes[i].Start) <= stringToInt(last))) // same as above
            {
                duration += bikes[i].Duration; // add durations of the bike trips in the given time
            }
        }
    }
    
    
    duration = duration / count; // divide duration by number of durations to get avg
    duration = duration / 60; // divide by 60 to get value in minutes from seconds
    return duration;
}

string function(Bike bikes[], Station stations[], int NumStations, int i)
{
    for (int j = 0; j < NumStations; j++)
    {
        if (bikes[i].sStationId == stations[j].StationId) // if bike starting station id is equal to a station id...
        {
            return stations[j].Name; // return the name of that station
        }
    }
    return "error"; // else there is an error in code
}

string* names(int NumBikes, Bike bikes[], Station stations[], int NumStations, string first, string last)
{
    int count = search(NumBikes, bikes, first, last);
    
    string* arr; // create dynamically allocated array of string
    arr = new string[count];
    int x = 0;
    if (stringToInt(first) < stringToInt(last))
    {
        for (int i = 0; i < NumBikes; i++)
        {
            if (stringToInt(bikes[i].Start) >= stringToInt(first) && stringToInt(bikes[i].Start) <= stringToInt(last))
            {
                arr[x] = function(bikes, stations, NumStations, i); // if bikes start time is in the user given time period, assign name of the station the bike was at to
                // element in string array
                x++;
            }
        }
    }
    else if (stringToInt(first) > stringToInt(last))
    {
        for (int i = 0; i < NumBikes; i++)
        {
            if ((stringToInt(bikes[i].Start) >= stringToInt(first) && stringToInt(bikes[i].Start) <= 2359)
                || (stringToInt(bikes[i].Start) >= 0 && stringToInt(bikes[i].Start) <= stringToInt(last)))
            {
                arr[x] = function(bikes, stations, NumStations, i); // if bikes start time is in the user given time period, assign name of the station the bike was at to
                // element in string array
                x++;
            }
        }
    }
    return arr;
}

void sortNameArr(string arr[], int count) // same as sortByName but for dynamic string array
{
    for (int i = 0; i < count-1; i++)
    {
        int minIndex = i;

        for (int j = i+1; j < count; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        string temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void outputTrips(int NumBikes, Bike bikes[], Station stations[], int NumStations, string first, string last)
{
    int count = search(NumBikes, bikes, first, last);
    
    if (count != 0)
    {
        string* arr; // create dynamic array of string
        arr = names(NumBikes, bikes, stations, NumStations, first, last); // assign array to dynamic array in names
        sortNameArr(arr, count); // use sort function to sort the array
        int duration = durationsTrips(NumBikes, bikes, first, last); // assign duration to avg duration function
        // cout all function required statements
        cout << "  " << count << " trips found" << endl;
        cout << "  avg duration: " << duration << " minutes" << endl;
        cout << "  stations where trip started: ";
        cout << arr[0];
        if (count > 2 && arr[0] != arr[1] && arr[0] != arr[count-1]) // checking the size of count and how to proceed depending on the size of count
        {
            for (int i = 1; i < count - 1; i++) // keep printing until second last if count is greater than 2 and or arr[1] and arr[count-1] is not equal to arr[0]
            {
                if(arr[i] != arr[i+1]) // check if two arrays are not the same
                {
                    cout << ", " << arr[i];
                }  
            }
            cout << ", " << arr[count-1] << endl ; // then print last element in array+
        }
        else if (count == 2)
        {
            cout << ", " << arr[count-1] << endl ;
        }
        else
        {
            cout << endl;
        }
        delete []arr;
    }
    
    else
    {
        cout << "  none found" << endl; // if count = 0, output none found
    }
}



int main()
{
    string filename; // assign two string variables
    string filename2;
    
    cout << "Kindly input your chosen filename for the station file: " << endl;
    cout << "Also, very kindly input your chosen filename for the trips file as well: " << endl;
    
    cin >> filename; // get filenames from user
    cin >> filename2;
    
    int NumStations; // assign int variables for size of arrays
    int NumBikes;
    Station* stations; // creat a station and bike dynamic array of struct
    Bike* bikes;
    if (inputStations(filename, NumStations) == nullptr) // if files do not open, return 0
    {
        cout << "  Invalid filename: " << filename << endl;
        return 0;
    }
    
    stations = inputStations(filename, NumStations); // assign both arrays of struct to a function that returns a dynamic array of struct
    
    if (inputBikes(filename2, NumBikes) == nullptr)
    {
        cout << "  Invalid filename: " << filename2 << endl;
        return 0;
    }
    
    bikes = inputBikes(filename2, NumBikes);
    
    eraser(NumStations, stations); // erase the space before the name variable
    
    cout << "Enter command (# to stop)> ";
    string cmd; // assign a string variable
    cin >> cmd; // assign user input to string variable

    // start while loop, end if "#" is entered by user
    while (cmd != "#")
    {
        // cmd == "abc" do cbd...
        if (cmd == "stats")
        {
            outputStats(NumStations, stations, NumBikes);
        }
        else if (cmd == "durations")
        {
            outputDurations(NumBikes, bikes);
        }
        else if (cmd == "starting")
        {
            outputStarting(NumBikes, bikes);
        }
        else if (cmd == "nearme")
        {
            double lat, lon, dist;
            
            cin >> lat >> lon >> dist;
            
            outputNearme(NumStations, stations, lat, lon, dist);
        }
        else if (cmd == "stations")
        {
            sortByName(stations, NumStations);
            outputStations(NumStations, stations, bikes, NumBikes);
        }
        else if (cmd == "find")
        {
            string input;
            
            cin >> input;
            
            sortByName(stations, NumStations);
            outputFind(NumStations, stations, bikes, NumBikes, input);
        }
        else if (cmd == "trips")
        {
            string first, last;

            cin >> first >> last;
            
            outputTrips(NumBikes, bikes, stations, NumStations, first, last);
        }
        else // else output invalid entry
        {
            cout << "** Invalid command, try again" << endl;
        }

        cout << "Enter a command (names, ratings, years, range, # to exit)> ";
        cin >> cmd; // get input from user to keep while loop going
    }
    
    // delete dynamically allocated arrays to free space
    delete []stations;
    delete []bikes;
    return 0;
}
