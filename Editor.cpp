//
// Created by dekel on 3/9/21.
//
#include <iostream>
#include <sstream>
#include <regex>
#include "Editor.hpp"

using namespace std;

void Editor::loop(void)
{
    //Main loop
    string line;

    //Regex patterns
    regex number("\\d+"); //At least one digit(\\d = [0-9])
    regex sign_number("(\\+|-)\\d+");
    regex search_pattern("/([^/]+)/?"); //slash, then anything that isn't slash (at least once) then 0 or one slash
    regex replace_pattern("s/([^/]*)/([^/]*)/?");
    regex single_char("(\\$|a|\\.|i|c|d|j|w|q)");
    regex write_new_file("w [\\w,-]+(\\.[A-Za-z]+)?");

    while(_document.document_open()) {
        getline(cin, line);

        //If write mode is enabled
        while(_document.write_mode() && line != "."){
            _document.write_new_line(line);
            getline(cin, line);
        }

        if(regex_match(line, number)){
             try{
                string current_line = _document.set_current_line(stoi(line));
                cout << current_line << endl;
            }catch(const out_of_range& e){
                goto default_operation;
            }
        }
        else if(regex_match(line, sign_number)){
            try{
                string current_line = _document.move_lines(stoi(line));
                cout << current_line << endl;
            }catch(const out_of_range& e){
                goto default_operation;
            }
        }
        else if(regex_match(line, search_pattern)){
            string to_search;
            stringstream ss(line.substr(1));
            getline(ss, to_search, '/');
            string current_line = _document.sed_search(to_search);
            cout << current_line << endl;
        }
        else if(regex_match(line, replace_pattern)){
            //Starting from char 2
            stringstream ss(line.substr(2));
            string old_text;
            string new_text;

            //Read text to old and new text from stream
            getline(ss, old_text, '/');
            getline(ss, new_text, '/');

            string current_line = _document.sed_replace(old_text, new_text);
            cout << current_line << endl;
        }
        else if(regex_match(line, single_char)){
            switch (line[0]){
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

                case 'i': {
                    _document.insert_lines();
                    break;
                }

                case 'c':{
                    if(_document.change_line()){
                        break;
                    }
                    goto default_operation;
                }

                case 'd':{
                    if(_document.delete_line()){
                        break;
                    }
                    goto default_operation;
                }

                case 'j':{
                    if(_document.join_lines()){
                        break;
                    }
                    goto default_operation;
                }

                case 'w':{
                    if(!_empty_ctor){
                        //If ctor wasn't empty, file name is already known
                        _document.write_file();
                        break;
                    }
                    goto default_operation;
                }

                case 'q': {
                    _document.quit();
                    break;
                }
            }
        }
        else if(regex_match(line, write_new_file)){
            string file = line.substr(2);
            _document.write_file(file);
        }
        else{
default_operation:
            cout << _undefined_operation << endl;
        }
    }
}