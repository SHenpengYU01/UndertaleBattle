#include "window.h"
#include "../common/property_id.h"
#include "../common/frame.h"


MainWindow::MainWindow(){
    this->setFramerateLimit(60);
}


PropertyNotification MainWindow::GetNotification(int nf_id){
    switch(nf_id){
    case PROP_ID::HEALTH:{
        return [this](uint32_t id)->void{
            switch (id) {
                case PROP_ID::HEALTH:
                    this->draw();
                    
                    break;
                default:
                    break;
            }
        };
    }
    }
}

void MainWindow::HandleInput(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->m_next_command(CMD_ID::LEFT);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->m_next_command(CMD_ID::RIGHT);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        this->m_next_command(CMD_ID::UP);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        this->m_next_command(CMD_ID::DOWN);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        this->m_next_command(CMD_ID::Z);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
        this->m_next_command(CMD_ID::X);
    }
}
