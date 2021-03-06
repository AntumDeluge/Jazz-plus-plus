//*****************************************************************************
// The JAZZ++ Midi Sequencer
//
// Copyright (C) 1994-2000 Andreas Voss and Per Sigmond, all rights reserved.
// Modifications Copyright (C) 2004 Patrick Earl
// Modifications Copyright (C) 2008-2010 Peter J. Stieber
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//*****************************************************************************

#pragma once

#include <sys/soundcard.h>
// in oss/free (from kernel 2.0.29) the following is not implemented
// but this works for oss/linux for 2.0.29
// #ifndef SNDCTL_SEQ_GETTIME
// #define SNDCTL_SEQ_GETTIME  _IOR ('Q',19, int)
// #endif

#include <sys/time.h>

#include "Events.h"
#include "Player.h"
#include "Audio.h"


class JZSample;
class JZAudioListener;

class JZAudioPlayer : public JZSeq2Player
{
  friend class JZAudioListener;

  public:

    JZAudioPlayer(JZSong *song);

    virtual ~JZAudioPlayer();

    int LoadSamples(const char *filename);

    virtual void Notify();

    virtual void StartPlay(int Clock, int LoopClock = 0, int Continue = 0);

    virtual void StopPlay();

    virtual void StartAudio();

    virtual int IsIsInstalled()
    {
      return mInstalled && JZSeq2Player::IsInstalled();
    }

    virtual bool GetAudioEnabled() const
    {
      return mAudioEnabled;
    }

    virtual void SetAudioEnabled(bool AudioEnabled)
    {
      mAudioEnabled = AudioEnabled;
    }

    virtual void ListenAudio(int key, int start_stop_mode = 1);

    virtual void ListenAudio(JZSample &spl, int fr_smpl, int to_smpl);

    virtual bool IsListening() const
    {
      return mpListener != 0;
    }

    virtual int GetListenerPlayPosition();

    // for recording
    int RecordMode() const;

    int PlaybackMode() const
    {
      return !RecordMode() || mCanDuplex;
    }

  private:

    // If true can do full duplex record/play.
    int mCanDuplex;

    int WriteSamples();
    void ReadSamples();
    void MidiSync();
    void OpenDsp();

    void CloseDsp(bool Reset);

    int dev;
    bool mInstalled;

    int midi_clock;
    int audio_bytes;
    int midi_speed;  // start speed in bpm
    int curr_speed;  // actual speed in bpm

    // False means MIDI only.
    int mAudioEnabled;

    JZAudioListener* mpListener;
    JZAudioRecordBuffer recbuffers;

    // Needed by buggy audio driver ...
    int force_read;
};
