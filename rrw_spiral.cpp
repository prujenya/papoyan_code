#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "vectorio.h" //We have created this library that saves received data in the Mathematica format of a Table, which can then be visualized using Mathematica.
using namespace std;

int main()
{
	ofstream file;
	file.precision(16);
	cout.precision(16);
	int const l = 500; //lattice size
	long int T = 5000; //number of steps out of clockwise cycles
	int bb1 = 0;
	int bb2 = 0;
	int bb3 = 0;
	int dd = 0;
	int m, i, j, i0, j0, i00, j00, ii, jj, iii, jjj, il, jl, k, p;
	int a[4] = { 3, 0, 1, 2 };
	int b[4] = { 0, 1, 0, -1 };
	int c[4] = { 1, 0, -1, 0 };
	srand(time(NULL));
	long int t, t0, tt, ttt, tl, R;
	vector<long int> Fn0(500, 0);//table for count of returns for each turn
    vector<long int> Ftn0(500, 0);//table count of total returns for each turn
	vector<vector<int>  > z(l, vector<int>(l, 0)); //lattice with configurations of arrows
	vector<vector<int>  > z0(l, vector<int>(l, 0));
	vector<vector<int>  > z1(l, vector<int>(l, 0));
	vector<vector<int>  > z2(l, vector<int>(l, 0));
	vector<int> Iall( 10*T, 0);   //i coordinates of the chip
	vector<int> Jall( 10*T, 0);  //j coordinates of the chip
	vector<int> II(10*T, 0);     //i coordinates of the nodes
	vector<int> JJ(10*T, 0);     //j coordinates of the nodes
	vector<int> I(T, -1);
	vector<int> J(T, -1);
	int ddd = 0;
	int mm = -1;
	long int n0 = 0;   //count of returns for each turn
	long int tn0 = 0;  //count of total returns for each turn
    long int M = 0;   //count of labels
	long int TTT = 0;
	int faz = 0; //count of turns of spiral

//////////////////////////////////////////////////////////////////////

	// initial random configuration of the arrows

	for (k = 0; k < l; k ++)
	{
		for (p = 0; p < l; p ++)
		{
			z[k][p] = rand() % 4;
			z0[k][p] = z[k][p];
		};
	};

/////////////////////////////////////////////////////////////////////

    //starting point

	i = l / 2;
	j = l / 2;
/////////////////////////////////////////////////////////////////////

//The chip moves according to the RRW rules. For each position of the chip, we check if this site is
//on the clockwise cycle of arrows (excluding elementary cycles). If it is, we then check if the
//conditions for a node are met. If they are, we declare this position as a node and calculate
//the number of turns in the spiral. During this process, we also keep track of the number of times
//we have returned to the starting position at each turn of the spiral.

   	for (t = 1; t < T; t++)
	{
////////////////////////////////////////
     // check the  elementary cycles
		int TT = 0;
		int d = 0;
		int j1 = b[z[i][j]];
		int i1 = c[z[i][j]];

		if (z[i][j] == 0 && z[i + i1][j + j1] == 2) { d = 1; dd ++; };
		if (z[i][j] == 1 && z[i + i1][j + j1] == 3) { d = 1; dd ++; };
		if (z[i][j] == 2 && z[i + i1][j + j1] == 0) { d = 1; dd ++; };
		if (z[i][j] == 3 && z[i + i1][j + j1] == 1) { d = 1; dd ++; };
////////////////////////////////////////////////////////////////////////////
		if (d == 0)
		{
		    // check the clockwise cycle

			ii = i;
			jj = j;
			int cl = 0;
			int ac = 0;

			I[0] = i;
			J[0] = j;

			for (tt = 1; tt < T; tt ++)
			{
				z1[ii][jj] = 1;
				int i2 = c[z[ii][jj]];
				int j2 = b[z[ii][jj]];
				ii += i2;
				jj += j2;
				if (ii <= 0 || ii >= l - 1 || jj <= 0 || jj >= l - 1) {bb2 ++; break;};
				I[tt] = ii;
				J[tt] = jj;

				if ((z[ii - i2][jj - j2] == 0 && z[ii][jj] == 3) || (z[ii - i2][jj - j2] == 3 && z[ii][jj] == 2) || (z[ii - i2][jj - j2] == 2 && z[ii][jj] == 1) || (z[ii - i2][jj - j2] == 1 && z[ii][jj] == 0)) cl ++;
				if ((z[ii - i2][jj - j2] == 0 && z[ii][jj] == 1) || (z[ii - i2][jj - j2] == 1 && z[ii][jj] == 2) || (z[ii - i2][jj - j2] == 2 && z[ii][jj] == 3) || (z[ii - i2][jj - j2] == 3 && z[ii][jj] == 0)) ac ++;
				TT = tt;

				if (z1[ii][jj] == 1 && (ii != i || jj != j))
				{
					for (m = 0; m <= TT; m ++)
					{
						i0 = I[m];
						j0 = J[m];
						z1[i0][j0] = 0;
						I[m] = -1;
						J[m] = -1;
					};
					break;
				};
				if (z1[ii][jj] == 1 && ii == i && jj == j)
				{
					for (m = 0; m <= TT; m ++)
					{
						i0 = I[m];
						j0 = J[m];
						z1[i0][j0] = 0;
					};

					if (cl - ac > 0)
					{
						if (ddd == 0){
						ddd = 1;
						M ++;
						iii = i;
						jjj = j;
						int ss = 0;
						int cc = 0;
						n0 = 0;
						for (ttt = 1; ttt < T; ttt ++)
						{
						    //clockwise dynamics  rules
							z[iii][jjj] = a[z[iii][jjj]];
							int i3 = c[z[iii][jjj]];
							int j3 = b[z[iii][jjj]];
							iii += i3;
							jjj += j3;
							if (iii <= 0 || iii >= l - 1 || jjj <= 0 || jjj >= l - 1) {bb3 ++; break;};

							if (iii == l / 2 && jjj == l / 2) {cc = 1; n0 ++; tn0 ++;};

							if (i + c[z[i][j]] == I[TT - 1] && j + b[z[i][j]] == J[TT - 1]) ss = 1;
							if (iii == i && jjj == j && ss == 1) {TTT = ttt; break;};
						};
									for (m = 0; m <= TT; m++) {z2[I[m]][J[m]] = 21;};

								};

						if (ddd == 1){
						mm = 0;
						int km = 0;
						for (m = 0; m <= TT; m++)
						{
						    // check the nodes conditions
						if( z2[I[m] - 1][J[m]] == 21 && I[m] - 1 + c[z[I[m] - 1][J[m]]] == I[m] ) {km ++; break;};
						if( z2[I[m] + 1][J[m]] == 21 && I[m] + 1 + c[z[I[m] + 1][J[m]]] == I[m] ) {km ++; break;};
						if( z2[I[m]][J[m] - 1] == 21 && J[m] - 1 + b[z[I[m]][J[m] - 1]] == J[m] ) {km ++; break;};
						if( z2[I[m]][J[m] + 1] == 21 && J[m] + 1 + b[z[I[m]][J[m] + 1]] == J[m] ) {km ++; break;};
						};
						if(km > 1) mm = 1;

						iii = i;
						jjj = j;
						int ss = 0;
						int cc = 0;
						n0 = 0;
						for (ttt = 1; ttt < T; ttt ++)
						{
							z[iii][jjj] = a[z[iii][jjj]];
							int i3 = c[z[iii][jjj]];
							int j3 = b[z[iii][jjj]];
							iii += i3;
							jjj += j3;
							if (iii <= 0 || iii >= l - 1 || jjj <= 0 || jjj >= l - 1) {bb3 ++; break;};

							if (iii == l / 2 && jjj == l / 2) {cc = 1; n0 ++; tn0 ++; };

						if (mm == 0){

						for (m = 0; m <= TT; m ++) { if (iii != I[m] && jjj != J[m] && z2[iii][jjj] == 21) {mm = 1; break;};};};

							if (i + c[z[i][j]] == I[TT - 1] && j + b[z[i][j]] == J[TT - 1]) ss = 1;
							if (iii == i && jjj == j && ss == 1) {TTT += ttt; break;};
						};

								if (mm == 1){

						for (m = 0; m <= TT; m ++) {z2[I[m]][J[m]] = 21;};

				       	M ++;
				 		II[M] = i;
						JJ[M] = j;
                            //count of turns of spiral
						 if ( II[M - 1] - l /2 > 0 && II[M] - l /2 > 0 && JJ[M - 1] - l /2 >= 0 && JJ[M] - l /2 <  0 ) faz ++;
						 if ( II[M - 1] - l /2 > 0 && II[M] - l /2 > 0 && JJ[M - 1] - l /2 <  0 && JJ[M] - l /2 >= 0 ) faz --;

						if (cc == 1){Fn0[faz] += n0; Ftn0[faz] = tn0;

				      cout << n0 << "     " << tn0 << "     " << faz <<  endl;

                                    };

                                            };

									};

					};

    		for (m = 0; m <= TT; m ++){I[m] = -1; J[m] = -1;}; break;

				};

			};

		};
            //clockwise dynamics  rules
		z[i][j] = a[z[i][j]];
		j1 = b[z[i][j]];
		i1 = c[z[i][j]];
		i += i1;
		j += j1;
		if (i <= 0 || i >= l - 1 || j <= 0 || j >= l - 1) {bb1 ++; break;};

	};
                            // TTT + t -total number of chip steps
    cout << bb1 << "            " << TTT + t << "                    " << faz << endl;

//////////////////////////////////////////////////////////////////////////////
      // the trajectory of chip
		i00 = l / 2;
        j00 = l / 2;

		for (t0 = 1; t0 < TTT + t ; t0++)
	{
		z0[i00][j00] = a[z0[i00][j00]];
		int j01 = b[z0[i00][j00]];
		int i01 = c[z0[i00][j00]];
		i00 += i01;
		j00 += j01;
		if (i00 <= 0 || i00 >= l - 1 || j00 <= 0 || j00 >= l - 1) {bb1 ++; break;};

        Iall[t0] = i00;
        Jall[t0] = j00;
	};
/////////////////////////////////////////////////////////////////////////////
    file.open("i_all.dat");
	file << Iall;
	file.close();
	file.open("j_all.dat");
	file << Jall;
	file.close();
    file.open("i_node.dat");
	file << II;
	file.close();
	file.open("j_node.dat");
	file << JJ;
	file.close();

	return 0;
}
