#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "histogram.h"
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    {

    } min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }
        else if (max < number)
        {
            max = number;
        }

    }
    return;
}

vector <size_t> make_histogram(const Input& input)
{
    vector <size_t> bins (input.bin_count, 0);
    double min ;
    double max ;
    find_minmax(input.numbers, min, max);

    double bin_size = (max - min) / input.bin_count;
    for (size_t i = 0; i < input.number_count; i++)
    {
        bool found = false;
        for(size_t j = 0; j < (input.bin_count-1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j+1) * bin_size;
            if ((lo <= input.numbers[i])&& (input.numbers[i] < hi) )
            {
                bins[j]++;
                found = true;
            }
        }
        if(!found)
            bins[input.bin_count-1]++;
    }
    return bins;
}

void show_histogram_text(vector<size_t> binss)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    size_t max_bin = binss[0];
    for(size_t bin : binss)
    {
        if(bin > max_bin)
        {
            max_bin = bin;
        }
    }


    for (size_t bin : binss)
    {
        size_t height = bin;
        if(max_bin > MAX_ASTERISK)   //Если масштабирование необходимо
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }
      size_t  proverka = max_bin;

        for(size_t i = 0; i < height; i++)
        {
            while ( proverka > height)
            {
                cout << " ";
                proverka = proverka - 1;
            }
            cout << '*';
        }
        ;
        cout << "|" ;

        if(bin < 100)
        {
            cout << " ";
        }
        if(bin < 10)
        {
            cout << " ";
        }
        cout <<bin;


        cout << endl;
    }


    return ;
}
