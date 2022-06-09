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

#define TEX_STATION_TITLEPAGE "./sources/station_title.tex"
#define TEX_STATION_BEGIN_TABLE "./sources/station_table.tex"
#define TEX_STATION_END_DOC "./sources/station_end.tex"

#define TEX_TEAM_START "./sources/team_start.tex"
#define TEX_TEAM_MID "./sources/team_mid.tex"
#define TEX_TEAM_END "./sources/team_end.tex"

#define TEX_ADMIN_START "./sources/admin_start.tex"

#define OUTPUT_FOLDER "./output/"
#define OUTPUT_SUFFIX ".tex"

bool write_from_file(std::ofstream &out, const char *filename);
void write_logs(std::ofstream &out, std::list<log_t> &logs);
void init_logs(std::list<log_t> &logs, int count);
int generate_example();
int generate_all();
int generate_station(doc_t &document, const std::string filename);
int generate_team(team_logs_t &logs, const std::string team_name);
int generate_admin(team_logs_t logs[], std::string teams[]);


int main()
{
    // init rand()
    srand(time(NULL)); // rand() seed

    return generate_all();
}

int generate_all()
{
    camp_locations_t camps;
    camps.locations[0].add_coords('A',0);
    camps.locations[1].add_coords('B',1);
    camps.locations[2].add_coords('C',2);
    camps.locations[3].add_coords('D',3);
    camps.locations[CAMP_COUNT - 1].add_coords('E',4);

    std::string team_names[TEAM_COUNT];
    team_names[0] = "Alfa";
    team_names[1] = "Beta";
    team_names[2] = "Gama";
    team_names[3] = "Delta";
    team_names[4] = "Epsilon";
    team_names[5] = "Lambda";
    team_names[6] = "Omikron";
    team_names[TEAM_COUNT - 1] = "Sigma";



    doc_t stations[STATION_COUNT];
    team_logs_t team_logs[TEAM_COUNT];

    for (uint8_t i = 0; i < STATION_COUNT; i++)
    {
        stations[i].init_random();
    }


    for (uint8_t i = 0; i < TEAM_COUNT; i++)
    {
        team_logs[i].add_locations(camps);
        team_logs[i].distrubute_logs(stations);
    }

    for (uint8_t i = 0; i < STATION_COUNT; i++)
    {   
        if (generate_station(stations[i], "station" + std::to_string(i)) != 0)
            return 1;
    }
    

    for (uint8_t i = 0; i < TEAM_COUNT; i++)
    {
        if (generate_team(team_logs[i], team_names[i]) != 0)
            return 1;
    }

    if (generate_admin(team_logs, team_names) != 0)
        return 1;

    return 0;
}

int generate_admin(team_logs_t logs[], std::string teams[])
{
    //output file
    std::ofstream out("./output/admin.tex", std::ios::out);
    if (!out.is_open())
    {
        std::cerr << "ERR: failed to open file (admin)\n";
        return 1;
    }

    // write begining
    if (!write_from_file(out, TEX_ADMIN_START))
    {
        out.close();
        return 1;
    }

    //table content
    //for each team
    for (uint8_t team_num = 0; team_num < TEAM_COUNT; team_num++)
    {
        //begin table
        out << "\t\t\\begin{table}[H]\n"
            << "\t\t\\ttfamily\n"
		    << "\t\t\\catcode`\\-=12\n"
            << "\t\t\\begin{tabularx}{\\textwidth}{c|c|l|s|s|s|s|s|S|}\n"
            << "\t\t\t\\multicolumn{9}{c}{\\bfseries\\Large " << teams[team_num] << "} \\\\ [0.3em]\n"
            << "\t\t\t\\textbf{Datum} & \\textbf{Čas} & \\textbf{Záznam signálu} & \\multicolumn{5}{l|}{\\bfseries Fake lokace} & \\textbf{\\large \\checkmark}\\\\ \\toprule[0.4mm]\n\n";

        //for each log (camp count)
        for (uint8_t camp_num = 0; camp_num < CAMP_COUNT; camp_num++)
        {
            std::string line[3];

            line[0] = "\\multirow[c]{3}{*}{" + logs[team_num].logs[camp_num].date.to_string() + "} & \\multirow[c]{3}{*}{" + logs[team_num].logs[camp_num].time.to_string() + "} & \\multirow[c]{3}{*}{" + logs[team_num].logs[camp_num].curve.to_latex() + "} & ";
            line[1] = "&&&";
            line[2] = "&&&";

            //for each line (3 fake logs)
            for (uint8_t line_num = 0; line_num < 3; line_num++)
            {
                uint8_t tmp_loc_cnt = 0;

                //fill table with fake locations
                while (tmp_loc_cnt < logs[team_num].false_locations[camp_num][line_num].size)
                {
                    line[line_num] += logs[team_num].false_locations[camp_num][line_num].locations[tmp_loc_cnt].to_string() + " & ";
                    tmp_loc_cnt++;
                }

                //fill to end
                while (tmp_loc_cnt < LOCATION_MAX_COUNT - 1)
                {
                    line[line_num] += " & ";
                    tmp_loc_cnt++;
                }
            }
            
            line[0] += logs[team_num].logs[camp_num].locations.to_string();

            line[0] += "\\\\ \\cline{4-8}";
            line[1] += "\\\\ \\cline{4-8}";
            line[2] += "\\\\ \\toprule[0.3mm]";

            out << "\t\t\t" << line[0] << "\n"
                << "\t\t\t" << line[1] << "\n"
                << "\t\t\t" << line[2] << "\n";
        }

        out << "\t\t\\end{tabularx}\n"
            << "\t\t\\end{table}\n\n";

    }

    //end doc
    out << "\\end{document}\n";

    out.close();
    return 0;
}

int generate_team(team_logs_t &logs, const std::string team_name)
{
    //output file
    std::ofstream out(OUTPUT_FOLDER + team_name + OUTPUT_SUFFIX, std::ios::out);  
    if (!out.is_open())
    {
        std::cerr << "ERR: failed to open file (" << team_name << ")\n";
        return 1;
    }

    // write begining
    if (!write_from_file(out, TEX_TEAM_START))
    {
        out.close();
        return 1;
    }

    out << team_name;

    // write table begin
    if (!write_from_file(out, TEX_TEAM_MID))
    {
        out.close();
        return 1;
    }

    //table content
    for (uint8_t log = 0; log < CAMP_COUNT; log++)
    {
        out << "\t\t\t&& \\multirow[c]{3}{*}{" << logs.logs[log].curve.to_latex() << "} &&&&&&& \\\\ \\cline{4-9}\n"
            << "\t\t\t&&&&&&&&& \\\\ \\cline{4-9}\n"
            << "\t\t\t&&&&&&&&& \\\\ \\toprule[0.3mm]\n";
    }

    // write end of table
    if (!write_from_file(out, TEX_TEAM_END))
    {
        out.close();
        return 1;
    }

    out.close();
    return 0;
}


int generate_station(doc_t &document, const std::string filename)
{
    //output file
    std::ofstream out(OUTPUT_FOLDER + filename + OUTPUT_SUFFIX, std::ios::out);
    if (!out.is_open())
    {
        std::cerr << "ERR: failed to open file (" << filename << ")\n";
        return 1;
    }

    // write titlepage
    if (!write_from_file(out, TEX_STATION_TITLEPAGE))
    {
        out.close();
        return 1;
    }

    out << document.id;

    // write begining of table
    if (!write_from_file(out, TEX_STATION_BEGIN_TABLE))
    {
        out.close();
        return 1;
    }
    
    //table content
    write_logs(out, document.log_list);

    // write end of table
    if (!write_from_file(out, TEX_STATION_END_DOC))
    {
        out.close();
        return 1;
    }

    out.close();
    return 0;
}

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
