/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <bitset>
#include <memory>

#include "Parser/parser.hpp"
#include "Parser/PAJE/paje_interface.hpp"
#include "Parser/PAJE/Reader_MainTrace.hpp"
#include "Parser/statesConfig.hpp"
#include "Parser/PAJE/Container_Reader.hpp"
#include "Parser/PAJE/Pattern_Reader.hpp"

using namespace std;

namespace paje
{   
    typedef void (*PAJE_EventFunc)(std::string, const EventDef&);
        //PajeTypeDef events
    void DefineContainerType(std::string line, EventDef const& event);
    void DefineStateType(std::string line, EventDef const& event);
    void DefineEventType(std::string line, EventDef const& event);
    void DefineVariableType(std::string line, EventDef const& event);
    void DefineLinkType(std::string line, EventDef const& event);
    void DefineEntityValue(std::string line, EventDef const& event);
        //PajePatternDef events
    void StartDefinePattern(std::string line, EventDef const& event);
    void EndDefinePattern(std::string line, EventDef const& event);
        //Container events
    void CreateContainer(std::string line, EventDef const& event);
    void DestroyContainer(std::string line, EventDef const& event);
        //State events
    void SetState(std::string line, EventDef const& event);
    void PushState(std::string line, EventDef const& event);
    void PopState(std::string line, EventDef const& event);
    void ResetState(std::string line, EventDef const& event);
        //Event events
    void NewEvent(std::string line, EventDef const& event);
        //Variable events
    void SetVariable(std::string line, EventDef const& event);
    void AddVariable(std::string line, EventDef const& event);
    void SubVariable(std::string line, EventDef const& event);
        //Link events
    void StartLink(std::string line, EventDef const& event);
    void EndLink(std::string line, EventDef const& event);
        //Include events
    void IncludeFile(std::string line, EventDef const& event);
    void IncludeContainerFile(std::string line, EventDef const& event);
    void IncludePatternFile(std::string line, EventDef const& event);
        //Pattern events
    void StartPattern(std::string line, EventDef const& event);
    void EndPattern(std::string line, EventDef const& event);
    
    void setName(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setType(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setAlias(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setStartContainerType(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setEndContainerType(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setColor(PajeTypeDef& newPJT, string str);
    
    void parseMainTrace();
    void initType(PajeTypeDef& newPJT);
    void defineType(string const& line, EventDef const& event, PajeType type);
    string getNextParamInLine(string const& line, int &spacePos);
    //Event Functions
    void pushEventInCurrentOccurrence(string const& line, EventDef const& event);

/*---------------------------------Internal variables --------------------------------------------------------*/

    static Reader_MainTrace mainTrace;
    
    static StatesConfig stateConf;
    
    // Table of functions use when a pajeEvent is read
    static PAJE_EventFunc eventFunctions[25] = { //PajeTypeDef events
                                                DefineContainerType,    //PEF_PajeDefineContainerType
                                                DefineStateType,        //PEF_PajeDefineStateType
                                                DefineEventType,        //PEF_PajeDefineEventType
                                                DefineVariableType,     //PEF_PajeDefineVariableType
                                                DefineLinkType,         //PEF_PajeDefineLinkType
                                                DefineEntityValue,      //PEF_PajeDefineEntityValue
                                                //PajePatternDef events
                                                StartDefinePattern,     //PEF_PajeStartDefinePattern
                                                EndDefinePattern,       //PEF_PajeEndDefinePattern
                                                //Container events
                                                CreateContainer,        //PEF_PajeCreateContainer
                                                DestroyContainer,       //PEF_PajeDestroyContainer
                                                //State events
                                                SetState,               //PEF_PajeSetState
                                                PushState,              //PEF_PajePushState
                                                PopState,               //PEF_PajePopState
                                                ResetState,             //PEF_PajeResetState
                                                //Event events
                                                NewEvent,               //PEF_PajeNewEvent
                                                //Variable events
                                                SetVariable,            //PEF_PajeSetVariable
                                                AddVariable,            //PEF_PajeAddVariable
                                                SubVariable,            //PEF_PajeSubVariable
                                                //Link events
                                                StartLink,              //PEF_PajeStartLink
                                                EndLink,                //PEF_PajeEndLink
                                                //Include events
                                                IncludeFile,            //PEF_IncludeFile
                                                IncludeContainerFile,   //PEF_IncludeContainerFile
                                                IncludePatternFile,     //PEF_IncludePatternFile
                                                //Pattern events
                                                StartPattern,           //PEF_PajeStartPattern
                                                EndPattern,             //PEF_PajeEndPattern
                                             };
   
    static int current_container_id;
    static vector<Container_Buffer> containers;
    static shared_ptr<Occurrence_Buffer> current_occurrence;
    
    static int current_pattern_id;
    static vector<Pattern_Buffer> patterns;
    
    static vector<EventDef> eventDefs;
    
    static vector<PajeTypeDef> typeDefs;
    
    
/*---------------------------------External functions --------------------------------------------------------*/

    void awake(string const& path){
        mainTrace.init(path);
        mainTrace.parseHeader(eventDefs);
        stateConf.initEvents();
    }
    
    bool start() {
        parseMainTrace();
        for (auto it : typeDefs) {
            switch (it.nameType){
                case FT_STRING :
                    cout << it.type << " name : " << it.name_str;
                    break;
                case FT_INT :
                    cout << it.type << " name : " << it.name_int;
                    break;
                default :
                    cout << "error, unexpected type : " << it.typeType;
                    break;
            }
            switch (it.typeType){
                case FT_STRING :
                    cout << " - type : " << it.type_str;
                    break;
                case FT_INT :
                    cout << " - type : " << it.type_int;
                    break;
                default :
                    cout << "error, unexpected type : " << it.typeType;
                    break;
            }
            if(it.color.a > 0){
                cout << " - color : " << it.color.r << " " << it.color.g << " " << it.color.b;
            }
            switch (it.aliasType){
                case FT_STRING :
                    cout << " - alias : " << it.alias_str;
                    break;
                case FT_INT :
                    cout <<" - alias : " << it.alias_int;
                    break;
                default :
                    cout << "error, unexpected type : " << it.typeType;
            }
            cout << " - state : " << it.state << endl;
        }
        for(auto& it : containers) {
            cout << "Container " << it.id << " name : " << it.alias << " t1=" << to_string((float)it.beginTime) << " t2=" << to_string((float)it.endTime) << endl;
        }
        
        return true;
    }
    
    void parseMainTrace(){
        int id;
        int fpos;
        string line;
        cout << "Begin parse main.trace" << endl;
        mainTrace.openStream();
        line = mainTrace.getLine();
        while(!mainTrace.end() && line != "!"){
            
            try{
                fpos = line.find(' ');
                id = stoi(line.substr(0,fpos));
            }
            catch(const std::invalid_argument& ia){
                cout << "error, invalid format : " << ia.what() << " parameter " << line.substr(0, fpos) << endl;
            }
            
            if(eventDefs[id].name > -1 && eventDefs[id].name < 8){
                cout << "function call : " << eventDefs[id].id << " ";
                eventFunctions[eventDefs[id].name](line, eventDefs[id]);
            } 
            else if(eventDefs[id].name == PEF_PajeCreateContainer || eventDefs[id].name == PEF_PajeDestroyContainer || eventDefs[id].name == PEF_IncludeContainerFile || eventDefs[id].name == PEF_IncludePatternFile){
                cout << "function call : " << eventDefs[id].id << " ";
                eventFunctions[eventDefs[id].name](line, eventDefs[id]);
            }
            else if (eventDefs[id].id == -1){
                cout << "error, eventDef not set : " << eventDefs[id].id << endl;
            }
            else {
                cout << "unexpected function during MainTrace parsing : " << eventDefs[id].name << " " << eventDefs[id].name_str << endl;
            }
            line = mainTrace.getLine();
        }
        
        mainTrace.closeStream();
    }
    
    void PajeEventCall(std::string line, EventDef& event) {
        eventFunctions[event.name](line, event);
    }
    
    void getEventsBetweenTwoTimesInContainer(int container_id, float t_begin, float t_end) {
        int fpos;
        int id;
        cout << "Request between t1=" << t_begin << " and t2=" << t_end << " in container : " << container_id << endl;
        
        vector<string> lines = containers[container_id].reader->getLinesBetweenTwoTimes(t_begin, t_end);
        cout << "lines get" << endl;
        //current_occurrence = make_shared<FOccurrence>();
        for(auto& it : lines) {    
            try{
                fpos = it.find(' ');
                id = stoi(it.substr(0,fpos));
            }
            catch(const std::invalid_argument& ia){
                cout << "error, invalid format : " << ia.what() << " parameter " << it.substr(0, fpos) << endl;
            }
            
            if(eventDefs[id].name > 22 && eventDefs[id].name < 25){
                //cout << "function call : " << eventDefs[id].id << " ";
                eventFunctions[eventDefs[id].name](it, eventDefs[id]);
            } 
            else if (eventDefs[id].id == -1){
                cout << "error, eventDef not set : " << eventDefs[id].id << endl;
            }
            else {
                cout << "unexpected function during Container parsing : " << eventDefs[id].name << " " << eventDefs[id].name_str << endl;
            }
        }
        
    }
    
/*---------------------------------Paje Event functions --------------------------------------------------------*/

/*-----------TypeDef events------------*/   
    
    void DefineContainerType(std::string line, EventDef const& event) {
        cout << "DefineContainerType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_CONTAINER);
    }
    
    void DefineStateType(std::string line, EventDef const& event) {
        cout << "DefineStateType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_STATE);        
    }
    
    void DefineEventType(std::string line, EventDef const& event) {
        cout << "DefineEventType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_EVENT);
    }
    
    void DefineVariableType(std::string line, EventDef const& event) {
        cout << "DefineVariableType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_VARIABLE);
    }
    
    void DefineLinkType(std::string line, EventDef const& event) {
        cout << "DefineLinkType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_LINK);
    }
    
    void DefineEntityValue(std::string line, EventDef const& event) {
        cout << "DefineEntityValue function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_VALUE);
    }
  
/*----------PatternDef events----------*/
    
    void StartDefinePattern(std::string line, EventDef const& event) {
        cout << "DefinePatternStart function called with : " << event.name_str << " " << event.name << endl;
    }
    
    void EndDefinePattern(std::string line, EventDef const& event) {
        cout << "DefinePatternEnd function called with : " << event.name_str << " " << event.name << endl;
    }
    
/*----------Container events-----------*/
    
    void CreateContainer(std::string line, EventDef const& event){
        cout << "CreateContainer function called with : " << event.name_str << " " << event.name << endl;
        
        int spacePos;
        int id = containers.size();
        float time;
        string sub_str;
        containers.push_back(Container_Buffer());
       
        containers[id].id = id;
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_NAME :
                    containers[id].name = sub_str;
                    break;
                case FN_TYPE :
                    cout << "Type define to define" << endl;
                    break;
                case FN_ALIAS :
                    containers[id].alias = sub_str;
                    break;
                case FN_CONTAINER :
                    cout << "Parent define to define" << endl;
                    break;
                case FN_TIME :
                    time = stof(sub_str);
                    containers[id].beginTime = time;
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
    }
    
    void DestroyContainer(std::string line, EventDef const& event){
        cout << "DestroyContainer function called with : " << event.name_str << " " << event.name << endl;
        int spacePos;
        int id = -1;
        string sub_str;
        string name;
        float time;
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_NAME :
                    name = sub_str;
                    for(auto& ct : containers) {
                        if(ct.name == sub_str) {
                            id = ct.id;
                            break;
                        }
                    }
                    break;
                case FN_TYPE :
                    cout << "Type define to define" << endl;
                    break;
                case FN_TIME :
                    time = stof(sub_str);
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        
        if(id > -1) {
            containers[id].endTime = time;
        } else {
            cout << "error, undefined container name : " << name << endl;
        }
    }
    
/*----------State events---------------*/
    
    void SetState(std::string line, EventDef const& event){
        cout << "SetState function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
    void PushState(std::string line, EventDef const& event){
        cout << "PushState function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
    void PopState(std::string line, EventDef const& event){
        cout << "PopState function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
    void ResetState(std::string line, EventDef const& event) {
        cout << "ResetState function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
   
/*----------Event events---------------*/
    
    void NewEvent(std::string line, EventDef const& event){
        cout << "NewEvent function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
/*----------Variable events------------*/
    
    void SetVariable(std::string line, EventDef const& event){
        cout << "SetVariable function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
    void AddVariable(std::string line, EventDef const& event){
        cout << "AddVariable function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
    void SubVariable(std::string line, EventDef const& event){
        cout << "SubVariable function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
/*----------Link events----------------*/
    
    void StartLink(std::string line, EventDef const& event){
        cout << "StartLink function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
    void EndLink(std::string line, EventDef const& event){
        cout << "EndLink function called with : " << event.name_str << " " << event.name << endl;
        pushEventInCurrentOccurrence(line, event);
    }
    
/*----------Include events-------------*/
    
    void IncludeFile(std::string line, EventDef const& event){
        
    }
    
    void IncludeContainerFile(std::string line, EventDef const& event){
        cout << "IncludeContainerFile function called with : " << event.name_str << " " << event.name << endl;
        int spacePos;
        int id = -1;
        string sub_str;
        string path = "";
        
        sub_str = mainTrace.getPath();
        int path_cutter = sub_str.find_last_of('/')+1;
        for(int i=0; i<path_cutter; i++) {
            path.push_back(sub_str[i]);
        } 
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_NAME :
                    for(auto& ct : containers) {
                        if(ct.name == sub_str) {
                            id = ct.id;
                            break;
                        }
                    }
                    break;
                case FN_TYPE :
                    cout << "Type define to define" << endl;
                    break;
                case FN_FILE :
                    path += sub_str;
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        
        containers[id].reader = make_unique<Container_Reader>(containers[id].alias, id);
        containers[id].reader->setBeginTime(containers[id].beginTime);
        containers[id].reader->setEndTime(containers[id].endTime);
        containers[id].reader->init(path, id);
        containers[id].reader->checkIfReady();
        
        cout << "Send container : " << containers[id].alias << " path : " << path << " to core" << endl;
        sendContainerToCore(FContainer(id, containers[id].alias, pair<float,float>(containers[id].beginTime,containers[id].endTime)));
    }
    
    //This function is not a definitive function, it will be delete in futur
    eventType convertState(StateType state) {
        switch(state) {
            case STATE_COMPUTE :
                return COMPUTE;
                break;
            case STATE_WAIT :
                return WAIT;
                break;
            case STATE_SEND :
                return SEND;
                break;
            default :
                return WAIT;
                break;
        }
    }
    
    void IncludePatternFile(std::string line, EventDef const& event){
        cout << "IncludePatternFile function called with : " << event.name_str << " " << event.name << endl;
        int spacePos;
        int id = patterns.size();
        string sub_str;
        string path = "";
        patterns.push_back(Pattern_Buffer());
        patterns[id].id = id;
        
        sub_str = mainTrace.getPath();
        int path_cutter = sub_str.find_last_of('/')+1;
        for(int i=0; i<path_cutter; i++) {
            path.push_back(sub_str[i]);
        }
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_ALIAS :
                    patterns[id].alias = sub_str;
                    break;
                case FN_TYPE :
                    cout << "Type define to define" << endl;
                    break;
                case FN_FILE :
                    path += sub_str;
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        
        current_pattern_id = id;
        patterns[id].reader = make_unique<Pattern_Reader>(patterns[id].alias, id);
        patterns[id].occurrence_buffer = make_shared<Occurrence_Buffer>();
        patterns[id].reader->init(path, id);
        patterns[id].reader->parseHeader(eventDefs);

        cout << "Send pattern to core " << patterns[id].alias << " events  : " << endl;
        FPattern newPattern = FPattern(id);
        vector<eventType> events;
        vector<float> times;
        
        events.push_back(convertState(patterns[id].occurrence_buffer->states[0]));
        times.push_back(patterns[id].occurrence_buffer->timeStamps[0]);
        cout << patterns[id].occurrence_buffer->alias[0] << " type : " << patterns[id].occurrence_buffer->states[0] << " time : " << patterns[id].occurrence_buffer->timeStamps[0] << endl;
        
        for(int i=1; i<patterns[id].occurrence_buffer->alias.size(); i++) {
            if(patterns[id].occurrence_buffer->timeStamps[i] != patterns[id].occurrence_buffer->timeStamps[i-1]){
                events.push_back(convertState(patterns[id].occurrence_buffer->states[i]));
                times.push_back(patterns[id].occurrence_buffer->timeStamps[i]);
                cout << patterns[id].occurrence_buffer->alias[i] << " type : " << patterns[id].occurrence_buffer->states[i] << " time : " << patterns[id].occurrence_buffer->timeStamps[i] << endl;
            }
        }
        newPattern.setEventTypes(events);
        newPattern.setMeanTimeStamps(times);
        sendPatternToCore(newPattern);
        current_pattern_id = -1;
    }
    
/*----------Pattern events-------------*/
    
    void StartPattern(std::string line, EventDef const& event){
        //cout << "StartPattern function called with : " << event.name_str << " " << event.name << endl;
        int spacePos;
        string sub_str;
        float time;
        string alias;
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_ALIAS :
                    alias = sub_str;
                    break;
                case FN_TIME :
                    time = stof(sub_str);
                    break;
                default :
                    //cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        
        for(int i=0; i<patterns.size(); i++) {
            if(patterns[i].alias == alias) {
                current_pattern_id = i;
                break;
            }
        }
        
        if(current_pattern_id > -1) {
            patterns[current_pattern_id].occurrence_buffer->t_begin = time;
        }
    }
    
    void EndPattern(std::string line, EventDef const& event){
        //cout << "EndPattern function called with : " << event.name_str << " " << event.name << endl;
        int spacePos;
        string sub_str;
        float time;
        string alias;
        int key;
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_ALIAS :
                    alias = sub_str;
                    break;
                case FN_TIME :
                    time = stof(sub_str);
                    break;
                case FN_KEY :
                    key =  stoi(sub_str);
                    break;
                default :
                    //cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        
        if(patterns[current_pattern_id].alias == alias) {
            patterns[current_pattern_id].occurrence_buffer->t_end = time;
            FOccurrence occurrence;
            occurrence.setContainerId(current_pattern_id);
            occurrence.setId(key);
            occurrence.setPatternId(current_pattern_id);
            occurrence.pushTime(patterns[current_pattern_id].occurrence_buffer->t_begin);
            occurrence.pushTime(patterns[current_pattern_id].occurrence_buffer->t_end);
            cout << "--------- Occurrence sended to core pattern alias : " << alias << " key : " << key << " t1=" << patterns[current_pattern_id].occurrence_buffer->t_begin << " t2=" << patterns[current_pattern_id].occurrence_buffer->t_end << endl;
            sendOccurenceToCore(occurrence);
        }
    }
    
/*---------------------------------Type definition functions ---------------------------------------------------*/
    
    void defineType(string const& line, EventDef const& event, PajeType type) {
        int spacePos;
        string sub_str;
        
        PajeTypeDef newPajeType;
        initType(newPajeType);
        
        newPajeType.type = type;
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_NAME :
                    setName(newPajeType, sub_str, it.type);
                    break;
                case FN_TYPE :
                    setType(newPajeType, sub_str, it.type);
                    break;
                case FN_ALIAS :
                    setAlias(newPajeType, sub_str, it.type);
                    break;
                case FN_STARTCONTAINERTYPE :
                    setStartContainerType(newPajeType, sub_str, it.type);
                    break;
                case FN_ENDCONTAINERTYPE :
                    setEndContainerType(newPajeType, sub_str, it.type);
                    break;
                case FN_COLOR :
                    setColor(newPajeType, sub_str);
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        
        if(newPajeType.nameType == FT_STRING && newPajeType.aliasType == FT_STRING){
            newPajeType.state = stateConf.getState(newPajeType.name_str, newPajeType.alias_str);
        } else {
            newPajeType.state = STATE_UNKNOWN;
        }
        
        typeDefs.push_back(newPajeType);
    }
  
    string getNextParamInLine(string const& line, int &spacePos) {
        int fpos,spos;
        fpos = spacePos;
        string sub_str;
        if(line.substr(fpos, 1) == " "){
            if(line.substr(fpos+1, 1) == "\""){
                spos = line.find("\"", fpos+2);
                spacePos = line.find(" ", spos);
                sub_str = line.substr(fpos+2, spos-fpos-2);
                return sub_str;
            }
            else {
                spos = line.find(" ", fpos+1);
                spacePos = spos;
                sub_str = line.substr(fpos+1, spos-fpos-1);
                return sub_str;
            }
        }
        else if(fpos == 0){
            if(line.substr(fpos, 1) == "\""){
                spos = line.find("\"", fpos+1);
                spacePos = line.find(" ", spos);
                sub_str = line.substr(fpos+1, spos-fpos-1);
                return sub_str;
            }
            else {
                spos = line.find(" ", fpos);
                spacePos = spos;
                sub_str = line.substr(fpos, spos-fpos);
                return sub_str;
            }
        }
        else {
            cout << "error, " << spacePos << " is not a space position in line : " << line << endl;
            return "!";
        }
    }
    
    void initType(PajeTypeDef& newPJT){
        newPJT.type = PT_UNDEFINED;
        
        newPJT.nameType = FT_UNDEFINED;
        newPJT.typeType = FT_UNDEFINED;
        newPJT.aliasType = FT_UNDEFINED;
        newPJT.startContainerTypeType = FT_UNDEFINED;
        newPJT.endContainerTypeType = FT_UNDEFINED;
        newPJT.color = FColor();
        newPJT.state = STATE_UNKNOWN;
    }
    
    void setName(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.nameType = FT_STRING;
                newPJT.name_str = str;
                break;
            case FT_INT :
                newPJT.nameType = FT_INT;
                newPJT.name_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setType(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.typeType = FT_STRING;
                newPJT.type_str = str;
                break;
            case FT_INT :
                newPJT.typeType = FT_INT;
                newPJT.type_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setAlias(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.aliasType = FT_STRING;
                newPJT.alias_str = str;
                break;
            case FT_INT :
                newPJT.aliasType = FT_INT;
                newPJT.alias_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setStartContainerType(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.startContainerTypeType = FT_STRING;
                newPJT.startContainerType_str = str;
                break;
            case FT_INT :
                newPJT.startContainerTypeType = FT_INT;
                newPJT.startContainerType_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setEndContainerType(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.endContainerTypeType = FT_STRING;
                newPJT.endContainerType_str = str;
                break;
            case FT_INT :
                newPJT.endContainerTypeType = FT_INT;
                newPJT.endContainerType_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }

    void setColor(PajeTypeDef& newPJT, string str){
        int spacePos = 0;
        int r = (int)(stof(getNextParamInLine(str, spacePos))*255);
        int g = (int)(stof(getNextParamInLine(str, spacePos))*255);
        int b = (int)(stof(getNextParamInLine(str, spacePos))*255);
        newPJT.color = FColor(r, g, b, 255);
    }
    
/*---------------------------------Event functions --------------------------------------------------------------*/
    
    void pushEventInCurrentOccurrence(string const& line, EventDef const& event) {
        int spacePos;
        float time;
        string sub_str;
        string name, alias;
        string type, value;
        
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_TYPE :
                    type = sub_str;
                    break;
                case FN_TIME :
                    time = stof(sub_str);
                    //cout << "----------------------------event time :" << time << endl;
                    patterns[current_pattern_id].occurrence_buffer->timeStamps.push_back(time);
                    break;
                case FN_VALUE :
                    value = sub_str;
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        for(auto& it : typeDefs) {
            if(type == it.type_str && value == it.alias_str) {
                type = alias = it.alias_str;
                name = it.name_str;
            }
        }
        StateType state = stateConf.getState(name, alias);
        patterns[current_pattern_id].occurrence_buffer->states.push_back(state);         
        patterns[current_pattern_id].occurrence_buffer->alias.push_back(type);
    }
}