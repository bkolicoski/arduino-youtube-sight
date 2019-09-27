/*
    YouTube Sight - Arduino library for using YouTube Sight service at https://tools.tastethecode.com/youtube-sight

    Author: Blagojce Kolicoski - bkolicoski@gmail.com
    https://www.youtube.com/tastethecode

    This library is provided for free without any warranty.

    A lot of the library is inspired by the work of Brian Lough from the Arduino YouTube API library
    https://github.com/witnessmenow/arduino-youtube-api     
*/

#ifndef YouTubeSight_h
#define YouTubeSight_h

#include "Arduino.h"
#include "Client.h"

#define YOUTUBE_SIGHT_URL "tools.tastethecode.com"
#define TIMEOUT 1500

struct channelStatistics {
    String views;
    String subscribers_gained;
    String subscribers_lost;
    String subscribers_count;
    String estimated_minutes_watched;
    String average_view_duration;
};

class YouTubeSight
{
    public:
        YouTubeSight(String guid, Client &client);
        channelStatistics channelStats;
        bool getData();
        bool _debug = false;

    private:
        String _guid;
        Client *client;
        String getValue(String data, char separator, int index);
};

#endif
