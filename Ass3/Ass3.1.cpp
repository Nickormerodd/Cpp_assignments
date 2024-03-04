/* C++ Code Assignment 3- Practicing Classes 
Author: Nicholas Ormerod 10630873
Date: 04/03/2024

This code will define an object (class) called Leptons with all the desired constructors*/

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

// Function to print particle data
void Lepton::print_data() const
{
  std::cout << "\nParticle Type: " << particle_type << "\nRest Mass: "<< std::setprecision(4) << rest_mass
            << " MeV\nCharge: " << charge << "\nVelocity: " << std::setprecision(5) << velocity
            << " m/s\nBeta: " << std::setprecision(5) << beta << "\n" << std::endl;
}

// Main function to demonstrate class usage
int main()
{
  Lepton electron("electron", 0.511, -1, 55896354);
  Lepton muon("muon", 105.658, -1, 123456789);

  Lepton positron = electron; // Copy constructor implicitly used here
  Lepton antimuon = muon;
  positron.antiparticle(); // Now positron is an antiparticle of electron
  antimuon.antiparticle();

  electron.print_data();
  muon.print_data();
  positron.print_data();
  antimuon.print_data();

  return 0;

}
