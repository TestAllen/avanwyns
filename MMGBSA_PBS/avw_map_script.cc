//creates maps from mmgbsa data

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;


int main(int argc, char *argv[])
{
	int frames;
	ifstream input;
	ofstream output;
	string filename;
	double temp;
//input files
	string ivc = "vdw_complex"; 	
  	string ivr = "vdw_receptor";
	string ivl = "vdw_ligand";


	string iec = "eel_complex"; 	
  	string ier = "eel_receptor";
	string iel = "eel_ligand";
	

	string igc = "egb_complex"; 	
  	string igr = "egb_receptor";
	string igl = "egb_ligand";


	string isc = "esurf_complex"; 	
  	string isr = "esurf_receptor";
	string isl = "esurf_ligand";
	string filelist[12] = {ivc,ivr,ivl,iec,ier,iel,igc,igr,igl,isc,isr,isl};

//output files
	string odv = "delta_vdw";
	string ode = "delta_eel";
	string odg = "delta_egb";
	string ods = "delta_esurf";
	
	string oseg = "sum_eel_egb";
	string osvs = "sum_vdw_esurf";
	
	string odelg = "delta_G";


//determine # of frames
	
	if(argc != 2)
	{
		cerr << "\n Error ---> Usage: ./avw_map_script <# of frames>\n\n";
		return 0;
	}
	else
	{
		frames = atoi( argv[1] );
	}
	
//initialize arrays
	vector<double> initial(frames, 0.0);
	vector< vector<double> > inputValues(12, initial);
	vector< vector<double> > outputValues(6, initial);


//check that files are available 	

	for(int i=0;i<12;i++)
	{
		filename=filelist[i];
		input.open(filename.data());
		if(!input.is_open())
		{
			cerr << "\n Could not open " << filename << "!!!\n\n";
			return 0;
		}
		input.close();
	}
	cout << "\n.....All Files Available.....\n";	

//read in data

	for(int i=0;i<12;i++)
	{
		filename = filelist[i];
		input.open(filename.data());
		if(!input.is_open())
		{	
			cerr << "\n Could not open " << filename << "!!!\n\n";
			return 0;
		}
		
		for(int j=0;j<frames;j++)
		{
			input >> inputValues[i][j];
			if(input.eof())
			{
				cerr << "\n Error ---> Number of entered frames (" << frames << ") is greater than number of lines in " << filename << "!!!\n\n";
				return 0;
			}
		}
		input >> temp;
		if(!input.eof())
		{
			cerr << "\n Error ---> Number of entered frames (" << frames << ") is less than number of lines in " << filename << "!!!\n\n";
			return 0;
		}
		input.close();
	}
	cout << "\n.....Data Read In.....\n";
	
//VDW calculation

	output.open(odv.data());
	for(int i=0;i<frames;i++)
	{
		outputValues[0][i] = inputValues[0][i] - inputValues[1][i] - inputValues[2][i];
		output << fixed << setprecision(4) << outputValues[0][i] << "\n";	
	}	
	output.close();
	cout << "\n.....VDW calculation done.....\n";

//EEL calculation

	output.open(ode.data());
	for(int i=0;i<frames;i++)
	{
		outputValues[1][i] = inputValues[3][i] - inputValues[4][i] - inputValues[5][i];
		output << fixed << setprecision(4) << outputValues[1][i] << "\n";	
	}	
	output.close();
	cout << "\n.....EEL calculation done.....\n";

//EGB calculation

	output.open(odg.data());
	for(int i=0;i<frames;i++)
	{
		outputValues[2][i] = inputValues[6][i] - inputValues[7][i] - inputValues[8][i];
		output << fixed << setprecision(4) << outputValues[2][i] << "\n";	
	}	
	output.close();
	cout << "\n.....EGB calculation done.....\n";

//ESURF calculation

	output.open(ods.data());
	for(int i=0;i<frames;i++)
	{
		outputValues[3][i] = inputValues[9][i] - inputValues[10][i] - inputValues[11][i];
		output << fixed << setprecision(4) << outputValues[3][i] << "\n";	
	}	
	output.close();
	cout << "\n.....ESURF calculation done.....\n";

//EEL+EGB calculation

	output.open(oseg.data());
	for(int i=0;i<frames;i++)
	{
		outputValues[4][i] = outputValues[1][i] + outputValues[2][i];
		output << fixed << setprecision(4) << outputValues[4][i] << "\n";	
	}	
	output.close();
	cout << "\n.....EEL+EGB calculation done.....\n";

//VDW+ESURF calculation

	output.open(osvs.data());
	for(int i=0;i<frames;i++)
	{
		outputValues[5][i] = outputValues[0][i] + outputValues[3][i];
		output << fixed << setprecision(4) << outputValues[5][i] << "\n";	
	}	
	output.close();
	cout << "\n.....VDW+ESURF calculation done.....\n";

//dG calculation

	output.open(odelg.data());
	for(int i=0;i<frames;i++)
	{
		output << fixed << setprecision(4) << outputValues[5][i] + outputValues[4][i] << "\n";	
	}	
	output.close();
	cout << "\n.....dG calculation done.....\n";
return 0;
}
