#include "svg.h"
#include <iostream>
#include <sstream>
#include <string>
#include <winsock.h>
#include <windows.h>

    void
    svg_begin(double width, double height)
    {
        cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
        cout << "<svg ";
        cout << "width='" << width << "' ";
        cout << "height='" << height << "' ";
        cout << "viewBox='0 0 " << width << " " << height << "' ";
        cout << "xmlns='http://www.w3.org/2000/svg'>\n";
    }

    void
    svg_end()
    {
        cout << "</svg>\n";
    }
    void svg_text(double left, double baseline, string text)
    {
        cout << "<text x='" << left << "' y='" <<baseline << "'>"<< text << "</text>";
    }

 void svg_rect(double x, double y, double width, double height,string stroke, string fill)
    {
        cout<< "<rect x='" << x << "' y='"<<y<<"' " "width='" <<width<< "' " "height='" <<height << "' " "stroke='" << stroke << "' " "fill='" << fill << "' />";
    }
string make_info_text() {
    stringstream buffer;
    const auto R =GetVersion();
   printf("n = %lu\n", R);
printf("n = %lx\n", R);
DWORD mask = 0b00000000'00000000'11111111'11111111;
DWORD version =R&mask;
printf("ver = %lu\n",version);
DWORD platform = R >> 16;
printf("ver2 = %lu\n",platform);
DWORD mask2=0b00000000'11111111;
DWORD version_major=version&mask2;
printf("version_major = %lu\n",version_major);
DWORD version_minor=version>>8;
printf("version_minor = %lu\n",version_minor);
DWORD build;
if ((R & 0x80000000) == 0)
{
   build =platform;
   printf("build = %lu\n",build);

}
buffer<<"Windows"<< " " <<"v"<< " " <<version_major<<"."<<version_minor<< " "<< "(build"<< " "<<build<<")"<<endl;
TCHAR storage [ MAX_COMPUTERNAME_LENGTH + 1];
DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH+1;
GetComputerNameA(storage,&bufCharCount);
buffer<<"Computer name:"<<" "<<storage;
    return buffer.str();
}
    void show_histogram_svg(const vector<size_t>& bins)
    {

        const auto IMAGE_WIDTH = 400;
        const auto IMAGE_HEIGHT = 300;
        const auto TEXT_LEFT = 20;
        const auto TEXT_BASELINE = 20;
        const auto TEXT_WIDTH = 50;
        const auto BIN_HEIGHT = 30;
        const auto BLOCK_WIDTH = 10;
         size_t max_bin_width=1;
        const size_t MAX_ASTERISK=IMAGE_WIDTH-TEXT_WIDTH;//345//-wid,т.к нужно учесть ещё ширину рамки по X

        size_t max_count = 0;
        for (size_t count : bins)
        {
            if (count > max_count)
            {
                max_count = count;
            }

        }
        max_bin_width=max_count*BLOCK_WIDTH;
        double top = 5;

        const bool scaling_needed= max_bin_width>MAX_ASTERISK;
        svg_begin(IMAGE_WIDTH,IMAGE_HEIGHT);

        for (size_t bin : bins)
        {

            size_t bin_width=bin*BLOCK_WIDTH;
            if(scaling_needed)
            {
                const double scalling_factor=(double)MAX_ASTERISK/( max_bin_width);
                bin_width=(size_t)(bin*scalling_factor*BLOCK_WIDTH-3);
            }

            svg_text(IMAGE_WIDTH - TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));;
            svg_rect(IMAGE_WIDTH - bin_width - TEXT_WIDTH , top,bin_width, BIN_HEIGHT, "#CD5C5C", "#CD5C5C");
            top += BIN_HEIGHT;
        }
        svg_text(TEXT_LEFT, top += BIN_HEIGHT, make_info_text());
        svg_end();

    }







