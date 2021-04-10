//
// Created by dekel on 3/9/21.
//
#include <fstream>
#include <iterator>
#include <regex>
#include "Document.hpp"

using namespace std;

Document::Document(const string file): Document()
{
    _file = file;
    ifstream is(_file);

    if(!is){
        cout << _file << ": No such file or directory" << endl;
        return;
    }

    //Copy the file's content into a vector
    string line;
    while (getline(is, line)){
        _lines.push_back(line);
    }

    set_last_line();
    //is.close() function called automatically on ifstream dtor (when going out of scope)
}

bool Document::document_open(void)
{
    return _open;
}

bool Document::write_mode(void)
{
    return _write_mode;
}

void Document::write_new_line(const string & line)
{
    _lines.insert(_lines.begin() + _current_line++, line);
}

string Document::set_current_line(const int & line_number)
{
    string result = "?";
    if(line_number > 0 && line_number <= _lines.size()) {
        _current_line = line_number;
        result = _lines[_current_line - 1];//return the actual line
    }

    return result;
}

string Document::move_lines(const int & howmany)
{
    return set_current_line(_current_line + howmany);
}

string Document::set_last_line()
{
    return set_current_line(_lines.size());
}

void Document::append_lines()
{
    _write_mode = true;
}

void Document::end_lines()
{
    _write_mode = false;
}

void Document::insert_lines()
{
    if(_current_line > 0){
        _current_line--;
    }
    //Finally, append the file
    append_lines();
}

bool Document::change_line()
{
    bool result = false;

    size_t old_current = _current_line;
    if(delete_line()){
        //means current line now points to the last line at the file
        if(_current_line != old_current){
            append_lines();
        }
        else{
            insert_lines();
        }
        
        result = true;
    }

    return result;
}

bool Document::delete_line()
{
    bool result = false;
    if(_current_line > 0) {
        //It's OK to erase strings event if the index is bigger then array size
        _lines.erase(_lines.begin() + _current_line - 1);
        //In case current line exceeds the array size
        _current_line = min(_current_line, _lines.size());
        result = true;
    }

    return result;
}

string Document::sed_search(const string & text)
{
    size_t line_number = 0;
    //Search every substring of text in the line
    regex pattern("(.*)" + text + "(.*)"); 

    //First, search from current line till the end
    for (auto it = begin (_lines) + _current_line; it != end (_lines); ++it) {
        if(regex_match(*it, pattern)){
            line_number = it - _lines.begin() + 1;
            break;
        }
    }

    if(line_number == 0){
        //Secondly, search from beginning till current line
        for (auto it = begin (_lines); it != begin (_lines) + _current_line; ++it) {
            if(regex_match(*it, pattern)){
                //plus 1 since we need to translate it to user lines
                line_number = it - _lines.begin() + 1;
                break;
            }
        }
    }

    return set_current_line(line_number);
}

string Document::sed_replace(const string & old_text, const string & new_text)
{
    string result = "?";
    regex pattern(old_text);
    //Temp uses as placeholder in order to later overwrite the new value
    string temp = regex_replace(_lines[_current_line - 1], pattern, new_text, 
                                regex_constants::format_first_only);
    result = (temp == _lines[_current_line - 1]) ? result : temp;
    _lines[_current_line - 1] = temp; //regex doesn't overwrite the input line

    return result;
}

bool Document::join_lines()
{
    bool joined = false;
    if((_current_line -1) < _lines.size() - 1){
        _lines[_current_line-1] += _lines[_current_line];
        _lines.erase(_lines.begin() + _current_line);
        joined = true;
    }

    return joined;
}

void Document::write_file()
{
    //In this case, the file name is already known, so we just call write_file(string)
    write_file(_file);
}

void Document::write_file(const string & file)
{
    ofstream output_file(file);
    ostream_iterator<string> output_iterator(output_file, "\n");
    //Copy the vector into the file's iterator and flushing it in the end. close called automatically
    copy(_lines.begin(), _lines.end(), output_iterator);
}

void Document::quit()
{
    _open = false;
}