/* C++ Code Assignment 3- Practicing Classes 
Author: Nicholas Ormerod 10630873
Date: 04/03/2024

This code will define an object (class) called Leptons with all the desired constructors, and then
define a leptondetector consisting of three trackers. A vector of the different particles will be used
to print out information and then a vector of the different trackers will turn them on and pass all
particles through them, then turn them off.*/

#include<iostream>
#include<string>
#include<cmath>
#include <iomanip>

#define speed_c 2.99792458e8 // Speed of light in m/s as a preprocessor directive

class Lepton 
{
private:
  std::string particle_type; // "electron" or "muon"
  double rest_mass; // Mass in MeV
  int charge; // +1 for particles, -1 for antiparticles
  double velocity; // in m/s
  double beta; // velocity / speed of light

public:
  // Default constructor
  Lepton() : particle_type(""), rest_mass(0), charge(0), velocity(0), beta(0) {}

  // Parameterized constructor
  Lepton(std::string type, double mass, int ch, double vel)
      : particle_type(type), rest_mass(mass), charge(ch), velocity(0), beta(0) 
      {
      setVelocity(vel); // Validation step
      }

  // Destructor
  ~Lepton() {}

  // Setters with input validation
  void setParticleType(const std::string& type){particle_type = type; }
  void setRestMass(double mass){rest_mass = mass; }
  void setCharge(int ch){charge = ch; }
  void setVelocity(double vel) 
  {
    if(vel > speed_c) 
    {
      throw std::invalid_argument("Particle speed cannot exceed the speed of light.");
    }
    velocity = vel;
    beta = velocity / speed_c;
  }

  // Getters
  std::string getParticleType() const {return particle_type; }
  double getRestMass() const {return rest_mass; }
  int getCharge() const {return charge; }
  double getVelocity() const {return velocity; }
  double getBeta() const {return beta; }

  void antiparticle()
  {
    charge = -charge; // Make antiparticle with same properties but opposite charge
    particle_type = "anti" + particle_type; // Prefix the type with "anti"
  }

  void print_data() const;
};

class LeptonDetector
{
private:
  std::string detector_type;
  bool status;
  int detected_particles_count;

public:
  // Constructors
  LeptonDetector() : detector_type(""), status(false), detected_particles_count(0) {}
  LeptonDetector(const std::string& type, const std::string& stat) : detector_type(type), detected_particles_count(0)
  {
    status = (stat == "on"); //converts stat to status- a string to on/off to a bool true/false
  }

  // Destructor
  ~LeptonDetector() {}

  // Function to turn on/off the detector
  void turn_on() 
  {
    status = true;
    std::cout << detector_type << " detector has been turned on." << std::endl;
  }

  void turn_off() 
  {
    status = false;
    std::cout << detector_type << " detector has been turned off." << std::endl;
  }
  
  // Function to check if the detector is on
  bool is_on() const {return status; }

  // Function to detect a particle
  int detect(const std::string& particle_type)
  {
    if(!status)
    {
      std::cout << detector_type << " detector is off." << std::endl;
      return 0;
    }

    // Check if the particle is detected based on detector type
    if((detector_type == "tracker" && (particle_type == "electron" || particle_type == "muon" || particle_type == "antielectron" || particle_type == "antimuon")) ||
      (detector_type == "calorimeter" && (particle_type == "electron" || particle_type == "antielectron")) ||
      (detector_type == "muon chamber" && (particle_type == "muon" || particle_type == "antimuon")))
      {
        detected_particles_count++;
        std::cout << particle_type << " was detected by " << detector_type << " detector." << std::endl;
        return 1;
      }

    std::cout << particle_type << " was not detected by " << detector_type << " detector." << std::endl;
    return 0;
  }

  // Function to print detector information
  void print_data() const
  {
    std::cout << "\nDetector Type: " << detector_type << std::endl;
    std::cout << "Status: " << (status ? "On" : "Off") << std::endl;
    std::cout << "Detected Particles Count: " << detected_particles_count << "\n" << std::endl;
  }
};

// Main function to demonstrate class usage
int main()
{
  Lepton electron("electron", 0.511, -1, 55896354);
  Lepton muon("muon", 105.658, -1, 123456789);

  Lepton antielectron = electron; // Copy constructor implicitly used here
  Lepton antimuon = muon;
  antielectron.antiparticle(); // Now positron is an antiparticle of electron
  antimuon.antiparticle();

  //electron.print_data();
  //muon.print_data();
  //antielectron.print_data();
  //antimuon.print_data();

  // Test the LeptonDetector class
  LeptonDetector tracker("tracker", "on");
  LeptonDetector calorimeter("calorimeter", "off");
  LeptonDetector muonchamber("muon chamber", "on");

  // Turn on/off the detectors
  calorimeter.turn_on();
  tracker.turn_on();

  // Test particle detection
  tracker.detect("electron"); // true if on
  tracker.detect("muon"); // true if on
  calorimeter.detect("electron"); //true if on
  calorimeter.detect("mun"); //false
  muonchamber.detect("antimuon"); //true
  muonchamber.detect("antielectron"); //false

  // Print detector information
  tracker.print_data();
  calorimeter.print_data();
  muonchamber.print_data();

  return 0;

}
