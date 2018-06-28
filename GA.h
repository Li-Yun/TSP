#include <iostream>
#include <vector>
#include "Population.h"

using namespace std;

class GA
{
private:
    double mutation_rate = 0.0;
    int selection_pool_Size = 0;
public:
    // constructor
    GA(double input_rate, int input_size);
    ~GA(){};
    
    // generate initial population
    vector< pair< vector<int>, float> > initial_population(vector< vector <int> > cities, int start_city, int N_popul);
    
    // envolve function
    vector< pair< vector<int>, float> > evolvePopulation(vector< pair< vector<int>, float> > inputs, vector< vector <int> > cities, int start_city, int N_popul);
};

// constructor
GA::GA(double input_rate, int input_size)
{
    mutation_rate = input_rate;
    selection_pool_Size = input_size;
}

// find the difference given two individuals
vector<int> find_difference(vector<int> input_vector, int input_array[])
{
    vector<int> small_vector;
    // convert int array to int vector
    vector<int> tmp(input_array, input_array + input_vector.size());
    
    // find difference
    for (int i = 1 ; i < input_vector.size() ; ++i)
    {
        // set flag variable
        int equality_flag = 0;
        // loop through another vector
        for (int j = 1 ; j < input_vector.size() ; ++j)
        {
            if ( input_vector.at(i) == tmp.at(j) )
            {
                equality_flag = 1;
            }
        }
        
        if (equality_flag == 0)
        {
            small_vector.push_back(input_vector.at(i));
        }
    }
    
    return small_vector;
}

// find zero positions
vector<int> searching_zeros(int input_array[], int lengths)
{
    vector<int> output_vector;
    
    for(int i = 1 ; i < lengths ; ++i)
    {
        if (input_array[i] == 0)
        {
            output_vector.push_back(i);
        }
    }
    
    return output_vector;
}

// mutation function
pair<vector<int>, float> mutation(pair<vector<int>, float> individual, vector<vector<int>> city_inf, float mutation_rate)
{
    // Loop
    for (int pos_index = 1 ; pos_index < individual.first.size() ; ++pos_index)
    {
        double random_value_1 = (double)rand() / ((double)RAND_MAX + 1);
        //apply mutation rate
        if (random_value_1 < mutation_rate)
        {
            // get the second random number between 1 to length - 1 in the individual
            int random_position_2 = (rand() % (individual.first.size() - 1)) + 1;
            
            // get two cities in the individual
            int city1 = individual.first.at(pos_index);
            int city2 = individual.first.at(random_position_2);
            
            // swap two positions
            individual.first.at(pos_index) = city2;
            individual.first.at(random_position_2) = city1;
        }
    }
    
    // re-compute total distance
    vector<vector<int>> tmp_2d_vec;
    for (int i = 0 ; i < city_inf.size() ; ++i)
    {
        vector<int> small_vec;
        for (int j = 0 ; j < city_inf[0].size() ; ++j)
        {
            small_vec.push_back( city_inf[individual.first.at(i) - 1][j] );
        }
        tmp_2d_vec.push_back( small_vec );
    }
    
    // record child
    pair<vector<int>, float> individual_output;
    individual_output.first = individual.first;
    individual_output.second = get_distance(tmp_2d_vec);
    
    return individual_output;
}

// doing cross over opeartions   ==> change the output format.
pair<vector<int>, float> cross_over(vector<int> parent1, vector<int> parent2, vector<vector<int>> city_info)
{
    // create a new child city order
    int tmp_array[parent1.size()];
    for (int i = 0 ; i < parent1.size() ; ++i)
    {
        tmp_array[i] = 0;
    }
    
    // generate start position and end position for crossover operation
    int start_pos = (rand() % (parent1.size() - 1)) + 1;
    int end_pos = (rand() % (parent1.size() - 1)) + 1;
    
    // Loop, and add sub-fragment into child's city order
    for (int i = 0 ; i < parent1.size() ; ++i)
    {
        if (i == 0)
        {
            tmp_array[i] = parent1.at(0);
        }
        // If start position is less than the end position
        if (start_pos < end_pos && i > start_pos && i < end_pos)
        {
            tmp_array[i] = parent1.at(i);
        }
        // If the start position is larger
        else if (start_pos > end_pos)
        {
            if (!(i < start_pos && i > end_pos))
            {
                tmp_array[i] = parent1.at(i);
            }
        }
    }
    
    // find difference
    vector<int> difference_set = find_difference(parent2, tmp_array);
    // find zero positions
    vector<int> zero_positions = searching_zeros(tmp_array, parent2.size());
    // add different elements into the offspring
    for (int i = 0 ; i < difference_set.size() ; ++i)
    {
        tmp_array[zero_positions.at(i)] = difference_set.at(i);
    }
    
    // convert array to vector
    vector<int> tmp_child(tmp_array, tmp_array + parent1.size());
    
    // create a tmp vector for distance computation
    vector<vector<int>> tmp_2d_vec;
    for (int i = 0 ; i < city_info.size() ; ++i)
    {
        vector<int> small_vec;
        for (int j = 0 ; j < city_info[0].size() ; ++j)
        {
            small_vec.push_back( city_info[tmp_child.at(i) - 1][j] );
        }
        tmp_2d_vec.push_back( small_vec );
    }
    
    // record child
    pair<vector<int>, float> child;
    child.first = tmp_child;
    child.second = get_distance(tmp_2d_vec);
    
    return child;
}

// individual selection
vector<int> individu_selection(vector< pair< vector<int>, float> > pop, vector< vector <int> > cities, int start_city, int selection_pool_Size)
{
    // create a selection pool
    Population *new_pool = new Population(selection_pool_Size);
    vector< pair< vector<int>, float> > select_pool = new_pool -> pool_generation(cities, start_city);
    
    // get a random individual from selection pool
    for (int i = 0 ; i < selection_pool_Size ; ++i)
    {
        // generate a random ID
        int randNum = rand() % ((pop.size() - 1) - 0 + 1) + 0;
        
        // ada a selected individual into selection pool
        //par<vector<int>, float> single = pop[randNum];
        select_pool[i] = pop[randNum];
    }
    
    // get the fittest individual
    pair<vector<int>,float> output = new_pool -> get_fittest(select_pool);
    
    return output.first;
}

// generate initial population
vector< pair< vector<int>, float> > GA::initial_population(vector< vector <int> > cities, int start_city, int N_popul)
{
    // create an initial pool
    // generate initial population
    Population *popu_pool = new Population(N_popul);
    vector< pair< vector<int>, float> > initial_popus = popu_pool -> pool_generation(cities, start_city);
    
    return initial_popus;
}

// evolving population, update individuals in the pool
vector< pair< vector<int>, float> > GA::evolvePopulation(vector< pair< vector<int>, float> > inputs, vector< vector <int> > cities, int start_city, int N_popul)
{
    // grab an individual with the highest fitness value
    Population *popu_pool = new Population(N_popul);
    
    // create a new population pool
    vector< pair< vector<int>, float> > new_pool = popu_pool -> pool_generation(cities, start_city);
    
    // Keep our best individual
    pair<vector<int>,float> the_best_individual = popu_pool -> get_fittest(inputs);
    
    // add the best individual to the new pool
    new_pool.at(0) = the_best_individual;
    
    
    /*
    cout << "The best individual in the initial pool:" << endl;
    for (int i = 0 ; i < the_best_individual.first.size() ; ++i)
    {
        cout << the_best_individual.first[i] << " ";
    }
    cout << endl;
    cout << the_best_individual.second << endl;
    cout << "================" << endl;
    */
    
    // Crossover population
    // Loop over the new population pool, and create new individuals from the input population
    for (int i = 1 ; i < new_pool.size() ; ++i)
    {
        // select parents
        vector<int> parent_1 = individu_selection(inputs, cities, start_city, selection_pool_Size);
        vector<int> parent_2 = individu_selection(inputs, cities, start_city, selection_pool_Size);
        
        // Crossover parents
        pair<vector<int>, float> child = cross_over(parent_1, parent_2, cities);
        
        // Add child to new population
        new_pool.at(i) = child;
    }
    
    // Mutation operation
    for (int i = 1 ; i < new_pool.size() ; ++i)
    {
        new_pool.at(i) = mutation(new_pool.at(i), cities, mutation_rate);
    }
    
    return new_pool;
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    cout << "==========" << endl;
    //dipaly
    for (int i = 0 ; i < N_popul ; ++i)
    {
        pair< vector<int>, float> aa = inputs[i];
        vector<int> indivi = aa.first;
        
        for (int j = 0 ; j < indivi.size() ; ++j)
        {
            cout << indivi[j] << " ";
        }
        cout << aa.second << endl;
    }
    */
    
    
    
}
























/*
// Evolves a population over one generation
public static Population evolvePopulation(Population pop) 
{
    //ok.
    Population newPopulation = new Population(pop.populationSize(), false);

 
 

 
 
    //ok.
    // Keep our best individual if elitism is enabled
    int elitismOffset = 0;
    if (elitism) {
        newPopulation.saveTour(0, pop.getFittest());
        elitismOffset = 1;
    }
    
 
 

 
 
    ok.
    // Crossover population
    // Loop over the new population's size and create individuals from Current population
    for (int i = elitismOffset; i < newPopulation.populationSize(); i++) {
        // Select parents
        Tour parent1 = tournamentSelection(pop);
        Tour parent2 = tournamentSelection(pop);
        // Crossover parents
        Tour child = crossover(parent1, parent2);
        // Add child to new population
        newPopulation.saveTour(i, child);
    }
    
 
 
 
 
 
 
    // Mutate the new population a bit to add some new genetic material
    for (int i = elitismOffset; i < newPopulation.populationSize(); i++) {
        mutate(newPopulation.getTour(i));
    }
    
 
 
 
 
    return newPopulation;
}
*/



















/*
// Applies crossover to a set of parents and creates offspring
public static Tour crossover(Tour parent1, Tour parent2)
{
    // Create new child tour
    Tour child = new Tour();
    
    // Get start and end sub tour positions for parent1's tour
    int startPos = (int) (Math.random() * parent1.tourSize());
    int endPos = (int) (Math.random() * parent1.tourSize());
 
 
    // Loop and add the sub tour from parent1 to our child
    for (int i = 0; i < child.tourSize(); i++) 
    {
        // If our start position is less than the end position
        if (startPos < endPos && i > startPos && i < endPos) 
        {
            child.setCity(i, parent1.getCity(i));
        
        } // If our start position is larger
        else if (startPos > endPos) 
        {
            if (!(i < startPos && i > endPos)) 
            {
                child.setCity(i, parent1.getCity(i));
            }
        }
    }
    
 
 
 
 

 
    //
    // Loop through parent2's city tour
    for (int i = 0; i < parent2.tourSize(); i++) 
    {
        // If child doesn't have the city add it
        if (!child.containsCity(parent2.getCity(i))) 
        {
            // Loop to find a spare position in the child's tour
            for (int ii = 0; ii < child.tourSize(); ii++) 
            {
                // Spare position found, add city
                if (child.getCity(ii) == null) 
                {
                    child.setCity(ii, parent2.getCity(i));
                    break;
                }
            }
        }
    }

 
 
 
 
 
    return child;
}
 */








