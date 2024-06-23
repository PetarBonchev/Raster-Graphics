#pragma once
#include "Session.h"

class SessionManager
{
public:

	SessionManager(const SessionManager&) = delete;
	SessionManager& operator=(const SessionManager&) = delete;

	static SessionManager& getInstance();

	void addSession();
	void goToSession(unsigned index);
	Session* getCurrentSession();
	unsigned getSessionsCount()const;
private:
	SessionManager() = default;
	~SessionManager() = default;

	Vector<Polymorphic_Ptr<Session>> sessions;
	unsigned currentSession = 0;
};