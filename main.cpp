#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>


using namespace std;

double speed_c = 299792458.0;

struct spectral_line {
    string species;
    string chem_name;
    string qn;
    string linelist;
    double teo_freq;
    double teo_freq_error;
    double meas_freq;
    double meas_freq_error;
    double freq;
    double freq_error;
    string jpl_intensity;
    string siuj;
    string sij;
    string aij;
    string ast_intensity;
    string e_l_c;
    string e_l_k;
    string e_u_c;
    string e_u_k;
    int measured = -1;
    double wavelenght = NAN;

};

int reader(string filename, vector<spectral_line> *chunk_vector ){

    ifstream file (filename);
    string value;

    while (getline(file,value)){

        spectral_line temp;

        string tempNumber = "";

        stringstream strstr(value);
        getline(strstr,temp.species, ':');
        getline(strstr,temp.chem_name, ':');


        getline(strstr,tempNumber, ':');
        temp.teo_freq = (tempNumber != "") ? atof(tempNumber.data()): NAN;
        tempNumber = "";


        getline(strstr,tempNumber, ':');
        temp.teo_freq_error = (tempNumber != "") ? atof(tempNumber.data()): NAN;
        tempNumber = "";

        getline(strstr,tempNumber, ':');
        temp.meas_freq = (tempNumber != "") ? atof(tempNumber.data()): NAN;
        tempNumber = "";

        getline(strstr,tempNumber, ':');
        temp.meas_freq_error = (tempNumber != "") ? atof(tempNumber.data()): NAN;
        tempNumber = "";

        getline(strstr,temp.qn, ':');
        getline(strstr,temp.jpl_intensity, ':');
        getline(strstr,temp.siuj, ':');
        getline(strstr,temp.sij, ':');
        getline(strstr,temp.aij, ':');
        getline(strstr,temp.ast_intensity, ':');
        getline(strstr,temp.e_l_c, ':');
        getline(strstr,temp.e_l_k, ':');
        getline(strstr,temp.e_u_c, ':');
        getline(strstr,temp.e_u_k, ':');
        getline(strstr,temp.linelist, ':');

        chunk_vector->push_back(temp);

    }
    return 0;
}

spectral_line lineProccesor(spectral_line input){



    if (isnan(input.teo_freq) && isnan(input.meas_freq)){ // Check if any of the is set, if not we have a HUGE problem
        exit(42);
    }else if (!isnan(input.teo_freq)){ // If the Theorical value is set, use it
        input.freq = input.teo_freq;
        input.freq_error = input.teo_freq_error;
        input.measured=0;

    } else { // If not, it must mean that the Measured value is set so use it.
        input.freq = input.meas_freq;
        input.freq_error = input.meas_freq_error;
        input.measured=1;
    }
    input.wavelenght = speed_c/input.freq;
    return input;
}

int vectorProccesor(vector<spectral_line> * input, vector<spectral_line> * output )
{
    vector<spectral_line>::iterator inputIterator;


    for(inputIterator = input->begin(); inputIterator != input->end(); inputIterator++)
    {
        output->push_back(lineProccesor(*inputIterator));
    }

}


int main() {
    vector<spectral_line> holder;
    vector<spectral_line> output;
    string filename = "/home/teohoch/ClionProjects/Parallel LDAP Data Processing/splited/splatalogue 1000000-1500000.csv/splatalogue 1000000-1500000.csv.part0";
    reader(filename, &holder);
    cout.precision(15);


    cout<< "Tamaño: "<<holder.size() <<"\n";
    vectorProccesor(&holder,&output);
    cout<< "Tamaño: "<<output.size() <<"\n";
    cout<< holder[34].species<<" "<<holder[34].wavelenght<<"\n";
    cout<< output[34].species<<" "<<output[34].wavelenght<<"\n";

}