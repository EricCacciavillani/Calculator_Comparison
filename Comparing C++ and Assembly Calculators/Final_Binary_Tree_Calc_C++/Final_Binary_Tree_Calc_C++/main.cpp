/*
 Author: Eric Cacciavillani
 Class: C230-02
 Assignment: Assignment Trees
 Date Assigned: Nov 1,2016
 Due Date: Nov 8,2016
 Description:
 This program is designed to create a binary tree that calculates a infix expersion
 using a prefix conversion and multiple error checks to ensure we get the correct input
 Certification of Authenticity:
 I certify that this is entirely my own work, except where I have given
 fully-documented references to the work of others. I understand the
 definition and consequences of plagiarism and acknowledge that the assessor
 of this assignment may, for the purpose of assessing this assignment:
 - Reproduce this assignment and provide a copy to another member of
 academic staff; and/or
 - Communicate a copy of this assignment to a plagiarism checking
 service (which may then retain a copy of this assignment on its
 database for the purpose of future plagiarism checking)
 */


#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <limits>
typedef std::chrono::high_resolution_clock Clock;

#include "Binary_Cal_Tree.h"

#define TEST_AMOUNT 10000


using namespace std;

//For future refrence (alt + -)"–" != "-". They are in fact different. I use '-'. In short be careful when copying and pasting equations in!!!

map<string,double> get_test_cases(const string abs_input_file_path)
{
    
    // Open file with default file name
    ifstream file (abs_input_file_path);
    
    // ---
    if (!file)
    {
        cout << "Unable to open file: Test Cases.txt\n";
        exit(1); //Terminate code with error
    }
    
    string file_line;
    
    // Maping the string equation to the answer
    map<string,double> equation_solution;
    
    // Iterate through file
    while(getline(file, file_line))
    {
        cout << file_line << "\n";
        // Delete all spaces in the string
        file_line.erase(remove_if(file_line.begin(), file_line.end(), ::isspace), file_line.end());
        
        try
        {
            // Split the string by the "=" to get the equation and the answer
            std::size_t pos = file_line.find("=");
            equation_solution[file_line.substr(0,pos)] = stod((file_line.substr(pos)).erase(0,1));
            cout << file_line << "\n";
            
        }
        // De-Bugging catch cases.
        catch (out_of_range)
        {
            cout << "Caught out of range!!!\n";
        }
        catch (invalid_argument)
        {
            cout << "Solution is not equal to a real number!!!\n";
        }
        
    }
    
    file.close();
    
    return equation_solution;
}

// Finds the standard deviation
double getStandardDeviation(double mean,unsigned long timed_data[],size_t size)
{
    double standard_deviation = 0.0;
    
    for(int i = 0; i < size; ++i)
    {
        standard_deviation += pow(timed_data[i] - mean, 2);
    }
    
    return sqrt(standard_deviation / size);
}


int main(int argc, const char * argv[])
{
    // Variables to handle the calculator
    Binary_Cal_Tree calculator;
    
    string equation_str;
    double equated_value;
    bool error_handling = EXIT_SUCCESS;
    
    // ::: CHNAGE ON YOUR OWN SYSTEM :::
    const string local_project_directory = "/Users/ericcacciavillani/Desktop/";
    //----------------------------------------------------------------------------
    
    // Path for the test cases
    const string abs_input_file_path = local_project_directory + "Calculator_Comparison/Comparing\ C++\ and\ Assembly\ Calculators/test_cases.txt";
    const string abs_output_file_path = local_project_directory + "Calculator_Comparison/Comparing\ C++\ and\ Assembly\ Calculators/Test\ Case\ Results/C++_Test_Results.txt";
    
    
    // Get equations to answers map
    map<string,double> equation_solution = get_test_cases(abs_input_file_path);
    map<string, double>::iterator it;
    
    // Output file handler
    ofstream outputFile;
    outputFile.open (abs_output_file_path);
    
    if (!outputFile)
    {
        cout << "Unable to open file: Teshght Cases.txt\n";
        exit(1); //Terminate code with error
    }
    
    // Vars for time evaluation
    unsigned long timed_data[TEST_AMOUNT];
    
    unsigned long long total_test_time = 0,
                       total_all_best_times = 0,
                       total_all_average_times = 0;
    
    unsigned long best_time_case;
    
    double mean,
           standard_deviation,
           best_case_z_score;
    
    unsigned int equation_counter = 0;
    // ---
    
    
    for ( it = equation_solution.begin(); it != equation_solution.end(); it++ )
    {
        equation_str = it->first;
        cout << equation_str << "\n";
        
        // ---
        calculator.create_tree_with_infix(equation_str);
        
        total_test_time = 0.0;
        best_time_case = numeric_limits<long>::max();
        
        // Peform multiple tests on the
        for(int i = 0; i < TEST_AMOUNT;i++)
        {
            auto start = Clock::now();
            equated_value = calculator.evaluate_tree(error_handling);
            auto end = Clock::now();
            
            timed_data[i] = (unsigned int)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
            
            total_test_time += timed_data[i];
            
            if(best_time_case > timed_data[i])
            {
                best_time_case = timed_data[i];
            }
            
        }
        
        mean = total_test_time/TEST_AMOUNT;
        standard_deviation = getStandardDeviation(mean, timed_data,TEST_AMOUNT);
        best_case_z_score = (mean-best_time_case)/standard_deviation;
        
        
        total_all_best_times += best_time_case;
        total_all_average_times += mean;
        
        if (equated_value == INFINITY)
        {
            cout << "\nError: Your equation is infinite!\n";
        }
        else if(error_handling == EXIT_SUCCESS)
        {
            ostringstream os;
            os << "\t\t   Equation Test #" << equation_counter + 1 << "\n" << string(40, '=')
                 << "\n\t\t  " << equation_str << " = " << equated_value << "\n"
                 << "\nAverage Time Taken:   " << mean << " nanoseconds"
                 << "\nBest Time Taken:      " << best_time_case << " nanoseconds"
                 << "\nZ-Score of best time: " << best_case_z_score
                 << "\nStandard Deviation:   " << standard_deviation << " nanoseconds\n"
                 << "\nTest Case is : ";
            
            
            if ((int)(equated_value * 1000.0)/1000.0 == it->second)
            {
                os << "CORRECT!" << "\n";
            }
            else
            {
                os << "WRONG!" << "\n";
                outputFile.close();
                
                exit(1);
            }
            os << string(40, '-') << "\n\n";
            cout << os.str();
            outputFile << os.str();

            
            equation_counter++;
        }
        else
        {
            cout << "\nError: An error has occured while evaluting the tree\n";
        }
        
    }
    outputFile.close();
    
    cout << ":::Final Results of Non-Assembly Calculator:::\n"
         << string(46,'=') << "\n\n"
         << "Average of all best case testing operations :    " << total_all_best_times/equation_counter
         << " nanoseconds \n"
         << "Average of all average case testing operations : " << total_all_average_times/equation_counter
         << " nanoseconds \n"
         << "\n" << string(46,'=') << "\n";
    
    return 0;
}
