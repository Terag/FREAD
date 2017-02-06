/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 #include "Render/FRender.hpp"

FRender::FRender(std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _pop_queue_core, 
                 std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _push_queue_core, 
                 float absoluteTime):
                _m_pop_queue_core(_pop_queue_core), 
                _m_push_queue_core(_push_queue_core), 
                absoluteTime(absoluteTime)
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
     auto received = std::static_pointer_cast<FPattern>( msg->getContent() ); 
     FPattern content = *received;
     return content;
 }
 
  FOccurrence FRender::viewOccurenceById(int patternId,int occId) 
{
    ask_for_occurrence( patternId,  occId);
    auto msg = *( _m_pop_queue_core->wait_and_pop() );
    auto received = std::static_pointer_cast<FOccurrence>( msg->getContent() ); 
     
    FOccurrence content = *received;
     
     return content;
  
 }
  std::vector<int> FRender::getContainerID(){
      ask_for_list_container();
    auto msg = *( _m_pop_queue_core->wait_and_pop() );
    auto received = std::static_pointer_cast<std::vector<int>>( msg->getContent() ); 
     
    std::vector<int> content = *received;
     
     return content;
      
  }
  std::vector<container_render> FRender::ContainerToDrawBettewen(int firstContID, int lastContID,float begin_time, float end_time, scale scale,std::vector<pattern_render> listPatterns)
  {
       std::vector<container_render> renderContainers;
       for( int i = firstContID; i < lastContID; i++) {
       ask_for_timestamps( i,  begin_time,  end_time);
       auto msg = *( _m_pop_queue_core->wait_and_pop());
     auto received = std::static_pointer_cast<FContainer>( msg->getContent() ); 
     FContainer content = *received;
     container_render container(content.getId(), content.getAlias(), 1000, scale.getContainerOffsetX(),scale.getContainerOffsetY(),scale.getWindowContainerOffsetY());
        std::vector <patternStruct> listPattern = content.getPatternList();
        for (unsigned int j = 0; j < listPattern.size(); j ++) {
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
 
 float FRender::getAbsoluteTime() 
{
    return absoluteTime;
} 
 
void FRender::thr_FRender() {

    //sfml antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //define the window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Container and occurrences test",sf::Style::Default, settings);
    int sizeX =window.getSize().x;
    int sizeY =window.getSize().y;
      
    //transform a list of FContainers in a list of container_renders + define the scaling 
    std::vector<pattern_render> listPattern;
    std::vector<int> listContainer;
    int nbContainer = listContainer.size();
    scale scale(absoluteTime, nbContainer, (sizeX - sizeX/10), sizeX/10, sizeX/20 ,(sizeY*3)/100, sizeY/100, (sizeY*45)/100);
    std::vector<container_render> renderContainers = ContainerToDrawBettewen(1,nbContainer,0.0,1.0,scale,listPattern);
    
    // window loop
        while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    
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
            }    
            window.clear(sf::Color(255,255,255));
            scale.draw(window);
            for (unsigned int i = 0; i < renderContainers.size(); i++) {
                       window.draw(renderContainers[i]);
                    }
            drawPatterns(listPattern,sizeX,sizeY,window);
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
  std::cout << "PARSER >>> SEND TIMESTAMPS ON CONTAINER : " << contId << " FROM : " << begin_time << " UNTIL : " << end_time << " TO CORE" << std::endl;
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
  std::cout << "RENDER >>> SEND LIST_ID  TO CORE" << std::endl;
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
FRender::~FRender(){
}
//Je ne sais pas comment vous comptez récupérer les messages mais sinon la méthode c'est:
//  auto msg = *( _m_pop_queue_core->try_and_pop() ); on récupère le message sous la forme d'un std::shared_ptr<FMessages>
//  auto received = std::static_pointer_cast<DEFINIR_LE_TYPE_SELON_LE_HEADER>( msg->getContent() ); on récupère un shared_ptr sur l'objet récupéré (dont le type dépend du HEADER : FContainer pour CONTAINER, FPattern pour PATTERN, std::vector<patternStruct> pour TIMESTAMP ou FOccurrence pour OCCURRENCE)
//  auto content = *received; pour avoir le contenu du shared_ptr