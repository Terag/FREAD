#include "Parser/PAJE/Reader_MainTrace.hpp"

using namespace std;

namespace paje
{
    Reader_MainTrace::Reader_MainTrace()
    {
        
    }
    
    void Reader_MainTrace::init(std::string const& path){
        mainTrace_Path = path;
    }

    void Reader_MainTrace::parseHeader(std::vector<EventDef>& eventDefs)
    {
        string in;
        int size = -1;
        int i = 0;

        mainTrace_Stream.open(mainTrace_Path);
        while(!mainTrace_Stream.eof()){
            mainTrace_Stream >> in;
            if(in == "EventDef"){
                i++;
                mainTrace_Stream >> in;
                mainTrace_Stream >> i;
                if(i>size){
                    size = i+1;
                }
            }
            mainTrace_Stream.ignore(256, '%');
        }
        mainTrace_Stream.close();

        eventDefs.reserve(size + 1);
        for(int i = 0; i < size + 1; i++){
            eventDefs.push_back(EventDef());
            eventDefs[i].id = -1;
        }

        mainTrace_Stream.open(mainTrace_Path);
        do {
            getline(mainTrace_Stream, in);
            if(in.substr(0, 9) == "%EventDef"){
                eventDef(eventDefs, in);
            }
        } while(!mainTrace_Stream.eof());
        mainTrace_Stream.close();
        
        for(auto it : eventDefs){
            if(it.id != -1){
                cout << it.id << " Event : " << it.name_str << " " << it.name << endl;
                for(auto itf : it.fieldDefs){
                    cout << "   " << itf.name << " and type " << itf.type << endl;
                }
            }
        }
    }

    void Reader_MainTrace::eventDef(std::vector<EventDef>& eventDefs, string &in)
    {
        int fpos, spos; //use to make substr
        int id = 1;
        string str;
        
        fpos = in.find(' ');
        spos = in.find(' ', fpos + 1);
        str = in.substr(fpos + 1, spos-fpos-1);
        
        fpos = spos;
        spos = in.find(' ', fpos + 1);
        id = stoi(in.substr(fpos + 1, spos-fpos-1));
        if(id < 0 || id > (int)eventDefs.size()){
            cout << "error, id is out of range : " << id << endl;
        }
        eventDefs[id].id = id;
        eventDefs[id].name_str = str;
        
        if(str == "PajeDefineContainerType"){
            eventDefs[id].name = PEF_PajeDefineContainerType;           
        }
        else if(str == "PajeDefineStateType"){
            eventDefs[id].name = PEF_PajeDefineStateType;
        }
        else if(str == "PajeDefineEventType"){
            eventDefs[id].name = PEF_PajeDefineEventType;
        }
        else if(str == "PajeDefineVariableType"){
            eventDefs[id].name = PEF_PajeDefineVariableType;
        }
        else if(str == "PajeDefineLinkType"){
            eventDefs[id].name = PEF_PajeDefineLinkType;
        }
        else if(str == "PajeDefineEntityValue"){
            eventDefs[id].name = PEF_PajeDefineEntityValue;
        }
        else if(str == "PajeStartDefinePattern"){
            eventDefs[id].name = PEF_PajeStartDefinePattern;
        }
        else if(str == "PajeEndDefinePattern"){
            eventDefs[id].name = PEF_PajeEndDefinePattern;
        }
        else if(str == "PajeCreateContainer"){
            eventDefs[id].name = PEF_PajeCreateContainer;
        }
        else if(str == "PajeDestroyContainer"){
            eventDefs[id].name = PEF_PajeDestroyContainer;
        }
        else if(str == "PajeSetState"){
            eventDefs[id].name = PEF_PajeSetState;
        }
        else if(str == "PajePushState"){
            eventDefs[id].name = PEF_PajePushState;
        }
        else if(str == "PajePopState"){
            eventDefs[id].name = PEF_PajePopState;
        }
        else if(str == "PajeResetState"){
            eventDefs[id].name = PEF_PajeResetState;
        }
        else if(str == "PajeNewEvent"){
            eventDefs[id].name = PEF_PajeNewEvent;
        }
        else if(str == "PajeSetVariable"){
            eventDefs[id].name = PEF_PajeSetVariable;
        }
        else if(str == "PajeAddVariable"){
            eventDefs[id].name = PEF_PajeAddVariable;
        }
        else if(str == "PajeSubVariable"){
            eventDefs[id].name = PEF_PajeSubVariable;
        }
        else if(str == "PajeStartLink"){
            eventDefs[id].name = PEF_PajeStartLink;
        }
        else if(str == "PajeEndLink"){
            eventDefs[id].name = PEF_PajeEndLink;
        }
        else if(str == "IncludeFile"){
            eventDefs[id].name = PEF_IncludeFile;
        }
        else if(str == "IncludeContainerFile"){
            eventDefs[id].name = PEF_IncludeContainerFile;
        }
        else if(str == "IncludePatternFile"){
            eventDefs[id].name = PEF_IncludePatternFile;
        }
        else if(str == "PajeStartPattern"){
            eventDefs[id].name = PEF_PajeStartPattern;
        }
        else if(str == "PajeEndPattern"){
            eventDefs[id].name = PEF_PajeEndPattern;
        }
        else {
            cout << "error, unknow PajeEventFunction : " << str << endl;
            eventDefs[id].name = PEF_Undefined;
        }
        
        string field_str;
        getline(mainTrace_Stream, field_str);
        while(!mainTrace_Stream.eof()){
            
            if(field_str.substr(0, field_str.find(' ')) == "%"){
                eventDefs[id].fieldDefs.push_back(fieldDef(field_str));
            }
            
            getline(mainTrace_Stream, field_str);
            if(field_str.substr(0, 12) == "%EndEventDef"){
                break;
            }
        }
    }

    FieldDef Reader_MainTrace::fieldDef(string &in)
    {
        FieldDef newField;
        int fpos, spos;
        
        fpos = in.find(' ');
        spos = in.find(' ', fpos+1);
        string name = in.substr(fpos+1, spos-fpos-1);
        
        if(name == "Name"){
           newField.name = FN_NAME;
        }
        else if(name == "Type"){
            newField.name = FN_TYPE;
        }
        else if(name == "Alias"){
            newField.name = FN_ALIAS;
        }
        else if(name == "Color"){
            newField.name = FN_COLOR;
        }
        else if(name == "Time"){
            newField.name = FN_TIME;
        }
        else if(name == "Container"){
            newField.name = FN_CONTAINER;
        }
        else if(name == "Value"){
            newField.name = FN_VALUE;
        }
        else if(name == "StartContainer"){
            newField.name = FN_STARTCONTAINER;
        }
        else if(name == "EndContainer"){
            newField.name = FN_ENDCONTAINER;
        }
        else if(name == "StartContainerType"){
            newField.name = FN_STARTCONTAINERTYPE;
        }
        else if(name == "EndContainerType"){
            newField.name = FN_ENDCONTAINERTYPE;
        }
        else if(name == "Key"){
            newField.name = FN_KEY;
        }
        else if(name == "File"){
            newField.name = FN_FILE;
        }
        else{
            cout << "error, unknow FieldName : " << name << endl;
        }

        fpos = spos;
        spos = in.find(' ', fpos+1);
        string type = in.substr(fpos+1, spos-fpos-1);
        
        if(type == "string"){
            newField.type = FT_STRING;
        }
        else if(type == "int"){
            newField.type = FT_INT;
        }
        else if(type == "color"){
            newField.type = FT_COLOR;
        }
        else if(type == "date"){
            newField.type = FT_DATE;
        }
        else if(type == "double"){
            newField.type = FT_DOUBLE;
        }
        else if(type == "hex"){
            newField.type = FT_HEX;
        } 
        else {
            cout << "error, unknow fieldType : " << type << endl;
        }
        
        return newField;
    }

    void Reader_MainTrace::openStream(){
        mainTrace_Stream.open(mainTrace_Path);
    }
    
    void Reader_MainTrace::closeStream(){
        mainTrace_Stream.close();
    }
    
    string Reader_MainTrace::getLine(){
        string in;
        
        getline(mainTrace_Stream, in);
        while (!mainTrace_Stream.eof()) {
            if(in.substr(0,1) != "%"){
                return in;
            }
            getline(mainTrace_Stream, in);
        };
        return "!";
    }
    
    bool Reader_MainTrace::end(){
        return mainTrace_Stream.eof();
    }
    
    Reader_MainTrace::~Reader_MainTrace() {
    }
}
