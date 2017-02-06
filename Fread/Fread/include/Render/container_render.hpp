/*
 * Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of the copyright holders nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   container_render.hpp
 * Author: Emma et Jerome 
 *
 * Created on 24 janvier 2017, 10:25
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../FObjet.hpp"
#include "event_render.hpp"
#include "occurrence_render.hpp"

class container_render : public sf::Drawable
{
private : 
    // the id of the container
    int id; 
    // the name or "alias" of a container, so that it can be drawn later when placing its mouse on the container
    std::string name;
    // a vector of all the occurrence_render (bloc of events) that occures in this container
    std::vector<occurrence_render> occurrences;
    // the font and the content of the sfml::text representing the id
    sf::Font font;
    sf::Text textId;
    //the vertex array of the line representing the container on the window
    sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
      
public : 
    //constructors & destructor
    container_render();
    container_render(int id, std::string name, int containerSize, int offsetX, int offsetY,  int windowContainerOffsetY);
    ~container_render();
    //setters
    //getters
    int getId();
    std::string getName();
    std::vector<occurrence_render> getOccurrences();
    //add an occurrence_render to its occurrences list
    void addOccurrence(occurrence_render occ);
    //update 
    void updatePosition(int containerSize, int offsetX, int offsetY, int windowContainerOffsetY);
    //draw
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;     
};