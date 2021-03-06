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
 * File:   pattern_render.hpp
 * Author: Emma, Jerome
 *
 * Created on 24 janvier 2017, 11:38
 */


#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include "Render/container_render.hpp"
#include <SFML/Graphics/VertexArray.hpp>

class pattern_render : public sf::Drawable {
    
private : 
//the id of the pattern drawn     
int id;
//x coordinate of the entire pattern_render (circles + events)
int x;
//y coordinate of the entire pattern_render (circles + events)
int y;
//the radius of the biggest circle
int radius;
// the vector of the timestamps of the pattern 
std::vector<float> meanTimeStamps;
//occurence represented by the pattern
occurrence_render occurrences;
//list of event in the pattern
std::vector<event_render> events;
//Points to draw the pattern
sf::VertexArray patternPoints;
//Lines of subdivision to draw
sf::VertexArray subDiv;

      
public : 
//constructors & destructors    
pattern_render();
pattern_render(int id, std::vector<float> meanTimeStamps, occurrence_render occurrence);
~pattern_render();
//draw of th render
void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
// Calculate the points for drawing 
void calculatePoints() ;
// Place the pattern in the windows 
void SetPosition(int posX, int posY, float Radius);

};
