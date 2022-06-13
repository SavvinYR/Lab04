#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <winsock2.h>
#include <windows.h>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
using namespace std;

vector<double> input_numbers(istream& in, size_t count)   //функция ввода чисел
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
        in >> result[i];
    return result;
}

Input read_input(istream& in,bool prompt)
{
    Input data;
    size_t number_count;
    if(prompt)
        cerr << "Enter number count: ";
    in >> number_count;
    if(prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);
    if(prompt)
    {
        cerr<<"bin count:";
    }
    in>>data.bin_count;
    data.number_count = number_count;

    return data;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

Input
download(const string& address)
{
    stringstream buffer;
    CURL* curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res!=CURLE_OK)
        {
            cerr<<curl_easy_strerror(res);
            exit(1);
        }
        curl_easy_cleanup(curl);

    }
    // std::cout << __FUNCTION__ << "():" << __LINE__ << std::endl;
    return read_input(buffer, false);

}


int
main(int argc, char* argv[])
{

    Input input;



    if (argc > 1)
    {

        size_t generator = 0;
        int URL_position = 0;
        bool generate_found = false;
        string option = "-generate";
        char* URL = "http://";
        for (int i=0; i<argc; i++)
        {
            string t = argv[i];
            if (option==t)
            {
                generator =atoi (argv[i+1]);
                generate_found = true;
            }
            if (strstr(argv[i],URL) !=NULL)
                URL_position = i;
        }
        if (URL_position == 0)
        {
            cout << "Incorrect input. URL not founded.";
            return 0;
        }
        input = download(argv[URL_position]);
        if (generate_found)
            if (generator>0)
            {
                vector <double> num;
                double value;
                input.number_count = generator;
                for(int j=0; j<generator; j++)
                {
                    value = rand() % input.bin_count +3;
                    input.numbers.push_back(value);
                }
            }
            else
            {
                cout << "Incorrect input. Example: Lab04.exe -generate 10 http://... or Lab04.exe http://... -generate 10.";
                return 0;
            }
    }
    else
    {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input);
    show_histogram_svg( bins);
    return 0 ;
}
