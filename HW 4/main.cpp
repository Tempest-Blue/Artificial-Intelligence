#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

double computeProb(double numY, vector<double> xValues, vector<double> probValues)
{
    double probYEqualsOne;
    double probProduct = 1;
    if (numY == 0)
    {
        for (int i = 0; i < 23; i++)
        {
            probYEqualsOne = pow((1 - probValues[i]),xValues[i]);
            probProduct *= probYEqualsOne;
        }
        return (1.0 - probProduct);
    }
    else
    {
        for (int i = numY * 23; i < ((numY + 1) * 23); i++)
        {
            probYEqualsOne = pow((1 - probValues[i%23]),xValues[i]);
            probProduct *= probYEqualsOne;
        }
        return (1.0 - probProduct);
    }
}

vector<double> compPi(vector<double> yValues, vector<double> xValues, vector<double> probValues)
{
    vector<double> newPi;
    for (int j = 0; j < 23; j++)
    {
        double tI = 0.0;
        double pI = 0.0;
        for (int i = 0; i < 267; i++)
        {
            if (xValues[(i*23) + j] == 1)
                ++tI;
            double denominator = 1.0;
            for (int k= 0; k < 23; k++)
            {
                denominator *= pow(1 - probValues[k], xValues[(i*23) + k]);
            }
            denominator = 1.0 - denominator;
            pI += (yValues[i] * xValues[(i*23) + j] * probValues[j]) / denominator;
        }
        newPi.push_back(pI * (1.0 / tI));
    }
    return newPi;
}

int main()
{
    ifstream infile;
    infile.open("x.txt");
    vector<double> xVector;
    while (infile)
    {
        double temp;
        infile >> temp;
        xVector.push_back(temp);
    }
    infile.close();
    infile.open("y.txt");
    vector<double> yVector;
    while (infile)
    {
        double temp;
        infile >> temp;
        yVector.push_back(temp);
    }
    vector<double> pI;
    for (int i = 0; i < 23; i++)
    {
        pI.push_back(2.0/23.0);
    }
    for (int j = 0; j < 257; j++)
    {
        vector<double> yVectorProb (267,0);
        int mistakes = 0;
        for (int i = 0; i < 267; i++)
        {
            double probYEqualsOne = computeProb(i, xVector, pI);
            if (yVector[i] == 1)
            {
                yVectorProb[i] = probYEqualsOne;
                if (probYEqualsOne <= .5)
                    ++mistakes;
            }
            else
            {
                yVectorProb[i] = 1.0 - probYEqualsOne;
                if (probYEqualsOne >= .5)
                    ++mistakes;
            }
        }
        double logValue = 0;
        for (int k = 0; k < 267; k++)
        {
            logValue += log(yVectorProb[k]);
        }
        logValue = logValue * (1.0/267.0);

        cout << "Iteration: " << j << " Mistakes: " << mistakes << " Log: " << logValue << endl;
        if (j == 256)
        {
            cout << endl;
            for (int l = 0; l < 23; l++)
            {
                cout << pI[l] << endl;
            }
        }
        pI = compPi(yVector, xVector, pI);
    }

    return 0;
}

