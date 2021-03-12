//
// Created by dekel on 3/9/21.
//

#ifndef ED_EDITOR_HPP
#define ED_EDITOR_HPP

#include <string>

#include "Document.hpp"

using namespace std;

class Editor {
    const string _undefined_operation = "?";

    Document _document;
    bool _empty_ctor;

    inline bool is_integer(const string & s);
public:
    Editor(): _empty_ctor(true){}
    Editor(string file) : _document(file), _empty_ctor(false){}
    virtual ~Editor(){}

    void loop(void);
};


#endif //ED_EDITOR_HPP
