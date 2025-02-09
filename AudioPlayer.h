/* mbed Microcontroller Library
 * Copyright (c) 2017-2017 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "mbed.h"
#include "AudioStream.h"

//#define DUMP_DATA

struct audio_buffer_t;

class AudioPlayer : private NonCopyable<AudioPlayer> {

public:

    AudioPlayer(PwmOut *mono);

    bool play(File *file);

    void stop();

    ~AudioPlayer();
#ifdef DUMP_DATA	
   for  dumping data 
   static const size_t _data_max = 32000;
   float _data[_data_max];
   short _data_n; 
#endif  

protected:
    void play_error();

    Ticker _ticker;
    EventFlags _flags;
    uint32_t _frequency;
    //AnalogOut *_mono;
    PwmOut *_mono;
    audio_buffer_t *_used_bufs;
    audio_buffer_t *_free_bufs;
    audio_buffer_t *_cur_buf;
    uint32_t _cur_pos;
    uint32_t _error_count;

    void _ticker_handler();
    bool _load_next_buf(AudioStream *stream);
    uint16_t _error_tone();

    void _move_buffers2free();

};

#endif
