/*
 < Li-Yun > < Wang >
 < 10-10 2016 >
 CS 541
 Lab 2
*/
#include <iostream>
#include <vector>
#include "DataProcess.h"
#include "GA.h"

using namespace std;

// display all individuals in the population
void display_population(vector< pair< vector<int>, float> > initials)
{
    cout << "Population Pool: " << endl;
    for (int i = 0 ; i < initials.size() ; ++i)
    {
        pair< vector<int>, float> aa = initials[i];
        vector<int> indivi = aa.first;
        
        for (int j = 0 ; j < indivi.size() ; ++j)
        {
            cout << indivi[j] << " ";
        }
        cout << aa.second << endl;
    }
    cout << "===================" << endl;
}

// searching minimum value
pair<vector<int>, float> searching_minimum(vector< pair< vector<int>, float> > inputs)
{
    // declare variables
    pair<vector<int>, float> output_pair;
    output_pair.first = inputs[0].first;
    output_pair.second = inputs[0].second;
    
    // loop through all pair sets to find minimum value
    for (int i = 1 ; i < inputs.size() ; ++i)
    {
        if (inputs[i].second < output_pair.second)
        {
            output_pair.second = inputs[i].second;
            output_pair.first = inputs[i].first;
        }
    }
    
    return output_pair;
}

int main(int argc, char** argv)
{
    // setting the seed for randomization
    srand((unsigned)time(NULL));
    
    // declare variables
    int visualization_flag = 0;
    int population_flag = 0;
    int generation_number = 0;
    int population_size = 0;
    int selection_size = 0;
    float mutation_rate = 0.0;
    
    //parsing arguments from command line
    if( argc < 2 )
    {
        cout << "Error!! Please Type File Name." << endl;
        return -1;
    }
    if ( argc == 2 )
    {
        visualization_flag = 0;
        population_flag = 0;
        generation_number = 100;
        population_size = 20;
        selection_size = 10;
        mutation_rate = 0.015;
    }
    else if ( argc == 3 )
    {
        visualization_flag = stoi(argv[2]);
        population_flag = 0;
        generation_number = 100;
        population_size = 20;
        selection_size = 10;
        mutation_rate = 0.015;
    }
    else if ( argc == 4 )
    {
        visualization_flag = stoi(argv[2]);
        population_flag = stoi(argv[3]);
        generation_number = 100;
        population_size = 20;
        selection_size = 10;
        mutation_rate = 0.015;
    }
    else if ( argc == 5 )
    {
        visualization_flag = stoi(argv[2]);
        population_flag = stoi(argv[3]);
        generation_number = stoi(argv[4]);
        population_size = 20;
        selection_size = 10;
        mutation_rate = 0.015;
    }
    else if ( argc == 6 )
    {
        visualization_flag = stoi(argv[2]);
        population_flag = stoi(argv[3]);
        generation_number = stoi(argv[4]);
        population_size = stoi(argv[5]);
        selection_size = 10;
        mutation_rate = 0.015;
    }
    else if ( argc == 7 )
    {
        visualization_flag = stoi(argv[2]);
        population_flag = stoi(argv[3]);
        generation_number = stoi(argv[4]);
        population_size = stoi(argv[5]);
        selection_size = stoi(argv[6]);
        mutation_rate = 0.015;
    }
    else if ( argc == 8 )
    {
        visualization_flag = stoi(argv[2]);
        population_flag = stoi(argv[3]);
        generation_number = stoi(argv[4]);
        population_size = stoi(argv[5]);
        selection_size = stoi(argv[6]);
        mutation_rate = stof(argv[7]);
    }
    else
    {
        cout << "Error !!" << endl;
    }
    
    
    // data initialization
    DataProcess * process = new DataProcess();
    Citys outputs = process -> Data_Loading_Parsing(argv[1]);
    
    
    // dispaly information
    cout << "# of Cities: " << outputs.N_city << endl;
    cout << "City Information: " << endl;
    for (int i = 0 ; i < outputs.all_city.size() ; ++i)
    {
        for (int j = 0 ; j < outputs.all_city[0].size() ; ++j)
        {
            cout << outputs.all_city[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Start City: " << outputs.Start_city << endl;
    
    
    if (visualization_flag)
    {
        // visulalization cities.
        process -> Data_Visualization(outputs);
    }
    
    
    // initialize a population pool
    GA *genetic_algorithm = new GA(mutation_rate, selection_size);
    vector< pair< vector<int>, float> > initials = genetic_algorithm -> initial_population(outputs.all_city, outputs.Start_city, population_size);
    
    if(population_flag)
    {
        cout << "Initial population: " << endl;
        display_population(initials);
    }
    
    // find the shorest path and city's order from initial population
    pair<vector<int>, float> best_solution = searching_minimum(initials);
    cout << "The order of the shorest distance: " << endl;
    for (int i = 0 ; i < best_solution.first.size() ; ++i)
    {
        cout << best_solution.first.at(i) << " ";
    }
    cout << endl;
    cout << "The shorest path of visiting all of the cities once is: " << best_solution.second << endl;
    cout << "========================================================" << endl;
    
    // Genetic Algorithm
    for (int i = 0 ; i < generation_number ; ++i)
    {
        initials = genetic_algorithm -> evolvePopulation(initials, outputs.all_city, outputs.Start_city, population_size);
    }
    
    cout << "The Result After " << generation_number << " generations: " << endl;
    // display population pool
    if(population_flag)
    {
        cout << "Population: " << endl;
        display_population(initials);
    }
    
    // find the shorest path and city's order from initial population
    pair<vector<int>, float> best_solution_2 = searching_minimum(initials);
    cout << "The order of the shorest distance: " << endl;
    for (int i = 0 ; i < best_solution_2.first.size() ; ++i)
    {
        cout << best_solution_2.first.at(i) << " ";
    }
    cout << endl;
    cout << "The shorest path of visiting all of the cities once is: " << best_solution_2.second << endl;
    cout << "========================================================" << endl;
    
    return 0;
}