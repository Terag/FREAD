/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FRender.hpp
 * Author: Emma et Jerome 
 *
 * Created on 30 janvier 2017, 17:15
 */

#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Render/container_render.hpp"
#include "Render/scale.hpp"
#include "Render/pattern_render.hpp"

#include "FQueue.hpp" 
#include "FMessages.hpp" 
#include "Core/FMap.hpp" 
#include "FThread_guard.hpp"
#include "FObjet.hpp"
#include "FOccurrence.hpp"
#include "FPattern.hpp"
#include "FContainer.hpp"
#include "Core/FCore.hpp"

class FRender {

private: 
    bool awake;
    std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _m_pop_queue_core;
    std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _m_push_queue_core;
    float absoluteTime; 

public: 
    FRender(std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _pop_queue_core,
            std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _push_queue_core,
            float absoluteTime);
    ~FRender();   
    std::vector<container_render> transformContainer(std::vector<std::shared_ptr<FContainer>> listContainer, scale scale);
    void thr_FRender();
    float getAbsoluteTime();
    void drawPatterns(std::vector<pattern_render> listPatterns,int sizeX, int sizeY,sf::RenderTarget& window);
    FPattern viewPatternById(int id) ;
    FOccurrence viewOccurenceById(int patternId,int occId) ;
    std::vector<container_render> ContainerToDrawBetween(std::vector<int>listContainer,float begin_time, float end_time, scale scale,std::vector<pattern_render> listPatterns);
    std::vector<int> getContainerID();
    
    void ask_for_occurrence(int patternId, int occId);
    void ask_for_timestamps(int contId, float begin_time, float end_time);
    void ask_for_pattern(int patternId);
    void ask_for_container(int contId);
    void ask_for_list_container();
    void receive_message();
};

void render_thread( std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _pop_queue_core, 
                    std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _push_queue_core, 
                    float absoluteTime);