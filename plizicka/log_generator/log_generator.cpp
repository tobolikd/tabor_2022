#include <stdlib.h>
#include <string>    // for std::string
#include <stdbool.h> // for bool
#include <algorithm> // for std::copy
#include <fstream>   // for std::filebuf
#include <iterator>  // for std::{i,o}streambuf_iterator
#include <iostream>
#include <fstream>
#include <time.h>
#include <list>

#include "log_generator.h"

#define OUT_FILENAME "./output/example.tex"
#define TEX_TITLEPAGE "./sources/point_title.tex"
#define TEX_BEGIN_TABLE "./sources/point_table.tex"
#define TEX_END_DOC "./sources/point_end.tex"

bool write_from_file(std::ofstream &out, const char *filename);
void write_logs(std::ofstream &out, std::list<log_t> &logs);
void init_logs(std::list<log_t> &logs, int count);
int generate_example();
int generate_all();
int generate_station(doc_t &station);
int generate_team(team_logs_t &logs);

#define ONLY_EXAMPLE true

int main()
{
#if ONLY_EXAMPLE
        return generate_example();
#else
        return generate_all();
#endif //ONLY_EXAMPLE
}

int generate_all()
{
    //TODO
    return 0;
}

int generate_station(doc_t &station)
{
    return 0;
}

int generate_team(team_logs_t &logs)
{
    return 0;
}

#if ONLY_EXAMPLE
int generate_example()
{
    //output file
    std::ofstream out(OUT_FILENAME, std::ios::out);
    if (!out.is_open())
    {
        std::cerr << "ERR: failed to open file (" << OUT_FILENAME << ")\n";
        return 1;
    }

    // init rand()
    srand(time(NULL)); // rand() seed

    // local vars
    doc_t document;

    // init
    document.init_random();

    // write titlepage
    if (!write_from_file(out, TEX_TITLEPAGE))
    {
        out.close();
        return 1;
    }

    out << document.id;

    // write begining of table
    if (!write_from_file(out, TEX_BEGIN_TABLE))
    {
        out.close();
        return 1;
    }
    // ↓↓↓table content↓↓↓

    write_logs(out, document.log_list);

    // write end of table
    if (!write_from_file(out, TEX_END_DOC))
    {
        out.close();
        return 1;
    }

    out.close();
    return 0;
}
#endif //ONLY_EXAMPLE

bool write_from_file(std::ofstream &out, const char *filename)
{
    std::ofstream tmp(filename, std::ios::in);

    if (!tmp.is_open())
    {
        std::cerr << "ERR: failed to open file (" << filename << ")\n";
        return false;
    }

    out << tmp.rdbuf();

    tmp.close();
    return true;
}

void write_logs(std::ofstream &out, std::list<log_t> &logs)
{
    logs.sort();

    for (std::list<log_t>::iterator item = logs.begin(); item != logs.end(); item++)
    {
        out << item->date.to_string()
            << " & "
            << item->time.to_string()
            << " & "
            << item->curve.to_latex()

            << " & "
            << item->locations.to_string()
            << " \\\\"
            << (std::next(item) == logs.end() ? "\\bottomrule\n\n" : "\\midrule\n\n");
    }
}
