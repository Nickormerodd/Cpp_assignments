
/* C++ Code Assignment 2- Physics Course Database
Author: Nicholas Ormerod 10630873
Date: 21/02/2024

Part 1
This code will read in values of course grades, numbers, and names from a dat file
It will determine the number of data entries in the file and compute the mean, standard
deviation and standard error of the mean for the coursework marks.

Part 2
It will also use a vector to print a list of courses in a selected school year (and iterate print them),
chosen by the user, and will compute the mean and stddev of those courses, after asking the user
whether the courses will be sorted by title or by course code. All user inputs are validated. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <cctype>

struct Course_st
{
  double mark;
  int course_number;
  std::string course_name;
};

// Function which reads data from dat file and returns a vector of courses
std::vector<Course_st> read_courses(const std::string& filename, int& num_entries) 
{
  std::vector<Course_st> courses;
  std::ifstream file{filename}; // Creates input file stream for reading from files

   std::cout<< "Physics Course Database" << std::endl;

  if(!file.is_open()) // Returns whether the stream is NOT assosciated to a file
  {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return courses;
  }

  std::string line;
  while(getline(file, line)) 
  {
    if(file.fail())
      {
        std::cerr << "Failed to read data from the file." << std::endl;
        break;
      }
    std::istringstream iss{line}; // Makes an istringstream called iss and fills with line contents
    Course_st course;
    if(iss >> course.mark >> course.course_number >> std::ws) // iss contents stored in mark and number std::ws removes white space
      {
        getline(iss, course.course_name); // If previous was successful, store course name
        courses.push_back(course); // Adds fully read course to a vector called courses
      }
  }

  if(file.eof()) // Reached end of file
  {
    num_entries = static_cast<int>(courses.size());
  } 
  else 
  {
    std::cerr << "Did not reach the end of the file successfully." << std::endl;
    num_entries = -1; // Error for not reaching EOF
  }

  file.close();
  return courses;
}

// Function to calculate statistics
void calculate_statistics(const std::vector<Course_st>& courses) 
{
  if(courses.empty()) 
  {
    std::cerr << "No course data available to calculate statistics." << std::endl;
    return;
  }

  double sum = 0;
  for(const Course_st& course : courses) 
  {
    sum += course.mark;
  }

  double mean = sum / courses.size();
  double variance = 0;

  for(const Course_st& course : courses) 
  {
    variance += std::pow((course.mark - mean),2);
  }

  double stddev = std::sqrt(variance / (courses.size() - 1));
  double stderror = stddev / std::sqrt(courses.size());

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Mean: " << mean << std::endl;
  std::cout << "Standard Deviation: " << stddev << std::endl;
  std::cout << "Standard Error: " << stderror << std::endl;
}

// Function to validated user input of year filters from main
bool validate_year_input(const std::string& year_input)
{
  if(year_input == "no") // Check if input is "no" first
  {
    return true;
  }

  for(char c : year_input) // Check if input contains only digits and commas
  {
    if(!std::isdigit(c) && c != ',')
    {
      return false;
    }
  }

  std::istringstream iss(year_input); // Check if each number is within the valid range [1, 4]
  std::string token;
  while(getline(iss, token, ','))
  {
    int year = std::stoi(token);
    if(year < 1 || year > 4)
    {
      return false;
    }
  }
  return true;
}

// Function to validate sort criteria
bool validate_sort_criteria(const std::string& sort_str)
{
  std::string lowercase_sort_str = sort_str;
  std::transform(lowercase_sort_str.begin(), lowercase_sort_str.end(), lowercase_sort_str.begin(), ::tolower); // Lowercased

  return lowercase_sort_str == "title" || lowercase_sort_str == "number"; // True if input is "title" or "number"
}

// Function to filter courses based on the year input from main
std::vector<Course_st> filter_courses(const std::vector<Course_st>& courses, const std::string& year_input) 
{
  std::vector<Course_st> filtered_courses;

  if(!validate_year_input(year_input)) 
  {
    std::cerr << "Invalid input format. Please type in the specified format (e.g., '1', 'no' or '1,2')" << std::endl;
    return filtered_courses; // Return an empty vector if input is invalid
  }

  if(year_input != "no") // Process the filtered courses based on the validated year input
  {
    std::istringstream iss(year_input);
    std::string year;
    while(getline(iss, year, ',')) 
    {
      char target_year = year[0]; // Extract the characters (digits) from the input year
      for(const auto& course : courses) 
      {
        char course_year = std::to_string(course.course_number)[0]; // Extract the first digit of course number
        if(course_year == target_year) 
        {
          filtered_courses.push_back(course);
        }
      }
    }
    std::cout << "\nComputing statistics for year(s) " << year_input << std::endl;
  } 
  else 
  {
    filtered_courses = courses; // No filter applied
    std::cout << "\nComputing statistics for all courses" << std::endl;
  }
  return filtered_courses;
}

// Function to print and compute filtered courses full name and statistics
void print_and_compute(const std::vector<Course_st>& courses, const std::string& year_input, const std::string& sort_str) 
{
  std::vector<Course_st> filtered_courses = filter_courses(courses, year_input);
  std::cout << "Number of  selected data entries: " << filtered_courses.size() << std::endl; // Number of entries
  calculate_statistics(filtered_courses); // Calculate and print statistics for filtered courses

  if(!validate_sort_criteria(sort_str)) // Validate the sorting criteria
  {
    std::cerr << "Invalid sort criteria. Please type 'title' or 'number'." << std::endl;
    return; // Exit if invalid criteria
  }

  // Sorting based on input from main (from user)
  if(sort_str == "title")
  {
    std::sort(filtered_courses.begin(), filtered_courses.end(), [](const Course_st& a, const Course_st& b)
    {
      return a.course_name < b.course_name;
    });
  } 
  else if(sort_str == "number") 
  {
    std::sort(filtered_courses.begin(), filtered_courses.end(), [](const Course_st& a, const Course_st& b)
    {
      return a.course_number < b.course_number;
    });
  }

  for(const auto& course : filtered_courses) // Print the courses in sorted order
  {
    std::cout << "PHYS " << course.course_number << " " << course.course_name << std::endl;
  }
}

int main() 
{
  const std::string filename{"courselist.dat"};
  int num_entries = 0;
  std::vector<Course_st> courses = read_courses(filename, num_entries);

  if(num_entries <= 0) 
  {
    std::cerr << "No course data available." << std::endl;
    return 1;
  }

  print_and_compute(courses, "no", "number"); // Prints all courses in default order 

  std::string repeat_calculation;
  do 
  {
    // Get year filter
    std::string year_input;
    do
    {
      std::cout << "Is there a specific year [1,2,3,4] that you would like to view, or [no]? ";
      std::cin >> year_input;
      if(!validate_year_input(year_input))
      {
        std::cerr << "Please type in the specified format (e.g., '1', 'no' or '1,2')" << std::endl;
      }
    } 
    while(!validate_year_input(year_input));

    // Get sort string
    std::string sort_str;
    do
    {
      std::cout << "Would you like the courses to be sorted by course [title] or by course unit [number]? ";
      std::cin >> sort_str;
      if(!validate_sort_criteria(sort_str))
      {
        std::cerr << "Invalid sort criteria. Please type 'title' or 'number'." << std::endl;
      }
     } 
    while(!validate_sort_criteria(sort_str));

    print_and_compute(courses, year_input, sort_str);

    // Get repeat calculation
    std::cout << "Would you like to repeat the calculation [yes] or [no]? "; // Ask user if they want to repeat the calculation
    std::cin >> repeat_calculation;
    while(repeat_calculation != "yes" && repeat_calculation != "no") 
    {
      std::cerr << "Please type 'yes' or 'no'." << std::endl;
      std::cout << "Would you like to repeat the calculation [yes] or [no]? "; 
      std::cin >> repeat_calculation;
    }
  } 
  while(repeat_calculation == "yes");
  return 0;
}