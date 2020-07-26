#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    int h = seconds/(60 * 60);
    seconds = seconds - (h * 60 * 60);
    int m = seconds/(60);
    int seconds1 = seconds - ( m * 60 );
    
    string hours = std::to_string(h);
    string minutes = std::to_string(m);
    string total_seconds = std::to_string(seconds1);
    return hours + ":" + minutes + ":" + total_seconds; }