// Kieth Vo
// A09632897
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

char returnChar(int x)
{
    return (char)(x + 65);
}

int main()
{
    ifstream infile;
    ofstream outfile;
    infile.open("emissionMatrix.txt");
    double** emissionMatrix = new double*[26];
    for (int i = 0; i < 26; i++)
    {
        emissionMatrix[i] = new double[2];
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            double temp;
            infile >> temp;
            emissionMatrix[i][j] = temp;
        }
    }
    infile.close();
    infile.open("transitionMatrix.txt");
    double** transitionMatrix = new double*[26];
    for (int i = 0; i < 26; i++)
    {
        transitionMatrix[i] = new double[26];
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            double temp;
            infile >> temp;
            transitionMatrix[i][j] = temp;
        }
    }
    infile.close();
    infile.open("observations.txt");
    vector<int> observations;
    while(infile)
    {
        int temp;
        infile >> temp;
        observations.push_back(temp);
    }
    infile.close();
    infile.open("initialStateDistribution.txt");
    double** lStarMatrix = new double*[26];
    for (int i = 0; i < 26; i++)
    {
        lStarMatrix[i] = new double[45000];
    }
    double** phiMatrix = new double*[26];
    for (int i = 0; i < 26; i++)
    {
        phiMatrix[i] = new double[45000];
    }
    for (int i = 0; i < 26; i++)
    {
        double temp;
        infile >> temp;
        int o1 = observations[0];
        lStarMatrix[i][0] = log(temp) + log(emissionMatrix[i][o1]);
        phiMatrix[i][0] = 0;
    }
    infile.close();
    for (int k = 1; k < 45000; k++)
    {
        for (int i = 0; i < 26; i++)
        {
            double maxVal = lStarMatrix[0][k-1] + log(transitionMatrix[0][i]);
            int indexHolder = 0;
            for (int j = 0; j < 26; j++)
            {
                if (lStarMatrix[j][k-1] + log(transitionMatrix[j][i]) > maxVal)
                {
                    maxVal = lStarMatrix[j][k-1] + log(transitionMatrix[j][i]);
                    indexHolder = j;
                }
            }
            int temp = observations[k];
            maxVal += log(emissionMatrix[i][temp]);
            lStarMatrix[i][k] = maxVal;
            phiMatrix[i][k] = indexHolder;
        }
    }
    double sStarT = lStarMatrix[0][44999];
    int phiT = 0;
    for (int i = 0; i < 26; i++)
    {
        if (lStarMatrix[i][44999] > sStarT)
        {
            sStarT = lStarMatrix[i][44999];
            phiT = i;
        }
    }
    vector<int> sStar;
    sStar.push_back(phiT);
    for (int i = 44998; i > 0; i--)
    {
        sStar.push_back(phiMatrix[phiT][i]);
        phiT = phiMatrix[phiT][i];
    }
    outfile.open("result.txt");
    for (int i = 1; i < 44999; i++)
    {
        outfile << sStar[i] << endl;
    }
    vector<int> sStarSimplified;
    int letter = sStar[0];
    sStarSimplified.push_back(letter);
    for (int i = 1; i < sStar.size(); i++)
    {
        if (sStar[i] != letter)
        {
            sStarSimplified.push_back(sStar[i]);
            letter = sStar[i];
        }
    }
    for (int i = sStarSimplified.size() - 1; i >= 0; i--)
    {
        cout << returnChar(sStarSimplified[i]);
    }
    delete lStarMatrix, phiMatrix, emissionMatrix, transitionMatrix;
    return 0;
}
