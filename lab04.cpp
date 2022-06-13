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

vector<double> input_numbers(size_t count);
vector<double> input_numbers(istream& in, size_t count) { //функция ввода чисел
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

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;
    CURL* curl = curl_easy_init();
    if(curl){
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res!=CURLE_OK){
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

if (argc > 2)
   {
       size_t generator;
       Input input2;
    string option = "-generate";
      for (int i=0; i<argc; i++)
      {
        string t = argv[i];
         if (option==t)
            generator =atoi (argv[i+1]);
      }
      vector <double> num;
      //double[] nums = new double[generator];
      //delete [] nums;
      for(int j=0; j<generator; j++)
      {
        //num[j] = j;
        double value;
        value = rand() % 3 +3;
      //  cout << value << "\n";
        input2.numbers.push_back(value);
      }
      input2.bin_count = 3;
      input2.number_count = generator;
      cout << input2.number_count << "\n" ;
      cout << input2.bin_count << "\n";
      for(int i =0; i < generator; i++)
      { cout << input2.numbers[i] << " ";

      }
 return 0;



}

    if (argc > 1)
    {

        input = download(argv[1]);

    }
    else{

        input = read_input(cin, true);
    }

    //for (int i = 0; i < input.numbers.size(); i++) {
    //    std::cout << "Data " << i << " " << input.numbers[i] << std::endl;
    //}
    //std::cout << "bin_count " << input.bin_count << std::endl;
    //std::cout << "number_count " << input.number_count << std::endl;
    //input.number_count=10;

    //std::cout << __FUNCTION__ << "():" << __LINE__ << std::endl;

    //std::cout << __FUNCTION__ << "():" << __LINE__ << std::endl;
    const auto bins = make_histogram(input);
    //std::cout << __FUNCTION__ << "():" << __LINE__ << std::endl;
    show_histogram_svg( bins);
    //std::cout << __FUNCTION__ << "():" << __LINE__ << std::endl;
    return 0 ;
}
