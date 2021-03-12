//
// Created by dekel on 3/9/21.
//

#ifndef ED_DOCUMENT_HPP
#define ED_DOCUMENT_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

class Document {
    string _file;
    vector<string> _lines;
    bool _write_mode; //True for writing mode, false for control mode
    bool _open; //True if we should edit the current line

    size_t _current_line;

public:
    Document():_write_mode(false), _current_line(0), _open(true){}
    Document(string file);

    bool document_open(void);
    bool write_mode(void);
    void write_new_line(string line);

    //ed supported operations
    string set_current_line(const int line_number);                            //command=n (where n is line number)
    string move_lines(const int howmany);                       //command=+/-
    string set_last_line();                               //command=$
    void append_lines();                                //command=a
    void end_lines();                                   //command=.
    void insert_lines();                                //command=i
    void change_line();                                 //command=c
    void delete_line();                                 //command=d
    void sed_search(string text);                       //command=/text/
    void sed_replace(string old_text, string new_text); //command=s/old/new
    void join_lines();                                  //command=j
    void write_file();                                  //command=w
    void write_file(const string file);                       //command=w file
    void quit();                                        //command=q
};


#endif //ED_DOCUMENT_HPP
