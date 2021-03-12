//
// Created by dekel on 3/9/21.
//

#include <iostream>
#include "Editor.hpp"

using namespace std;

inline bool Editor::is_integer(const string & s)
{
    if(s.empty() || ((!isdigit(s[0])))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

void Editor::loop(void)
{
    //Main loop
    string line;
    char user_input;

    while(_document.document_open()) {
        getline(cin, line);

        //If write mode enabled
        while(_document.write_mode() && line != ".") {
            _document.write_new_line(line);
            getline(cin, line);
        }

        if(is_integer(line))
        {
            string current_line = _document.set_current_line(stoi(line));
            cout << current_line << endl;
            continue;
        }

        //If write mode is enabled
        while(_document.write_mode() && line != "."){
            _document.write_new_line(line);
            getline(cin, line);
        }

        user_input = line[0]; //Get the first character
        switch (user_input) {
            case '+':
            case '-': {
                if(is_integer(line.substr(1))) {
                    string current_line = _document.move_lines(stoi(line));
                    cout << current_line << endl;
                    //Break only in case of success, otherwise go to default
                    break;
                }
                goto default_case;
            }

            case '$': {
                string current_line = _document.set_last_line();
                cout << current_line << endl;
                break;
            }

            case 'a': {
                _document.append_lines();
                break;
            }

            case '.': {
                _document.end_lines();
                break;
            }

            case '$': {
                string current_line = _document.set_last_line();
                cout << current_line << endl;
                break;
            }

            case 'i': {
                _document.insert_lines();
                break;
            }

            case 'w': {
                if ((_empty_ctor && line.size() == 1) ||
                //Second char should be space
                if((line.size() > 2 && line[1] == ' ')) {
                    //Position 2 is the file name
                    string file = line.substr(2);
                    _document.write_file(file);
                    break;
                }
                else if(!_empty_ctor){
                    //If ctor wasn't empty, file name is already known
                    _document.write_file();
                    break;
                }

                goto default_case;
            }

            case 'q': {
                _document.quit();
                break;
            }
default_case:
            default: {
                cout << _undefined_operation << endl;
                break;
            }
        }
    }
}