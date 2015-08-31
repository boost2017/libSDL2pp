/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL2PP_MIXER_HH
#define SDL2PP_MIXER_HH

#include <SDL2/SDL_mixer.h>

namespace SDL2pp {

class Chunk;

////////////////////////////////////////////////////////////
/// \brief SDL_mixer's audio mixer
///
/// \ingroup mixer
///
/// \headerfile SDL2pp/Mixer.hh
///
/// This class represents open SDL_mixer audio device. Object
/// of this class must be constructed before creating any
/// SDL2pp:Chunk's.
///
////////////////////////////////////////////////////////////
class Mixer {
public:
	typedef void (*ChannelFinishedHandler)(int); ///< Function type for channel finished callback

private:
	bool open_;

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct a mixer and open an audio device
	///
	/// \param[in] frequency Output sampling frequency in samples
	///                      per second (Hz). You might use
	///                      MIX_DEFAULT_FREQUENCY(22050) since that
	///                      is a good value for most games
	/// \param[in] format Output sample format
	/// \param[in] channels Number of sound channels in output. Set
	///                     to 2 for stereo, 1 for mono. This has
	///                     nothing to do with mixing channels
	/// \param[in] chunksize Bytes used per output sample
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC11
	///
	////////////////////////////////////////////////////////////
	Mixer(int frequency, Uint16 format, int channels, int chunksize);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC12
	///
	////////////////////////////////////////////////////////////
	~Mixer();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Mixer object to move data from
	///
	////////////////////////////////////////////////////////////
	Mixer(Mixer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Mixer object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Mixer& operator=(Mixer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Mixer(const Mixer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Mixer& operator=(const Mixer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Set the number of channels to mix
	///
	/// \param[in] numchans Number of channels to allocate for mixing
	///
	/// \returns The number of channels allocated
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC26
	///
	////////////////////////////////////////////////////////////
	int AllocateChannels(int numchans);

	////////////////////////////////////////////////////////////
	/// \brief Get the number of channels being mixed
	///
	/// \returns The number of channels allocated
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC26
	///
	////////////////////////////////////////////////////////////
	int GetNumChannels() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the mix volume of a channel
	///
	/// \param[in] channel Channel to set mix volume for.
	///                    -1 will set the volume for all allocated
	///                    channels.
	/// \param[in] volume The volume to use from 0 to MIX_MAX_VOLUME(128)
	///
	/// \returns Current volume of the channel. If channel is -1,
	///          the average volume is returned
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC27
	///
	////////////////////////////////////////////////////////////
	int SetVolume(int channel, int volume);

	////////////////////////////////////////////////////////////
	/// \brief Get the mix volume of a channel
	///
	/// \param[in] channel Channel to set mix volume for.
	///                    -1 will return the average volume.
	///
	/// \returns Current volume of the channel. If channel is -1,
	///          the average volume is returned
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC27
	///
	////////////////////////////////////////////////////////////
	int GetVolume(int channel) const;

	////////////////////////////////////////////////////////////
	/// \brief Play loop
	///
	/// \param[in] channel Channel to play on, or -1 for the first
	///                    free unreserved channel
	/// \param[in] chunk Sample to play
	/// \param[in] loops Number of loops, -1 is infinite loops.
	///                  Passing one here plays the sample twice (1 loop).
	///
	/// \returns The channel the sample is played on
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC28
	///
	////////////////////////////////////////////////////////////
	int PlayChannel(int channel, const Chunk& chunk, int loops = 0);

	////////////////////////////////////////////////////////////
	/// \brief Play loop and limit by time
	///
	/// \param[in] channel Channel to play on, or -1 for the first
	///                    free unreserved channel
	/// \param[in] chunk Sample to play
	/// \param[in] loops Number of loops, -1 is infinite loops.
	///                  Passing one here plays the sample twice (1 loop).
	/// \param[in] ticks Millisecond limit to play sample, at most.
	///                  If not enough loops or the sample chunk is not
	///                  long enough, then the sample may stop before
	///                  this timeout occurs. -1 means play forever
	///
	/// \returns The channel the sample is played on
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC29
	///
	////////////////////////////////////////////////////////////
	int PlayChannel(int channel, const Chunk& chunk, int loops, int ticks);

	////////////////////////////////////////////////////////////
	/// \brief Play loop with fade in
	///
	/// \param[in] channel Channel to play on, or -1 for the first
	///                    free unreserved channel
	/// \param[in] chunk Sample to play
	/// \param[in] loops Number of loops, -1 is infinite loops.
	///                  Passing one here plays the sample twice (1 loop).
	/// \param[in] ms Milliseconds of time that the fade-in effect
	///               should take to go from silence to full volume
	///
	/// \returns The channel the sample is played on
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC30
	///
	////////////////////////////////////////////////////////////
	int FadeInChannel(int channel, const Chunk& chunk, int loops, int ms);

	////////////////////////////////////////////////////////////
	/// \brief  loop with fade in and limit by time
	///
	/// \param[in] channel Channel to play on, or -1 for the first
	///                    free unreserved channel
	/// \param[in] chunk Sample to play
	/// \param[in] loops Number of loops, -1 is infinite loops.
	///                  Passing one here plays the sample twice (1 loop).
	/// \param[in] ms Milliseconds of time that the fade-in effect
	///               should take to go from silence to full volume
	/// \param[in] ticks Millisecond limit to play sample, at most.
	///                  If not enough loops or the sample chunk is not
	///                  long enough, then the sample may stop before
	///                  this timeout occurs. -1 means play forever
	///
	/// \returns The channel the sample is played on
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC31
	///
	////////////////////////////////////////////////////////////
	int FadeInChannel(int channel, const Chunk& chunk, int loops, int ms, int ticks);

	////////////////////////////////////////////////////////////
	/// \brief Pause a channel
	///
	/// \param[in] channel Channel to pause on, or -1 for all channels
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC32
	///
	////////////////////////////////////////////////////////////
	void PauseChannel(int channel = -1);

	////////////////////////////////////////////////////////////
	/// \brief Resume a paused channel
	///
	/// \param[in] channel Channel to resume playing, or -1 for all channels
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC33
	///
	////////////////////////////////////////////////////////////
	void ResumeChannel(int channel = -1);

	////////////////////////////////////////////////////////////
	/// \brief Stop playing on a channel
	///
	/// \param[in] channel Channel to stop playing, or -1 for all channels
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC34
	///
	////////////////////////////////////////////////////////////
	void HaltChannel(int channel = -1);

	////////////////////////////////////////////////////////////
	/// \brief Change the timed stoppage of a channel
	///
	/// \param[in] channel Channel to stop playing, or -1 for all channels
	/// \param[in] ticks Millisecons until channel(s) halt playback
	///
	/// \returns Number of channels set to expire. Whether or not they are active
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC35
	///
	////////////////////////////////////////////////////////////
	int ExpireChannel(int channel, int ticks);

	////////////////////////////////////////////////////////////
	/// \brief Stop playing channel after timed fade out
	///
	/// \param[in] channel Channel to fade out, or -1 to fade all channels out
	/// \param[in] ms Milliseconds of time that the fade-out effect should
	///               take to go to silence, starting now
	///
	/// \returns The number of channels set to fade out
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC36
	///
	////////////////////////////////////////////////////////////
	int FadeOutChannel(int channel, int ms);

	////////////////////////////////////////////////////////////
	/// \brief Set callback for when channel finishes playing
	///
	/// \param[in] channel_finished Function to call when any channel
	///                             finishes playback
	///
	/// \note Since Mix_ChannelFinished doesn't take any custom data
	///       pointer, unfortunately there's no safe way of using
	///       std::function here.
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC37
	///
	////////////////////////////////////////////////////////////
	void SetChannelFinishedHandler(ChannelFinishedHandler channel_finished);

	////////////////////////////////////////////////////////////
	/// \brief Get the active playing status of a channel
	///
	/// \param[in] channel Channel to test whether it is playing or not.
	///                    -1 will tell you how many channels are playing
	///
	/// \returns Zero if the channel is not playing. Otherwise if you passed
	///          in -1, the number of channels playing is returned. If you
	///          passed in a specific channel, then 1 is returned if it is
	///          playing.
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC38
	///
	////////////////////////////////////////////////////////////
	int IsChannelPlaying(int channel) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the pause status of a channel
	///
	/// \param[in] channel Channel to test whether it is paused or not.
	///                    -1 will tell you how many channels are playing
	///
	/// \returns Zero if the channel is not paused. Otherwise if you passed
	///          in -1, the number of paused channels is returned. If you
	///          passed in a specific channel, then 1 is returned if it is
	///          paused.
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC39
	///
	////////////////////////////////////////////////////////////
	int IsChannelPaused(int channel) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the fade status of a channel
	///
	/// \param[in] which Channel to get the fade activity status from
	///
	/// \returns The fading status
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC40
	///
	////////////////////////////////////////////////////////////
	Mix_Fading GetChannelFading(int which) const;

	// TODO: Groups
	// TODO: Music
	// TODO: Effects
};

}

#endif
