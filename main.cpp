#include <iostream>
#include <zconf.h>
#include <pwd.h>
#include "h264parser.h"

using namespace std;

const char *homedir;

/**
 *
 *  1.  get home dir
 *  2.  input file url
 *  3.  output file url
 *  4.  define output file url
 *  5.  parse the argument
 *  6.  check if input file valid
 *  7.  check if output file valid
 *  8.  output custom head info
 *  9.  output h264 parser info【core】
 *  10. invoke shell cmd to open output file
 */
int main(int argc, char **argv) {
    //get home dir
    if ((homedir = getenv("HOME")) == nullptr) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    //define input file url
    char *url = nullptr;

    //define output file url
    FILE *out = nullptr;
    char *outputFile = nullptr;
    string outputFileName = "/h264_parse_result.txt";

    //parse the argument
    if (argc <= 1) {
        cout << "please input a file url" << endl;
        url = static_cast<char *>(malloc(2048));
        memset(url, 0, 2048);
        cin >> url;
        outputFile = static_cast<char *>(calloc(1, strlen(homedir) + outputFileName.length()));
        strcpy(outputFile, homedir);
        outputFile = strcat(outputFile, outputFileName.c_str());
        out = fopen(outputFile, "wb+");
    } else if (argc == 2) {
        url = *(argv + 1);
        outputFile = static_cast<char *>(calloc(1, strlen(homedir) + outputFileName.length()));
        strcpy(outputFile, homedir);
        outputFile = strcat(outputFile, outputFileName.c_str());
        out = fopen(outputFile, "wb+");
    } else if (argc == 3) {
        url = *(argv + 1);
        outputFile = *(argv + 2);
        out = fopen(outputFile, "wb+");
    } else {
        url = *(argv + 1);
        outputFile = *(argv + 2);
        out = fopen(outputFile, "wb+");
        cout << "ignore unrecognized argument start from" << *(argv + 3) << endl;
    }

    cout << "input url is: " << url << endl;

    //check if input file valid
    FILE *file = fopen(url, "r");
    if (!file) {
        cout << "input file not exist!" << endl;
        return 0;
    } else {
        fclose(file);
        file = nullptr;
    }

    //check if output file valid
    if (!out) {
        cout << "output file not valid" << endl;
        return 0;
    }

    //output custom head info
    auto start = std::chrono::system_clock::now();
    auto start_time = std::chrono::system_clock::to_time_t(start);
    char *timeString = std::ctime(&start_time);
    fprintf(out, "start time: %s\n", timeString);
    fprintf(out, "************************************************\n");
    fprintf(out, "\n");

    //output h264 parser info
    simplest_h264_parser(url, out);

    //invoke shell cmd to open output file
    if (outputFile) {
        char *cmd = static_cast<char *>(calloc(1, 2048));
        strcpy(cmd, "open ");
        strcat(cmd, outputFile);
        system(cmd);
        cout << "output file :" << outputFile << endl << "should be opened now" << endl;
    }


    return 0;
}