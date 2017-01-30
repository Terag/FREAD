/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* #include <vector>

#include "Render/FRender.hpp"

FRender::FRender(std::shared_ptr<FQueue<FMessages<FObjet> > > _pop_queue_core, 
                 std::shared_ptr<FQueue<FMessages<FObjet> > > _push_queue_core):
_m_pop_queue_core(_pop_queue_core), _m_push_queue_core(_push_queue_core)
{}

 std::vector<container_render> FRender::transformContainer(std::vector<std::shared_ptr<FContainer>> listContainer, scale) 
{
    std::vector<container_render> renderContainers;
    for(int i = 0; i < listContainer.size(); i++) 
    {
        container_render container = container_render(listContainer[i]->getId(), listContainer[i]->getAlias(), 1000);
        std::vector <FOccurrence> listOccurrences = listContainer[i]->getListeOccurrences();
        for (int j = 0; j < listOccurrences.size(); j ++) {
            occurrence_render occ = occurrence_render(listOccurrences[j].getId(),listOccurrences[j].getContainerId(),
                                                      scale.getContainerOffsetY(), scale.getContainerOffsetX(),
                                                      scale.getEventOffsetY(), scale.getScale(), listOccurrences[j].getTimeStamps(),
                                                      getPatternById(listOccurrences[j].getPatternId()).getEventTypes()
                                                      );
            container.addOccurrence(occ);
        }
        renderContainers.push_back(container);
    }
    return renderContainers;
} 

 FPattern FRender::getPatternById(int id) 
 {
     FPattern pattern = FPattern();
     return FPattern;
 }
 
void FRender::thr_FRender() {
    float absoluteTime; 
    std::vector<std::shared_ptr<FContainer>> listContainer;
    int nbContainer = listContainer.size();
    scale scale = scale(absoluteTime, nbContainer);
    std::vector<container_render> renderContainers = transformContainer(listContainer, scale);
    
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Container and occurrences test",sf::Style::Default, settings);
    
        while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    for (int i = 0; i < renderContainers.size(); i++) {
                       window.draw(renderContainers[i]);
                    }
                    window.close();
            }
            window.clear(sf::Color(255,255,255));
            window.display();
    }
} */

