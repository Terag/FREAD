/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   occurrence_render.hpp
 * Author: emma
 *
 * Created on 6 février 2017, 18:35
 */

#pragma once 
#include <vector>
#include <SFML/Graphics.hpp>
#include "../FObjet.hpp"
#include "event_render.hpp"

class occurrence_render : public sf::Drawable {
 
private : 
int id;
std::vector<float> timeStamps;
std::vector<eventType> eventTypes;
std::vector<event_render> events; 

public : 
//constructors & destructors
occurrence_render();
occurrence_render(int id, int containerID, int containerOffsetY, 
                  int containerOffsetX, int eventOffsetY, int windowContainerOffsetY, float scale, std::vector<float> timeStamps,
                  std::vector<eventType> event);
~occurrence_render();
//getters
std::vector<event_render> getEvents();
int getId();
//update
void updatePosition(int newScale, int containerOffsetY, int offsetX, int offsetY);
//draw
void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

