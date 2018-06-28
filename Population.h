#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>

using namespace std;

class Population
{
private:
    int population_size = 0;
public:
    // constructor
    Population(int input_popu_size);
    ~Population(){};
    
    // create population pool
    vector< pair< vector<int>, float> > pool_generation( vector< vector <int> > initial_city, int start_city );
    
    // get the best candidate
    pair<vector<int>,float> get_fittest(vector< pair< vector<int>, float> > input_pool);
};

// constructor
Population::Population(int input_popu_size)
{
    population_size = input_popu_size;
    //pool = new PopulationPool[population_size];
}

// calculate the distance between two points
float the_distance(int from_point[2], int to_point[2])
{
    int x_distance = abs(from_point[0] - to_point[0]);
    int y_distance = abs(from_point[1] - to_point[1]);
    
    return sqrt((x_distance * x_distance) + (y_distance * y_distance));
}

// compute the distance
float get_distance(vector< vector <int> > initial_city)
{
    // declare variables
    float output_distance = 0.0;
    int city_from[2];
    int city_to[2];
    
    // looping
    for (int city_index = 0 ; city_index < initial_city.size() ; ++city_index)
    {
        
        // get city we are travelling from
        city_from[0] = initial_city[city_index][1];
        city_from[1] = initial_city[city_index][2];
        
        // get city we are travelling to
        if(city_index + 1 < initial_city.size())
        {
            city_to[0] = initial_city[city_index + 1][1];
            city_to[1] = initial_city[city_index + 1][2];
        }
        else
        {
            city_to[0] = initial_city[0][1];
            city_to[1] = initial_city[0][2];
        }
        
        // get the distance between two cities
        output_distance += the_distance(city_from, city_to);
    }
    return output_distance;
}

// compute fitness value
float get_fitness(float total_dist)
{
    float fitness_value = 0.0;
    fitness_value = 1.0 / total_dist;
    
    return fitness_value;
}

// Non-repeated number generation
int* non_repeated_number_generation(int total_number)
{
    int* output_array = new int[total_number];
    // fill index numbers into output array
    for (int i = 0 ; i < total_number ;i++)
    {
        output_array[i] = i;
    }
    
    // shuffle the output array
    for (int j = total_number - 1 ; j > 0 ; j--)
    {
        // get a new index
        int new_index = rand() % j;
        
        // swap index values, array[j] and array[new_index]
        int temp = output_array[j];
        output_array[j] = output_array[new_index];
        output_array[new_index] = temp;
    } // end shuffle loop
    
    return output_array;
}

// searching index function
int searching_index(int *input_array, int lengths,int target_value)
{
    int output_index = 0;
    for (int i = 0 ; i < lengths ; ++i)
    {
        if(input_array[i] == target_value)
        {
            output_index = i;
            break;
        }
    }
    
    return output_index;
}

// swap indexs function
int* swap_index(int *random_index_array, int input_index)
{
    int tmp = random_index_array[0];
    random_index_array[0] = random_index_array[input_index];
    random_index_array[input_index] = tmp;
    
    return random_index_array;
}

// create population pool
vector< pair< vector<int>, float> > Population::pool_generation(vector< vector <int> > initial_city, int start_city)
{
    vector< pair< vector<int>, float> > pool;
    
    // generate all candidates in the pool
    for (int i = 0 ; i < population_size ; ++i)
    {
        // create a tmp vector to store each individual and total distance
        vector<int> tmps;
        float tmp_distance;
        
        // generate non-repeated index array given data number
        int* random_index_array = non_repeated_number_generation(initial_city.size());
        
        // find city's index
        int target_index = searching_index(random_index_array, initial_city.size(), start_city - 1);
        
        // swap the positions between target index and the beginning index
        random_index_array = swap_index(random_index_array, target_index);
        
        // making new city's order, and making a new tour.
        for (int j = 0 ; j < initial_city.size() ; ++j)
        {
            tmps.push_back( initial_city[random_index_array[j]][0] );
        }
        
        // create a 2D vector for total distance computation
        vector < vector <int> > tmp_city_infor;
        for (int j = 0 ; j < initial_city.size() ; ++j)
        {
            vector <int> tmp_vec;
            for (int k = 0 ; k < initial_city[0].size() ; ++k)
            {
                tmp_vec.push_back( initial_city[random_index_array[j]][k] );
            }
            tmp_city_infor.push_back( tmp_vec );
        }
        
        // compute total distance given city information
        tmp_distance = get_distance(tmp_city_infor);
        
        // push tmps vector into pool vector
        pool.push_back( make_pair(tmps, tmp_distance));
    }
    
    return pool;
}

// find the best individual in population pool
pair<vector<int>,float> Population::get_fittest(vector< pair< vector<int>, float> > input_pool)
{
    // setting individual
    pair< vector<int>, float > tmp1 = input_pool[0];
    vector<int> vectors = tmp1.first;
    int individual_tour[vectors.size()];
    float initial_distance = tmp1.second;
    
    for (int i = 0 ; i < vectors.size() ; ++i)
    {
        individual_tour[i] = vectors.at(i);
    }
    
    // loop through each individual to find the best one
    for (int i = 1 ; i < population_size ; ++i)
    {
        // get new pair
        pair< vector<int>, float > new_pair = input_pool[i];
        vector<int> vectors2 = new_pair.first;
        float new_value = new_pair.second;
        
        if (get_fitness(initial_distance) <= get_fitness( new_value ))
        //if (inputs[i].distances < initial_distance)
        {
            for (int j = 0 ; j < vectors2.size() ; ++j)
            {
                individual_tour[j] = vectors2.at(j);
            }
            //individual_tour = initial_pool[i].city_order;
            
            initial_distance = new_pair.second;
        }
        
    }
    
    // convert array to vector
    vector<int> individual_tours(individual_tour, individual_tour + vectors.size());
    pair<vector<int>,float> output;
    output.first = individual_tours;
    output.second = initial_distance;
    
    return output;
}



















/*
 cout << "======" << endl;
 // display all individuals
 for (int i = 0 ; i < population_size ; ++i)
 {
 cout << "Order:" << endl;
 for (int j = 0 ; j < initial_city.size() ; ++j)
 {
 cout << pool[i].city_order[j] << " ";
 }
 cout << endl;
 cout << "Distance:" << pool[i].distances << endl;
 }
 */








/*
// Gets the best tour in the population
public Tour getFittest()
{
    Tour fittest = tours[0];
    // Loop through individuals to find fittest
    for (int i = 1; i < populationSize(); i++) {
 
        if (fittest.getFitness() <= getTour(i).getFitness()) {
            fittest = getTour(i);
        }
 
    }
 return fittest;
}
 */






/*
// Construct a population
public Population(int populationSize, boolean initialise) {
    tours = new Tour[populationSize];
    // If we need to initialise a population of tours do so
    if (initialise) {
        // Loop and create individuals
        for (int i = 0; i < populationSize(); i++) {
            Tour newTour = new Tour();
            newTour.generateIndividual();
            saveTour(i, newTour);
        }
    }
}
*/







