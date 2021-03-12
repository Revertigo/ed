//
// Created by dekel on 3/9/21.
//
#include <sstream>
#include "Document.hpp"
using namespace std;

Document::Document(string file): Document()
{
    _file = file;
    ifstream is(_file);

    if(!is){
        cout << "File doesn't exists." << endl;
        return;
    }

    std::string line;
    while (std::getline(is, line))
    {
        _lines.push_back(line);
    }
    set_last_line();
    //This function called automatically on ifstream dtor (when going out of scope)
    is.close();
}

bool Document::document_open(void)
{
    return _open;
}

bool Document::write_mode(void)
{
    return _write_mode;
}

void Document::write_new_line(string line)
{
    _lines.insert(_lines.begin() + _current_line++, line);
}
string Document::set_current_line(int line_number)
{
    string result = "?";
    if(line_number > 0 && line_number <= _lines.size()) {
        _current_line = line_number;
        result = _lines[_current_line - 1];//return the actual line
    }

    return result;
}
void Document::move_lines(int howmany)
{
    _current_line += howmany;
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
    if(_current_line > 0)
    {
        _current_line--;
    }
    //Finally, append the file
    append_lines();
}
void Document::change_line(){}
void Document::delete_line(){}
void Document::sed_search(string text){}
void Document::sed_replace(string old_text, string new_text){}
void Document::join_lines(){}
void Document::write_file()
{
    //In this case, the file name is already known, so we just call write_file(string)
    write_file(_file);
}
void Document::write_file(string file)
{
    std::ofstream output_file(file);
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(_lines.begin(), _lines.end(), output_iterator);
}
void Document::quit()
{
    _open = false;
}
