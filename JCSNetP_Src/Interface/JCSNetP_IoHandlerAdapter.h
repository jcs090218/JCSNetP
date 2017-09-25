#ifndef __JCSNETP_IOHANDLERADAPTER_H__
/**
 * $File: JCSNetP_IoHandlerAdapter.h $
 * $Date: 2017-04-16 03:09:30 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_IOHANDLERADAPTER_H__


NS_JCS_BEGIN

class JCSNetP_IoSession;

/**
 * @class JCSNetP_IoHandlerAdapter
 * @brief Handle packet that are encripted.
 */
class JCSNetP_IoHandlerAdapter
{
public:
    virtual ~JCSNetP_IoHandlerAdapter() { }


    /**
     * @func MessageSent
     * @brief Function trigger when the message sent, use
     * for the logging.
     */
    virtual void MessageSent(
        JCSNetP_IoSession& session/*, 
        Object messag*/) = 0;

    /**
     * @func ExceptionCaught
     * @brief Error handle.
     */
    virtual void ExceptionCaught(
        JCSNetP_IoSession& session/*, 
        Throwable cause*/) = 0;

    /**
     * @func SessionOpened
     * @brief Function trigger if the session is opened.
     */
    virtual void SessionOpened(JCSNetP_IoSession& session) = 0;

    /**
     * @func SessionClosed
     * @brief Function trigger if the session were closed.
     */
    virtual void SessionClosed(JCSNetP_IoSession& session) = 0;

    /**
     * @func MessageReceived
     * @brief Function trigger if the message received.
     * When arrive this function call, the packet were
     * encrypted properly.
     */
    virtual void MessageReceived(
        JCSNetP_IoSession& session/*, 
        Object message */) = 0;

    /**
     * @func SessionIdle
     * @brief Function trigger in when the session were idle.
     * Time are depends on the timeout setting.
     */
    virtual void SessionIdle(
        const JCSNetP_IoSession& session/*, 
        final IdleStatus status*/) = 0;
};

NS_JCS_END
typedef JCSNetP::JCSNetP_IoHandlerAdapter JCSNetP_IoHandlerAdapter;

#endif /* __JCSNETP_IOHANDLERADAPTER_H__ */
