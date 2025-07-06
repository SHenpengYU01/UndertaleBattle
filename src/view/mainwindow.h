#pragma once

#include "../headers.h"
#include "../common/property_id.h"
#include "../common/frame.h"
#include <any>

class MainWindow : public sf::RenderWindow{
private:
    std::function<void(int)> m_next_command;


public:
    MainWindow();
    MainWindow(const MainWindow&) = delete;

    MainWindow(sf::VideoMode mode, char const* title, unsigned int style);
	MainWindow& operator=(const MainWindow&) = delete;

    void SetNextCommand(std::function<void(int)>&& pn) noexcept{
        this->m_next_command = std::move(pn);
    }

    //notification
	PropertyNotification GetNotification(int nf_id);


};