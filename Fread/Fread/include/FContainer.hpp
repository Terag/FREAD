/*
Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the copyright holders nor the names of its contributors 
  may be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#ifndef FCONTAINER_HPP
#define FCONTAINER_HPP

#include <utility>
#include <string>
#include <algorithm>
#include <vector>
#include "FObjet.hpp"

struct patternStruct {
  int id;
  int contId;
  int occId;
  float tBegin;
  float tEnd;
  patternStruct(int i, int ci, float t1, float t2) : id(i), contId(ci), tBegin(t1), tEnd(t2) {} 

  bool operator < (const patternStruct& other) const
  {
      return (tBegin < other.tBegin);
  }
};

class FContainer : public FObjet
{
private :

    int id;
    std::string alias;
    std::vector<int> listeIdOccurrences;
    std::pair<float,float> timestamp_begin_end;
    std::vector<patternStruct> patternList;


public:
    FContainer();
    FContainer(int i);
    FContainer( int const& c_id, std::string c_alias, std::pair<float, float> t_begin_and_end);
    ~FContainer();

    void setId(int const& newId) {id = newId;}
    void setAlias(int const& newAlias) {alias = newAlias;}
    void setTimestamp(float const& t_begin, float const& t_end) {timestamp_begin_end = std::pair<float,float>(t_begin, t_end);}
    std::vector<int> getListeIdOccurrences() {return listeIdOccurrences;}

    int getId() const {return id;}
    std::string getAlias() const {return alias;}
    float getBeginTime() const {return timestamp_begin_end.first;}
    float getEndTime() const {return timestamp_begin_end.second;}
    std::pair<float, float> getTimelapse() {return timestamp_begin_end;}

    void add_pattern(patternStruct element);
    void remove_pattern();
    bool contains( patternStruct element );
    std::vector<patternStruct> getPatternList() const { return patternList; }


};

#endif //FCONTAINER_HPP