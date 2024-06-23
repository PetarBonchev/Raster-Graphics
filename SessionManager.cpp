#include "SessionManager.h"

SessionManager& SessionManager::getInstance()
{
    static SessionManager instance;
    return instance;
}

void SessionManager::addSession()
{
    Polymorphic_Ptr<Session> newSession(new Session());
    sessions.pushBack(newSession);
    currentSession = sessions.getSize() - 1;
}

void SessionManager::goToSession(unsigned index)
{
    if (index >= sessions.getSize())
        throw std::logic_error("Session ID not found");

    currentSession = index;
}

Session* SessionManager::getCurrentSession()
{
    return sessions[currentSession].get();
}

unsigned SessionManager::getSessionsCount() const
{
    return sessions.getSize();
}
