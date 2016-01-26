// Kieth Vo
// A09632897
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int main()
{
    ifstream infile;
    infile.open("prob_a1.txt");
    double** a1Matrix = new double*[187];
    for (int i = 0; i < 187; i++)
    {
        a1Matrix[i] = new double[3];
    }
    for (int i = 0; i < 187; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double temp;
            infile >> temp;
            a1Matrix[i][j] = temp;
        }
    }
    infile.close();

    infile.open("prob_a2.txt");
    double** a2Matrix = new double*[187];
    for (int i = 0; i < 187; i++)
    {
        a2Matrix[i] = new double[3];
    }
    for (int i = 0; i < 187; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double temp;
            infile >> temp;
            a2Matrix[i][j] = temp;
        }
    }
    infile.close();

    infile.open("prob_a3.txt");
    double** a3Matrix = new double*[187];
    for (int i = 0; i < 187; i++)
    {
        a3Matrix[i] = new double[3];
    }
    for (int i = 0; i < 187; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double temp;
            infile >> temp;
            a3Matrix[i][j] = temp;
        }
    }
    infile.close();

    infile.open("prob_a4.txt");
    double** a4Matrix = new double*[187];
    for (int i = 0; i < 187; i++)
    {
        a4Matrix[i] = new double[3];
    }
    for (int i = 0; i < 187; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double temp;
            infile >> temp;
            a4Matrix[i][j] = temp;
        }
    }
    infile.close();

    infile.open("rewards.txt");
    double* rewardsMatrix = new double[81];
    for (int i = 0; i < 81; i++)
    {
        double temp;
        infile >> temp;
        rewardsMatrix[i] = temp;
    }
    infile.close();

    double discountFactor = .99;
    double** vStarMatrix = new double*[81];
    for (int i = 0; i < 81; i++)
    {
        vStarMatrix[i] = new double[1000];
    }
    for (int i = 0; i < 81; i++)
    {
        vStarMatrix[i][0] = 0;
    }
    double** piStarMatrix = new double*[81];
    for (int i = 0; i < 81; i++)
    {
        piStarMatrix[i] = new double[1000];
    }
    for (int j = 0; j < 1000; j++)
    {
        for (int k = 0; k < 81; k++)
        {
            double a1Sum = 0;
            double a2Sum = 0;
            double a3Sum = 0;
            double a4Sum = 0;
            for (int i = 0; i < 187; i++)
            {
                int temp = a1Matrix [i][1];
                if (a1Matrix[i][0] == k)
                {
                    a1Sum += a1Matrix[i][2] * vStarMatrix[temp][j];
                }
                if (a2Matrix[i][0] == k)
                {
                    a2Sum += a2Matrix[i][2] * vStarMatrix[temp][j];
                }
                if (a3Matrix[i][0] == k)
                {
                    a3Sum += a3Matrix[i][2] * vStarMatrix[temp][j];
                }
                if (a4Matrix[i][0] == k)
                {
                    a4Sum += a4Matrix[i][2] * vStarMatrix[temp][j];
                }
            }
            double maxAction = max(a1Sum, a2Sum);
            maxAction = max(a3Sum, maxAction);
            maxAction = max(a4Sum, maxAction);
            if (a1Sum == maxAction)
            piStarMatrix[k][j+1] = 1;
            if (a2Sum == maxAction)
            piStarMatrix[k][j+1] = 2;
            if (a3Sum == maxAction)
            piStarMatrix[k][j+1] = 3;
            if (a4Sum == maxAction)
            piStarMatrix[k][j+1] = 4;
            vStarMatrix[k][j+1] = rewardsMatrix[k] + (pow(discountFactor, j) * maxAction);
        }
    }
    return 0;
}
