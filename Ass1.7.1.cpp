/* C++ Code Assignment 1- Bohr electron emission/absorption
Author: Nicholas Ormerod 10630873
Date: 01/02/2024

This code asks the user for an atomic number, an initial and final quantum number for the
emission or absorption energy of a photon. The code will also ask whether the user wants the units
to be in eV or J (or both) and then ask whether the calculation should be repeated for other given
values. All inputs are validated to give realistic integer values. */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits>
#include <sstream>

// Constants
const double Rydberg = 13.6; // Rydberg constant in eV
const double eV_to_J = 1.60218e-19; // Conversion factor from eV to Joules

// Function to calculate the energy of electron transition in eV
double calculate_transition_energy(int atomic_number, int initial_n, int final_n)
{
    return Rydberg * std::pow(atomic_number, 2) * (1 / std::pow(final_n, 2) - 1 / std::pow(initial_n, 2));
}

// Function to convert energy from eV to J
double convert_to_J(double energy_eV)
{
    return energy_eV * eV_to_J;
}

// Input validation function
int get_validated_input(const std::string& prompt, int min_val, int max_val, const std::string& error_msg)
{
    std::cout << prompt;
    std::string input_line;
    int valid_input;
    double temp_input;

    while(true)
    {
        std::getline(std::cin, input_line);
        std::istringstream stream(input_line);
        if(stream >> temp_input && !(stream >> input_line) && // Check for trailing characters
            temp_input >= min_val && temp_input <= max_val && std::floor(temp_input) == temp_input)
        {
            valid_input = static_cast<int>(temp_input);
            break;
        } else std::cout << error_msg;
    }
    return valid_input;
}

int main() 
{
    std::cout << "Bohr Atom Photon Energy Calculator" << std::endl;
    char repeat = 'y';
    do
    {
        // Validate and collect inputs from the user
        int atomic_number = get_validated_input("Enter the atomic number (< 250): ", 1, 249, "Please provide a realistic and integer: ");
        int initial_n = get_validated_input("Enter the initial quantum number (< 999): ", 2, 998, "Please provide a realistic integer: ");
        int final_n = get_validated_input("Enter the final quantum number (less than initial): ", 1, initial_n - 1, "Please provide a realistic integer less than the initial value: ");

        // Calculate the transition energy
        double transition_energy = calculate_transition_energy(atomic_number, initial_n, final_n);

        // User choice for output unit
        std::string output_unit;
        bool valid_input = false; // Initialise to false to enter the while loop

        while(!valid_input) 
        {
            std::cout << "Print energy in Joules (J), electron Volts (eV), or both? Enter J, eV, or both: ";
            std::getline(std::cin, output_unit); // Use getline to read the whole line, including spaces

            for(char &c : output_unit) // Convert input to lowercase
            {
                c = std::tolower(c);
            }

            if(output_unit == "j")
            {
                std::cout << "Transition Energy: " << std::setprecision(4) << convert_to_J(transition_energy) << " Joules" << std::endl;
                valid_input = true;
            }
            else if(output_unit == "ev")
            {
                std::cout << "Transition Energy: " << std::setprecision(4) << transition_energy << " eV" << std::endl;
                valid_input = true;
            }
            else if(output_unit == "both")
            {
            std::cout << "Transition Energy: " << std::setprecision(4) << transition_energy << " eV or " << std::setprecision(4) << convert_to_J(transition_energy) << " Joules" << std::endl;
            valid_input = true;
            }
            else std::cout << "Invalid unit. Please type 'J', 'eV', or 'both'\n";
        }

        // Checking for repeat
        std::cout << "Calculate another transition energy? (Y/N): "; 
        std::string repeat_var;
        std::cin >> repeat_var;
        repeat = tolower(repeat_var[0]);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer again
    }
    while (repeat == 'y');
    return 0;
}
