﻿/* soapTmriOutAccessSoapBindingProxy.h
   Generated by gSOAP 2.8.44 for TmriOutAccess.h

gSOAP XML Web services tools
Copyright (C) 2000-2017, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef soapTmriOutAccessSoapBindingProxy_H
#define soapTmriOutAccessSoapBindingProxy_H
#include "soapH.h"

    class SOAP_CMAC TmriOutAccessSoapBindingProxy : public soap {
      public:
        /// Endpoint URL of service 'TmriOutAccessSoapBindingProxy' (change as needed)
        const char *soap_endpoint;
        /// Variables globally declared in TmriOutAccess.h, if any
        /// Construct a proxy with new managing context
        TmriOutAccessSoapBindingProxy();
        /// Copy constructor
        TmriOutAccessSoapBindingProxy(const TmriOutAccessSoapBindingProxy& rhs);
        /// Construct proxy given a managing context
        TmriOutAccessSoapBindingProxy(const struct soap&);
        /// Constructor taking an endpoint URL
        TmriOutAccessSoapBindingProxy(const char *endpoint);
        /// Constructor taking input and output mode flags for the new managing context
        TmriOutAccessSoapBindingProxy(soap_mode iomode);
        /// Constructor taking endpoint URL and input and output mode flags for the new managing context
        TmriOutAccessSoapBindingProxy(const char *endpoint, soap_mode iomode);
        /// Constructor taking input and output mode flags for the new managing context
        TmriOutAccessSoapBindingProxy(soap_mode imode, soap_mode omode);
        /// Destructor deletes deserialized data and managing context
        virtual ~TmriOutAccessSoapBindingProxy();
        /// Initializer used by constructors
        virtual void TmriOutAccessSoapBindingProxy_init(soap_mode imode, soap_mode omode);
        /// Return a copy that has a new managing context with the same engine state
        virtual TmriOutAccessSoapBindingProxy *copy() SOAP_PURE_VIRTUAL;
        /// Copy assignment
        TmriOutAccessSoapBindingProxy& operator=(const TmriOutAccessSoapBindingProxy&);
        /// Delete all deserialized data (uses soap_destroy() and soap_end())
        virtual void destroy();
        /// Delete all deserialized data and reset to default
        virtual void reset();
        /// Disables and removes SOAP Header from message by setting soap->header = NULL
        virtual void soap_noheader();
        /// Get SOAP Header structure (i.e. soap->header, which is NULL when absent)
        virtual ::SOAP_ENV__Header *soap_header();
        /// Get SOAP Fault structure (i.e. soap->fault, which is NULL when absent)
        virtual ::SOAP_ENV__Fault *soap_fault();
        /// Get SOAP Fault string (NULL when absent)
        virtual const char *soap_fault_string();
        /// Get SOAP Fault detail as string (NULL when absent)
        virtual const char *soap_fault_detail();
        /// Close connection (normally automatic, except for send_X ops)
        virtual int soap_close_socket();
        /// Force close connection (can kill a thread blocked on IO)
        virtual int soap_force_close_socket();
        /// Print fault
        virtual void soap_print_fault(FILE*);
    #ifndef WITH_LEAN
    #ifndef WITH_COMPAT
        /// Print fault to stream
        virtual void soap_stream_fault(std::ostream&);
    #endif
        /// Write fault to buffer
        virtual char *soap_sprint_fault(char *buf, size_t len);
    #endif
        /// Web service operation 'queryObjectOut' (returns SOAP_OK or error code)
//        virtual int queryObjectOut(char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_queryObjectOutReturn)
//        { return this->queryObjectOut(NULL, NULL, _xtlb, _jkxlh, _jkid, _UTF8XmlDoc, _queryObjectOutReturn); }
//        virtual int queryObjectOut(const char *soap_endpoint, const char *soap_action, char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_queryObjectOutReturn);
        virtual int queryObjectOut(char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_queryObjectOutReturn, const char *_remoteServerIp_Char, const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                   , const std::string &_zdbs, const std::string &_dwjgdm)
        { return this->queryObjectOut(NULL, NULL, _xtlb, _jkxlh, _jkid, _UTF8XmlDoc, _queryObjectOutReturn, _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm); }
        virtual int queryObjectOut(const char *soap_endpoint, const char *soap_action, char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_queryObjectOutReturn
                                   , const char *_remoteServerIp_Char, const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                   , const std::string &_zdbs, const std::string &_dwjgdm);

        /// Web service operation 'writeObjectOut' (returns SOAP_OK or error code)
//        virtual int writeObjectOut(char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_writeObjectOutReturn)
//        { return this->writeObjectOut(NULL, NULL, _xtlb, _jkxlh, _jkid, _UTF8XmlDoc, _writeObjectOutReturn); }
//        virtual int writeObjectOut(const char *soap_endpoint, const char *soap_action, char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_writeObjectOutReturn);
        virtual int writeObjectOut(char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_writeObjectOutReturn, const char *_remoteServerIp_Char, const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                   , const std::string &_zdbs, const std::string &_dwjgdm)
        { return this->writeObjectOut(NULL, NULL, _xtlb, _jkxlh, _jkid, _UTF8XmlDoc, _writeObjectOutReturn, _remoteServerIp_Char, _SOAP_ServerPort, _requestUri, _cjbh, _zdbs, _dwjgdm); }
        virtual int writeObjectOut(const char *soap_endpoint, const char *soap_action, char *_xtlb, char *_jkxlh, char *_jkid, char *_UTF8XmlDoc, char *&_writeObjectOutReturn
                                   , const char *_remoteServerIp_Char, const std::string &_SOAP_ServerPort, const std::string &_requestUri, const std::string &_cjbh
                                   , const std::string &_zdbs, const std::string &_dwjgdm);

    };
#endif
