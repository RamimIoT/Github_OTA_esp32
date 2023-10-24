/**
 * HTTPUpdate--->GithubOTAUpdate || HTTP_UPDATE--->GithubOTA_UPDATE || httpUpdate--->githubOTAUpdate
 * @file GithubOTAUpdate.h based on HTTPUpdate.h 
 * @date 24.10.2023
 * @author Sakiul Mowla Ramim
 *
 * Copyright (c) 2015 Markus Sattler. All rights reserved.
 * This file is part of the ESP32 Http Updater.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef ___GithubOTA_UPDATE_H___
#define ___GithubOTA_UPDATE_H___

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <Update.h>

/// note we use HTTP client errors too so we start at 100
#define HTTP_UE_TOO_LESS_SPACE              (-100)
#define HTTP_UE_SERVER_NOT_REPORT_SIZE      (-101)
#define HTTP_UE_SERVER_FILE_NOT_FOUND       (-102)
#define HTTP_UE_SERVER_FORBIDDEN            (-103)
#define HTTP_UE_SERVER_WRONG_HTTP_CODE      (-104)
#define HTTP_UE_SERVER_FAULTY_MD5           (-105)
#define HTTP_UE_BIN_VERIFY_HEADER_FAILED    (-106)
#define HTTP_UE_BIN_FOR_WRONG_FLASH         (-107)
#define HTTP_UE_NO_PARTITION                (-108)

enum GithubOTAUpdateResult {
    GithubOTA_UPDATE_FAILED,
    GithubOTA_UPDATE_NO_UPDATES,
    GithubOTA_UPDATE_OK
};

typedef GithubOTAUpdateResult t_githubOTAUpdate_return; // backward compatibility

using GithubOTAUpdateStartCB = std::function<void()>;
using GithubOTAUpdateRequestCB = std::function<void(HTTPClient*)>;
using GithubOTAUpdateEndCB = std::function<void()>;
using GithubOTAUpdateErrorCB = std::function<void(int)>;
using GithubOTAUpdateProgressCB = std::function<void(int, int)>;

class GithubOTAUpdate
{
public:
    GithubOTAUpdate(void);
    GithubOTAUpdate(int httpClientTimeout);
    ~GithubOTAUpdate(void);

    void rebootOnUpdate(bool reboot)
    {
        _rebootOnUpdate = reboot;
    }
    
    /**
      * set redirect follow mode. See `followRedirects_t` enum for avaliable modes.
      * @param follow
      */
    void setFollowRedirects(followRedirects_t follow)
    {
        _followRedirects = follow;
    }

    void setLedPin(int ledPin = -1, uint8_t ledOn = HIGH)
    {
        _ledPin = ledPin;
        _ledOn = ledOn;
    }


    // void addGitToken(const String& name, const String& value, bool first = false, bool replace = true);

    void addGitToken(const String& githubToken){
      _githubToken = githubToken;
    }

    



    t_githubOTAUpdate_return update(WiFiClient& client, const String& url, const String& currentVersion = "", GithubOTAUpdateRequestCB requestCB = NULL);

    t_githubOTAUpdate_return update(WiFiClient& client, const String& host, uint16_t port, const String& uri = "/",
                               const String& currentVersion = "", GithubOTAUpdateRequestCB requestCB = NULL);

    t_githubOTAUpdate_return updateSpiffs(WiFiClient& client, const String& url, const String& currentVersion = "", GithubOTAUpdateRequestCB requestCB = NULL);

    t_githubOTAUpdate_return update(HTTPClient& httpClient,
                               const String& currentVersion = "", 
                               GithubOTAUpdateRequestCB requestCB = NULL);

    t_githubOTAUpdate_return updateSpiffs(HTTPClient &httpClient, const String &currentVersion = "", GithubOTAUpdateRequestCB requestCB = NULL);

    // Notification callbacks
    void onStart(GithubOTAUpdateStartCB cbOnStart)          { _cbStart = cbOnStart; }
    void onEnd(GithubOTAUpdateEndCB cbOnEnd)                { _cbEnd = cbOnEnd; }
    void onError(GithubOTAUpdateErrorCB cbOnError)          { _cbError = cbOnError; }
    void onProgress(GithubOTAUpdateProgressCB cbOnProgress) { _cbProgress = cbOnProgress; }

    int getLastError(void);
    String getLastErrorString(void);

protected:
    t_githubOTAUpdate_return handleUpdate(HTTPClient& http, const String& currentVersion, bool spiffs = false, GithubOTAUpdateRequestCB requestCB = NULL);
    bool runUpdate(Stream& in, uint32_t size, String md5, int command = U_FLASH);

    // Set the error and potentially use a CB to notify the application
    void _setLastError(int err) {
        _lastError = err;
        if (_cbError) {
            _cbError(err);
        }
    }
    int _lastError;
    bool _rebootOnUpdate = true;
private:
    int _httpClientTimeout;
    followRedirects_t _followRedirects;

    // Callbacks
    GithubOTAUpdateStartCB    _cbStart;
    GithubOTAUpdateEndCB      _cbEnd;
    GithubOTAUpdateErrorCB    _cbError;
    GithubOTAUpdateProgressCB _cbProgress;

    int _ledPin;
    uint8_t _ledOn;
    String _githubToken;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_HTTPUPDATE)
extern GithubOTAUpdate githubOTAUpdate;
#endif

#endif /* ___GithubOTA_UPDATE_H___ */
