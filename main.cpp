#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>


using namespace std;

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


}

int main() {
    vector<spectral_line> holder;
    string filename = "/home/teohoch/ClionProjects/Parallel LDAP Data Processing/splited/splatalogue 1000000-1500000.csv/splatalogue 1000000-1500000.csv.part0";
    reader(filename, &holder);
    cout.precision(15);
    

    cout<< "Tamaño: "<<holder.size() <<"\n";

}