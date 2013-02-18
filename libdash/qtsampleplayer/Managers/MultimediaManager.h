/*
 * MultimediaManager.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef QTSAMPLEPLAYER_MANAGERS_MULTIMEDIAMANAGER_H_
#define QTSAMPLEPLAYER_MANAGERS_MULTIMEDIAMANAGER_H_

#include "IMPD.h"
#include "MultimediaStream.h"
#include "../libdashframework/Adaptation/IAdaptationLogic.h"
#include "../libdashframework/Buffer/IBufferObserver.h"
#include "../Renderer/QTGLRenderer.h"

namespace sampleplayer
{
    namespace managers
    {
        class MultimediaManager : public IStreamObserver
        {
            public:
                MultimediaManager           (renderer::QTGLRenderer *videoelement);
                virtual ~MultimediaManager  ();

                bool                Init    (const std::string& url);
                void                Start   ();
                void                Stop    ();
                dash::mpd::IMPD*    GetMPD  ();

                void OnVideoFrameAvailable  (const QImage& image, dash::mpd::IAdaptationSet *adaptationSet);
                void OnAudioSampleAvailable ();

                bool SetVideoAdaptationSet      (dash::mpd::IAdaptationSet *adaptationSet);
                bool SetAudioAdaptationSet      (dash::mpd::IAdaptationSet *adaptationSet);

                bool SetVideoRepresenation      (dash::mpd::IRepresentation *representation);
                bool SetAudioRepresenation      (dash::mpd::IRepresentation *representation);
               
                bool SetVideoAdaptationLogic    (libdash::framework::adaptation::LogicType type);
                bool SetAudioAdaptationLogic    (libdash::framework::adaptation::LogicType type);

                void AttachVideoBufferObserver  (libdash::framework::buffer::IBufferObserver *videoBufferObserver);
                void AttachAudioBufferObserver  (libdash::framework::buffer::IBufferObserver *audioBufferObserver);

                void NotifyVideoObservers       ();
                void NotifyAudioObservers       ();

                void NotifyVideoBufferObservers ();
                void NotifyAudioBufferObservers ();

            private:
                dash::IDASHManager                                          *manager;
                dash::mpd::IMPD                                             *mpd;
                renderer::QTGLRenderer                                      *videoelement;
                dash::mpd::IAdaptationSet                                   *videoAdaptationSet;
                libdash::framework::adaptation::IAdaptationLogic            *videoLogic;
                MultimediaStream                                            *videoStream;
                std::vector<libdash::framework::buffer::IBufferObserver* >  videoBufferObservers;
                bool                                                        run;
        };
    }
}

#endif /* QTSAMPLEPLAYER_MANAGERS_MULTIMEDIAMANAGER_H_ */