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
 * Author: emma
 *
 * Created on 24 janvier 2017, 10:25
 */

#ifndef CONTAINER_RENDER_HPP
#define CONTAINER_RENDER_HPP



#endif /* CONTAINER_RENDER_HPP */

#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>

#include "occurrence_render.hpp"

class container_render : public sf::Drawable
{
private : 
    int id; 
    std::string name;
    float scale = 1.f;
    int offsetX = 10;
    int offsetY = 20;
    int sizeContainer = 500;
    sf::Vertex line[] = 
    {
        sf::Vertex(sf::Vector2f(offsetX, offsetY*id)), 
        sf::Vertex(sf::Vector2f((scale*absoluteTime) + offsetX, offsetY*id))
    }; 
    static float absoluteTime;
    std::vector<occurrence_render> occurrences;
        
public : 
    container_render();
    container_render(int id, std::string name, float absoluteTime);
    container_render(int id, std::string name, float absoluteTime, int offsetX, int offsetY);
    float getScale();
    int getOffsetX();
    int getOffsetY();
    int getId();
    void addOccurrence(occurrence_render occ);
    void calculateScale(float absoluteTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    ~container_render();
            
};
