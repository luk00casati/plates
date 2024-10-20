#include "cpiatti.hpp"
#include <string>

int main(){
    std::string inputfilename = "examples/upper.piatti"; 
    std::string outputfilename = "output.irpiatti";
    genir(inputfilename, outputfilename);
}
