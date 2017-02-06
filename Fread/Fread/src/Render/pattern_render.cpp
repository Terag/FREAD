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
 * File:   pattern_render.cpp
 * Author: gg
 * 
 * Created on 26 janvier 2017, 15:24
 */

#include "Render/pattern_render.hpp"
#include <cmath>
#include <iostream>
pattern_render::pattern_render(): 
id(0)
{
}

pattern_render::pattern_render(int id, std::vector<float> meanTimeStamps,occurrence_render occurrence) :
id(id), meanTimeStamps(meanTimeStamps), occurrences(occurrence),events(occurrence.getEvents()){    //events(occurrence.getEvents());
    patternPoints = sf::VertexArray(sf::Quads, events.size()*8 );
    subDiv = sf::VertexArray(sf::Lines, events.size()*2 );
  

}

void pattern_render::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        sf::CircleShape circle[20];
    
    for (int i=0; i<10;i++)
    {
        circle[2*i]= sf::CircleShape((radius-radius/10*i),1000);
        circle[2*i].setFillColor(sf::Color::Transparent);
        circle[2*i].setOutlineThickness(1);
        circle[2*i].setOutlineColor(sf::Color(155, 155, 155));
        circle[2*i].setPosition((x-radius+radius/10*i),(y-radius+radius/10*i));
        circle[2*i+1]= sf::CircleShape((radius-(radius/20)-(radius/10)*i),1000);
        circle[2*i+1].setFillColor(sf::Color::Transparent);
        circle[2*i+1].setOutlineThickness(1);
        circle[2*i+1].setOutlineColor(sf::Color(231, 231, 231));
        circle[2*i+1].setPosition((x-radius+radius/20+radius/10*i),(y-radius+radius/20+radius/10*i));
    }
     sf::ConvexShape polygon(200);
        polygon.setPointCount(4);
        polygon.setPoint(0, sf::Vector2f(radius-radius/50,-2));
        polygon.setPoint(1, sf::Vector2f(radius, radius));
        polygon.setPoint(2, sf::Vector2f(radius, radius));
        polygon.setPoint(3, sf::Vector2f(radius+radius/50, -2));
        polygon.setOutlineColor(sf::Color(155, 155,155));
        polygon.setOutlineThickness(2);
        polygon.setPosition(x-radius, y-radius);
        
        target.draw(subDiv);
        for (int i=0; i<20;i++)
    {
       target.draw(circle[i],states);
    }
        target.draw(patternPoints);
        target.draw(polygon);
}
void pattern_render::SetPosition(int posX, int posY, float Radius)  {
    x = posX;
    y = posY;
    radius = Radius;
     calculatePoints();
}
void pattern_render::calculatePoints() {
   
    int sub = events.size();
    
    if (meanTimeStamps.size()>0) {
        
        float tMin = meanTimeStamps.at(0);
        float tMax = meanTimeStamps.at(meanTimeStamps.size()-1);
        float tradius = (tMax-tMin);        
        float radSub = 360.00 /sub; 
        
        for (unsigned int i = 0; i < events.size()  ; i++)
        {
            float tStart = meanTimeStamps[2*i];
            float tEnd = meanTimeStamps[2*i+1];
           /*
            Calcul à redéfinir
            */
            float tRadius = ((tradius-(tEnd-tStart))/tradius*radius) ;
            
            float demi =radSub * M_PI / 180.0/2;
            float tAngle = i * radSub * M_PI / 180.0 ;
         
            subDiv[2*i].position = sf::Vector2f(x,y);
            subDiv[2*i+1].position = sf::Vector2f(x + radius*sin(tAngle ),y -radius*cos(tAngle ));
            subDiv[2*i].color = sf::Color(199,199,199);
            subDiv[2*i+1].color = sf::Color(199,199,199);
            
            patternPoints[8*i].position = sf::Vector2f(x + radius*sin(tAngle ),y -radius*cos(tAngle ));
            patternPoints[8*i+1].position = sf::Vector2f(x + (radius+4)*sin(tAngle), y-(radius+4)*cos(tAngle));
            patternPoints[8*i+3].position = sf::Vector2f(x + tRadius*sin(tAngle+demi ),y -tRadius*cos(tAngle+demi));
            patternPoints[8*i+2].position = sf::Vector2f(x + (tRadius+4)*sin(tAngle+demi), y -(tRadius+4)*cos(tAngle+demi));
            patternPoints[8*i+4].position = sf::Vector2f(x + tRadius*sin(tAngle+demi ),y -tRadius*cos(tAngle+demi));
            patternPoints[8*i+5].position = sf::Vector2f(x + (tRadius+4)*sin(tAngle+demi), y -(tRadius+4)*cos(tAngle+demi));
            patternPoints[8*i+7].position = sf::Vector2f(x + radius*sin(tAngle+2*demi ),y -radius*cos(tAngle+2* demi ));
            patternPoints[8*i+6].position = sf::Vector2f(x + (radius+4)*sin(tAngle+2* demi), y -(radius+4)*cos(tAngle+2* demi));
            
            for (int j =0 ; j< 8;j++ )
            { 
                patternPoints[8*i+j].color = events[i].getColor();
            }
            
        }
    }
      
}
pattern_render::~pattern_render() 
{
}