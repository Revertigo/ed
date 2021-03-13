//
// Created by dekel on 3/9/21.
//

#ifndef ED_DOCUMENT_HPP
#define ED_DOCUMENT_HPP

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Document {
    string _file;
    vector<string> _lines;

    bool _open; //Whether the document is open or not
    bool _write_mode; //True for writing mode, false for control mode
    bool _change_current; //True if we should edit the current line

    size_t _current_line;//Always between 1 and _lines.size inclusive

public:
    Document(): _open(true), _write_mode(false), _change_current(false), _current_line(0){}
    Document(const string file);

    bool document_open(void);
    bool write_mode(void);
    void write_new_line(const string & line);

    //ed supported operations
    string set_current_line(const int & line_number);                       //command=n (where n is line number)
    string move_lines(const int & howmany);                                 //command=+/-
    string set_last_line();                                                 //command=$
    void append_lines();                                                    //command=a
    void end_lines();                                                       //command=.
    void insert_lines();                                                    //command=i
    bool change_line();                                                     //command=c
    bool delete_line();                                                     //command=d
    string sed_search(const string & text);                                 //command=/text/
    string sed_replace(const string & old_text, const string & new_text);   //command=s/old/new
    bool join_lines();                                                      //command=j
    void write_file();                                                      //command=w
    void write_file(const string & file);                                   //command=w file
    void quit();                                                            //command=q
};


#endif //ED_DOCUMENT_HPP
