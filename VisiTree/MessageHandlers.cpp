#include "StdAfx.h"
#include "MessageHandlers.h"

bool DefaultMessageHandler::Handle(LPMSG msg)
{
	TranslateMessage(msg);
	DispatchMessage(msg);
	return true;
}

bool DialogMessageHandler::Handle(LPMSG msg)
{
	return IsDialogMessage(m_wnd, msg);
}

CompositeMessageHandler::~CompositeMessageHandler()
{
#if _MSC_VER > 1200
	for (auto x : m_handlers)
	{
		delete x;
	}
#else
	for (std::list<AbstractMessageHandler *>::iterator it = m_handlers.begin();
		 it != m_handlers.end();
		 it++)
	{
		AbstractMessageHandler *handler = *it;
		delete handler;
	}
#endif
	m_handlers.clear();
}

bool CompositeMessageHandler::Handle(LPMSG msg)
{
#if _MSC_VER > 1200
	for (auto x : m_handlers)
	{
		if (x->Handle(msg))
		{
			return true;
		}
	}
#else
	for (std::list<AbstractMessageHandler *>::iterator it = m_handlers.begin();
		 it != m_handlers.end();
		 it++)
	{
		AbstractMessageHandler *handler = *it;
		if (handler->Handle(msg))
		{
			return true;
		}
	}
#endif
	return false;
}

void CompositeMessageHandler::Add(AbstractMessageHandler *handler)
{
	m_handlers.push_front(handler);
}
