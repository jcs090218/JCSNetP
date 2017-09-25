/**
 * $File: ServerHandler.cpp $
 * $Date: 2017-04-17 22:27:42 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../ServerExample.h"


ServerHandler::~ServerHandler()
{

}

// Function trigger when the message sent, use for the logging.
void ServerHandler::MessageSent(JCSNetP_IoSession& session/*, Object messag */)
{

}

// Error handle.
void ServerHandler::ExceptionCaught(JCSNetP_IoSession& session/*, Throwable cause */)
{

}

// Function trigger if the session is opened.
void ServerHandler::SessionOpened(JCSNetP_IoSession& session)
{

}

// Function trigger if the session were closed.
void ServerHandler::SessionClosed(JCSNetP_IoSession& session)
{

}

// Function trigger if the message received.
void ServerHandler::MessageReceived(JCSNetP_IoSession& session/*, Object message */)
{

}

// Function trigger in when the session were idle.
void ServerHandler::SessionIdle(const JCSNetP_IoSession& session/*, final IdleStatus status*/)
{

}
