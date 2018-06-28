#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// output struct
typedef struct
{
    int N_city;
    int Start_city;
    vector< vector<int> > all_city;
}Citys;

class DataProcess
{
private:
    int n_city;
    vector< vector<int> > city_infor;
    int start_city_number;
public:
    // class constructor
    DataProcess();
    ~DataProcess(){};
    
    // individual function
    Citys Data_Loading_Parsing(char* file_name);
    void Data_Visualization(Citys inputs);
};

// Constructor
DataProcess::DataProcess()
{
    // initialize private parameters
    n_city = 0;
    start_city_number = 0;
}

// Data Loading and Parsing
Citys DataProcess::Data_Loading_Parsing(char* file_name)
{
    // declare local variables
    int counts = 0;
    int counts_2 = 0;
    string line_1;
    string line_2;
    
    // read file given file name, and count the number of lines
    ifstream inputfile(file_name, ios::in); // open the file
    while(getline(inputfile, line_1))
    {
        counts++;
    }
    inputfile.close();
    
    // Error Checking
    if (counts == 0)
    {
        cout << "Error!! Empty File." << endl;
        exit(0);
    }
    else if (counts == 1 || counts == 2)
    {
        cout << "Error!! Imcomplete File." << endl;
        exit(0);
    }
    
    // parsing input file
    ifstream inputfile_2(file_name, ios::in); // open the file
    while(getline(inputfile_2, line_2))
    {
        counts_2++;
        if (counts_2 == 1)
        {
            n_city = stoi(line_2);
        }
        if (counts_2 != 1 && counts_2 != counts)// load all of cities
        {
            istringstream temp_string(line_2);
            vector <int> col_vector;
            string col_element;
            
            // read every column from the line that is seperated by commas
            while(getline(temp_string, col_element, ' '))
            {
                int temp_value = atoi( col_element.c_str() );
                col_vector.push_back(temp_value);
            }
            city_infor.push_back(col_vector);
            
        }
        if (counts_2 == counts)
        {
            start_city_number = stoi(line_2);
        }
        
    }
    inputfile_2.close();
    
    // output weights and biases
    Citys output_city;
    output_city.N_city = n_city;
    output_city.Start_city = start_city_number;
    output_city.all_city = city_infor;
    
    return output_city;
}

// Data Visualization
void DataProcess::Data_Visualization(Citys inputs)
{
    // declare 200 by 200 grid
    int grids_array[200][200] = {0};
    
    // assign a city to the corresponding coordinates
    for (int i = 0 ; i < inputs.all_city.size() ; ++i)
    {
        grids_array[inputs.all_city[i][2] - 1][inputs.all_city[i][1] - 1] = inputs.all_city[i][0];
    }
    
    // visuallization
    for (int i = 0 ; i < 200 ; ++i)
    {
        for (int j = 0 ; j < 200 ; ++j)
        {
            cout << grids_array[i][j] << " ";
        }
        cout << endl;
    }
}