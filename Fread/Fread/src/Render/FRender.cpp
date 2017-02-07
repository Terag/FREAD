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

 #include "Render/FRender.hpp"

FRender::FRender(std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _pop_queue_core, 
                 std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _push_queue_core, 
                 float absoluteTime):
                _m_pop_queue_core(_pop_queue_core), 
                _m_push_queue_core(_push_queue_core), 
                absoluteTime(absoluteTime)
{}

FRender::~FRender()
{}

 std::vector<container_render> FRender::transformContainer(std::vector<std::shared_ptr<FContainer>> listContainer, scale scale) 
{
    std::vector<container_render> renderContainers;
    for(unsigned int i = 0; i < listContainer.size(); i++) 
    {
        container_render container(listContainer[i]->getId(), listContainer[i]->getAlias(), 1000, scale.getContainerOffsetX(),scale.getContainerOffsetY(),scale.getWindowContainerOffsetY());
        std::vector <patternStruct> listPattern = listContainer[i]->getPatternList();
        for (unsigned int j = 0; j < listPattern.size(); j ++) {
            FPattern fPat = viewPatternById(listPattern[j].id);
            occurrence_render occ(
                                  fPat.getId(),listPattern[j].contId,
                                  scale.getContainerOffsetY(), scale.getContainerOffsetX(),
                                  scale.getEventOffsetY(), scale.getWindowContainerOffsetY(),scale.getScale(), fPat.getMeanTimeStamps(),
                                  fPat.getEventTypes()
                                  );
            container.addOccurrence(occ);
        }
        renderContainers.push_back(container);
    }
    return renderContainers;
}
 
 FPattern FRender::viewPatternById(int id) 
{
    ask_for_pattern(id);
    auto msg = *( _m_pop_queue_core->wait_and_pop() );
    std::cout << "RENDER <<< PATTERN FROM CORE" << std::endl;

    auto received = std::static_pointer_cast<FPattern>( msg->getContent() ); 
    FPattern content = *received;
    std::cout << "RENDER <<< PATTERN RECEIVED FROM CORE" << std::endl;
    return content;
 }
 
  FOccurrence FRender::viewOccurenceById(int patternId,int occId) 
{
    ask_for_occurrence( patternId,  occId);
    auto msg = *( _m_pop_queue_core->wait_and_pop() );
        std::cout << "RENDER <<< OCCURENCE FROM CORE" << std::endl;

    auto received = std::static_pointer_cast<FOccurrence>( msg->getContent() ); 
     
    FOccurrence content = *received;
     
     return content;
  
 }
  std::vector<int> FRender::getContainerID(){
      ask_for_list_container();
        
    auto msg = *( _m_pop_queue_core->wait_and_pop() );
    std::cout << "RENDER <<< LIST_ID FROM CORE" << std::endl;

    auto received = std::static_pointer_cast<std::vector<int>>( msg->getContent() ); 
     
    std::vector<int> content = *received;
     
     return content;
      
  }
  std::vector<container_render> FRender::ContainerToDrawBetween(std::vector<int>listContainer,float begin_time, float end_time, scale scale,std::vector<pattern_render> listPatterns)
  {
    std::vector<container_render> renderContainers;
    for( unsigned int i = 0; i < listContainer.size(); i++) {
            ask_for_timestamps(listContainer[i] ,  begin_time,  end_time);
            auto msg_timestamps = *( _m_pop_queue_core->wait_and_pop());
            std::cout << "RENDER <<< TIMESTAMPS FROM CORE" << std::endl;

            auto received_timestamps = std::static_pointer_cast< std::vector<patternStruct> >( msg_timestamps->getContent() ); 
            std::cout << "RENDER <<< TIMESTAMPS RECEIVED" << std::endl;
            std::vector<patternStruct> listPattern = *received_timestamps;
            std::cout << "RENDER <<< TIMESTAMPS TAKEN" << std::endl;

            ask_for_container(listContainer[i]);
            auto msg_container = *( _m_pop_queue_core->wait_and_pop());
            std::cout << "RENDER <<< CONTAINER FROM CORE" << std::endl;

            auto received_container = std::static_pointer_cast< FContainer >( msg_container->getContent() ); 
            std::cout << "RENDER <<< CONTAINER RECEIVED" << std::endl;
            FContainer content = *received_container;
            std::cout << "RENDER <<< CONTAINER TAKEN" << std::endl;

            //content.setPatternList( listPattern );

            container_render container(content.getId(), content.getAlias(), 1000, scale.getContainerOffsetX(),scale.getContainerOffsetY(),scale.getWindowContainerOffsetY());
            std::cout << "RENDER <<< CONTAINER_RENDER CREATE" << std::endl;
            
     
        for (unsigned int j = 0; j < listPattern.size(); j ++) {
            if( isInPatternsToRender(i, listPatterns) ){
                for(auto it = listPatterns.begin(); it != listPatterns.end(); ++it){
                    if( it->getId() == i ){
                        listPatterns.push_back( *it );
                        break;
                    }
                }
            }else{
                FPattern fPat = viewPatternById(listPattern[j].id);
            
                occurrence_render occ(
                                      fPat.getId(),listPattern[j].contId,
                                      scale.getContainerOffsetY(), scale.getContainerOffsetX(),
                                      scale.getEventOffsetY(), scale.getWindowContainerOffsetY(),scale.getScale(), fPat.getMeanTimeStamps(),
                                      fPat.getEventTypes()
                                      );
                container.addOccurrence(occ);
                pattern_render pat(fPat.getId(),fPat.getMeanTimeStamps(),occ);
                listPatterns.push_back(pat);
            
        }
        renderContainers.push_back(container);
       
       }
       return renderContainers;
       
  }
}

bool FRender::isInPatternsToRender(int i , std::vector< pattern_render > my_vector){
    for(auto it = my_vector.begin(); it != my_vector.end(); ++it){
        if( it->getId() == i ){
            return true;
        }
    }
    return false;
}
 
float FRender::getAbsoluteTime() 
{
    return absoluteTime;
} 
 
void FRender::thr_FRender() {

    //sfml antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //define the window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "FREAD",sf::Style::Default, settings);
    int sizeX =window.getSize().x;
    int sizeY =window.getSize().y;
      
    //transform a list of FContainers in a list of container_renders + define the scaling 
    std::vector<pattern_render> listPatterns;
    std::vector<int> listContainer = getContainerID() ;
    int nbContainer = listContainer.size();
    
    scale scale(absoluteTime, nbContainer, (sizeX - sizeX/10), sizeX/10, sizeX/20 ,(sizeY*3)/100, sizeY/100, (sizeY*45)/100);

    std::vector<container_render> renderContainers = ContainerToDrawBetween(listContainer,0.0,0.5,scale,listPatterns);
    float barreSize =(sizeX - sizeX/10);
    sf::RectangleShape barre(sf::Vector2f(barreSize, 10));
    barre.setPosition(100,sizeY-20);
    barre.setFillColor(sf::Color(131,131,131));

    sf::RectangleShape barre2(sf::Vector2f(barreSize*(0.5)/absoluteTime, 10));
    barre2.setPosition(100,sizeY-20);
    barre2.setFillColor(sf::Color(200,200,200));
    
    float startclic =0.0 ;
    bool clic = false;
    
    // window loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {    
                    window.close();
            
                }
                if (event.type == sf::Event::Resized)
                {
                    std::cout << "new width: " << event.size.width << std::endl;
                    std::cout << "new height: " << event.size.height << std::endl;
                    sizeX =window.getSize().x;
                    sizeY =window.getSize().y;
                    scale.updateScale((sizeX - sizeX/10), sizeX/10, sizeX/20 ,(sizeY*3)/100, sizeY/100, (sizeY*45)/100,nbContainer);       
                }
                if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (barre2.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                            {
                                clic = true;
                                startclic=(barre2.getPosition().x);
                            }
                            else if (barre.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                            {
                                // std::cout << "the barre button was pressed" << std::endl;
                            }
                        }
                    }
                if (event.type == sf::Event::MouseMoved and clic)
                { 
                    if (event.mouseMove.x-startclic/2<1000 and event.mouseMove.x-startclic/2>100)
                    {
                    barre2.setPosition(event.mouseMove.x-startclic/2,sizeY-20);
                    float timeS =((barreSize)-(barre2.getPosition().x-100))/barreSize*absoluteTime;
                    renderContainers = ContainerToDrawBetween(listContainer,timeS,timeS+0.5,scale,listPatterns);
                    
                    
                    }

                }     
                if (event.type == sf::Event::MouseButtonReleased and clic)
                {
                    clic = false;
                }
            }
            
        window.clear(sf::Color(255,255,255));
        scale.draw(window);
        
        for (unsigned int i = 0; i < renderContainers.size(); i++) 
        {   
            window.draw(renderContainers[i]);
        }
        
        drawPatterns(listPatterns,sizeX,sizeY,window);
        window.draw(barre);
        window.draw(barre2);
        window.display();
    }
    
} 
void FRender::drawPatterns(std::vector<pattern_render> listPatterns,int sizeX, int sizeY,sf::RenderTarget& window) {
    int drawX = sizeX - sizeX/10 ;
    int drawY = sizeY*45/100 - sizeY/20;
    int radius;
    if (drawX/10>drawY/4) {radius =drawY/4;}
    else {radius = drawX/10;}
    for (unsigned int i=0; i<listPatterns.size(); i++) {
        listPatterns[i].SetPosition((2*radius+radius/5)*(i+1),radius + sizeY/20,radius);
        window.draw(listPatterns[i]);
        
    }
    
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR AN OCCURRENCE BY ITS patternId AND ITS OWN occId
 *
 */
void FRender::ask_for_occurrence(int patternId, int occId){
  std::pair<int, int> occurrence(patternId, occId);
  std::shared_ptr< std::pair<int, int> > occurrence_send = std::make_shared< std::pair<int, int> >(occurrence);
  auto content_send = std::static_pointer_cast<void>( occurrence_send );
  FMessages msg_send(OCCURRENCE, content_send);
  std::cout << "RENDER >>> SEND OCCURRENCE " << patternId << ":" << occId << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR ALL THE PATTERN IN THE CONTAINER contId BETWEEN begin_time AND end_time
 *
 */
void FRender::ask_for_timestamps(int contId, float begin_time, float end_time){
  patternStruct timestamp(-1, contId, begin_time, end_time);
  auto timestamps_send = std::make_shared< patternStruct >(timestamp);
  auto content_send = std::static_pointer_cast<void>( timestamps_send );
  FMessages msg_send(TIMESTAMP, content_send);
  std::cout << "RENDER >>> SEND TIMESTAMPS ON CONTAINER : " << contId << " FROM : " << begin_time << " UNTIL : " << end_time << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR A PATTERN BY ITS patternId
 *
 */
void FRender::ask_for_pattern(int patternId){
  std::shared_ptr<int> pattern_send = std::make_shared<int>( patternId );
  auto content_send = std::static_pointer_cast<void>( pattern_send );
  FMessages msg_send(PATTERN, content_send);
  std::cout << "RENDER >>> SEND PATTERN : " << patternId << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR A CONTAINER BY ITS contId
 *
 */
void FRender::ask_for_container(int contId){
  std::shared_ptr<int> container_send= std::make_shared<int>( contId );
  auto content_send = std::static_pointer_cast<void>( container_send );
  FMessages msg_send(CONTAINER, content_send);
  std::cout << "RENDER >>> SEND CONTAINER : " << contId << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}
/*
 *
 * METHODS USED TO ASK THE CORE FOR A CONTAINER LIST BY ITS contId
 *
 */
void FRender::ask_for_list_container(){
    std::shared_ptr<void> list_ask;
  auto content_send = list_ask;
  FMessages msg_send(LIST_ID, list_ask);
  std::cout << "RENDER >>> SEND ASK LIST_ID  TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}
/*
 *
 * METHODS USED TO GET A MESSAGE FROM THE CORE
 *
 */
void FRender::receive_message(){

  std::shared_ptr<FMessages> msg = *( _m_pop_queue_core->try_pop() );
  if( msg.use_count() != 0 && msg != NULL){
      switch(msg->getHeader()){
          case(START):
          {
              std::cout << "CORE >>> START MESSAGE RECEIVED FROM CORE" << std::endl;
              break;
          }
          case(INITDONE):
          {
              std::cout << "CORE >>> INITDONE MESSAGE RECEIVED FROM CORE" << std::endl;
              break;
          }
          case(CONTAINER):
          {
              std::cout << "CORE >>> CONTAINER MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< FContainer > received = std::static_pointer_cast<FContainer>( msg->getContent() );
              break;
          }
          case(PATTERN):
          {
              std::cout << "CORE >>> PATTERN MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< FPattern > received = std::static_pointer_cast<FPattern>( msg->getContent() );
              break;
          }
          case(TIMESTAMP):
          {
              std::cout << "CORE >>> TIMESTAMP MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< std::vector< patternStruct > > received = std::static_pointer_cast< std::vector<patternStruct> >( msg->getContent() );
              break;
          }
          case(OCCURRENCE):
          {
              std::cout << "CORE >>> OCCURRENCE MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< FOccurrence > received = std::static_pointer_cast<FOccurrence>( msg->getContent() );
              break;
          }
          default:

          break;
      } /* switch */
    } /* if */
} /* void */


void render_thread( std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _pop_queue_core, 
                    std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _push_queue_core, 
                    float absoluteTime){

  FRender render(_pop_queue_core, _push_queue_core, absoluteTime);

  std::cout << "start FRender" << std::endl;

  render.thr_FRender();
}