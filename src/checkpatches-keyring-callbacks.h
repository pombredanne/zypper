/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zmd/backend/KeyRingCallbacks.cc
 *
 */
#ifndef CHECKPATCHES_KEYRINGCALLBACKS_H
#define CHECKPATCHES_KEYRINGCALLBACKS_H

#include "zypp/ZYppCallbacks.h"
#include "zypp/Pathname.h"
#include "zypp/KeyRing.h"
#include "zypp/Digest.h"

///////////////////////////////////////////////////////////////////
namespace zypp {
///////////////////////////////////////////////////////////////////


    // read callback answer
    //   can either be '0\n' -> false
    //   or '1\n' -> true
    // reads characters from stdin until newline. Defaults to 'false'
    static bool
        readCallbackAnswer()
    {
      // bnc #398530
      return false;
    }

    ///////////////////////////////////////////////////////////////////
    // KeyRingReceive
    ///////////////////////////////////////////////////////////////////
    struct KeyRingReceive : public zypp::callback::ReceiveReport<zypp::KeyRingReport>
    {
      virtual bool askUserToAcceptUnsignedFile( const std::string &file )
      {
        return readCallbackAnswer();
      }
      virtual bool askUserToAcceptUnknownKey( const std::string &/*file*/, const std::string &/*id*/ )
      {
        return readCallbackAnswer();
      }
      virtual bool askUserToTrustKey( const PublicKey &key )
      {
        return readCallbackAnswer();
      }
      virtual bool askUserToAcceptVerificationFailed( const std::string &file, const PublicKey &key )
      {
        return readCallbackAnswer();
      }
    };


    struct DigestReceive : public zypp::callback::ReceiveReport<zypp::DigestReport>
    {
      virtual bool askUserToAcceptNoDigest( const zypp::Pathname &file )
      {
        return readCallbackAnswer();
      }
      virtual bool askUserToAccepUnknownDigest( const Pathname &file, const std::string &name )
      {
        return readCallbackAnswer();
      }
      virtual bool askUserToAcceptWrongDigest( const Pathname &file, const std::string &requested, const std::string &found )
      {
        return readCallbackAnswer();
      }
    };

    ///////////////////////////////////////////////////////////////////
}; // namespace zypp
///////////////////////////////////////////////////////////////////

class KeyRingCallbacks {

  private:
    zypp::KeyRingReceive _keyRingReport;

  public:
    KeyRingCallbacks()
    {
      _keyRingReport.connect();
    }

    ~KeyRingCallbacks()
    {
      _keyRingReport.disconnect();
    }

};

class DigestCallbacks {

  private:
    zypp::DigestReceive _digestReport;

  public:
    DigestCallbacks()
    {
      _digestReport.connect();
    }

    ~DigestCallbacks()
    {
      _digestReport.disconnect();
    }

};

#endif // CHECKPATCHES_KEYRINGCALLBACKS_H