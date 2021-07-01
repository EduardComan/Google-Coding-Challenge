#include "videoplayer.h"
#include "videoplaylist.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

std::string VideoPlayer::getCurrentlyPlaying(){
    return currentlyPlaying;
}

void VideoPlayer::setCurrentlyPlaying(std::string nowPlaying) {
    currentlyPlaying = nowPlaying;
}

bool VideoPlayer::getPausedVideo() {
    return pausedVideo;
}

void VideoPlayer::setPausedVideo(bool paused) {
    pausedVideo = paused;
}

void VideoPlayer::showAllVideos() {
    std::cout << "Here's a list of all available videos:" << std::endl;
    std::vector<std::string> titles;
    for (auto i : mVideoLibrary.getVideos())
    {
        titles.push_back(i.getTitle());
    }
    std::sort(titles.begin(), titles.end());
    for (int j = 0; j < titles.size(); ++j)
    {
        for (auto i : mVideoLibrary.getVideos()) {
            if (titles[j] == i.getTitle()) {
                std::cout << "  " << i.getTitle() << " (" << i.getVideoId() << ") " << "[";
                int iteration = 0;
                for (auto j : i.getTags())
                {
                    if (iteration == 0) {
                        iteration++;
                        std::cout << j;
                    }
                    else {
                        std::cout << " " << j;
                    }
                }
                std::cout << "]" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void VideoPlayer::playVideo(const std::string& videoId) {
    bool hasAppeared = false;
    for (auto i : mVideoLibrary.getVideos())
    {
        if (videoId == i.getVideoId())
        {
            hasAppeared = true;
            if (this->getCurrentlyPlaying() != "") {
                std::cout << "Stopping video: " << this->getCurrentlyPlaying() << std::endl;
            }
            std::cout << "Playing video: " << i.getTitle() << std::endl << std::endl;
            this->setCurrentlyPlaying(i.getTitle());
            this->setPausedVideo(false);
            break;
        }
    }

    if (!hasAppeared) {
        //if there isn't a video with that id
        std::cout << "Cannot play video: Video does not exist" << std::endl << std::endl;
    }
}

void VideoPlayer::stopVideo() {
    if (this->getCurrentlyPlaying() == "") {
        //if there is nothing currently playing
        std::cout << "Cannot stop video: No video is currently playing" << std::endl << std::endl;
    }
    else {
        //if the is a video currently playing
        std::cout<<"Stopping video: "<<this->getCurrentlyPlaying()<< std::endl << std::endl;
        this->setCurrentlyPlaying("");
    }
}

void VideoPlayer::playRandomVideo() {
  int randomNumber, n= mVideoLibrary.getVideos().size(), currentIteration=0;
  randomNumber = rand()%n;//generating a number from 0 to n-1

  for (auto i : mVideoLibrary.getVideos())
  {
      if (currentIteration == randomNumber) {

          if (this->getCurrentlyPlaying() != "") {
              std::cout << "Stopping video: " << this->getCurrentlyPlaying() << std::endl;
          }
          std::cout << "Playing video: " << i.getTitle() << std::endl << std::endl;
          this->setCurrentlyPlaying(i.getTitle());
          this->setPausedVideo(false);
          break;
      }
      ++currentIteration;
  }
}

void VideoPlayer::pauseVideo() {
    if (this->getCurrentlyPlaying() != "") {
        if (this->getPausedVideo()==true) {
            std::cout << "Video already paused: " << this->getCurrentlyPlaying() << std::endl << std::endl;
        }
        else {
            std::cout << "Pausing video: " << this->getCurrentlyPlaying() << std::endl << std::endl;
            this->setPausedVideo(true);
        }
    }
    else {
        std::cout << "Cannot pause video: No video is currently playing" << std::endl << std::endl;
    }
}

void VideoPlayer::continueVideo() {
    if (this->getCurrentlyPlaying() != "") {
        if (this->getPausedVideo() == true) {
            std::cout << "Playing video: " << this->getCurrentlyPlaying() << std::endl << std::endl;
            this->setPausedVideo(false);
        }
        else {
            std::cout << "Cannot continue video: Video is not paused" << std::endl << std::endl;
        }
    }
    else {
        std::cout<< "Cannot continue video: No video is currently playing" << std::endl << std::endl;
    }
}

void VideoPlayer::showPlaying() {
    if (this->getCurrentlyPlaying() == "") {
        std::cout << "No video is currently playing" << std::endl << std::endl;
    }
    else {
        for (auto i : mVideoLibrary.getVideos()) {
            if (i.getTitle() == this->getCurrentlyPlaying()) {
                std::cout << "Currently playing: " << i.getTitle() << " (" << i.getVideoId() << ") " << "[";
                int iteration = 0;
                for (auto j : i.getTags())
                {
                    if (iteration == 0) {
                        iteration++;
                        std::cout << j;
                    }
                    else {
                        std::cout << " " << j;
                    }
                }
                std::cout << "]" << std::endl<<std::endl;
                break;
            }
        }
    }
}

std::string transformingToLowerCase(std::string word)
{
    std::transform(word.begin(), word.end(), word.begin(),
        [](unsigned char c) { return std::tolower(c); });

    return word;
}

bool isValidName(std::string name) {
    //counting the whitesaoces to vheck if the name is vakid or not
    int count = 0;

    for (int i = 0; i < name.length(); i++) {
        int c = name[i];
        if (isspace(c)) {
            count++;
        }
    }
    if (count == 0) {
        return true;
    }
    else {
        return false;
    }
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
    bool hasAppeared = false;
    if (isValidName(playlistName)) {
        std::string loweredName = transformingToLowerCase(playlistName);
        for (int i = 0; i < playlistNames.size();++i) {
            if (loweredName == transformingToLowerCase(playlistNames[i])) {
                std::cout << "Cannot create playlist: A playlist with the same name already exists" << std::endl << std::endl;
                hasAppeared = true;
                break;
            }
        }
    }
    else {
        std::cout << "The playlist name should not contain whitespaces" << std::endl << std::endl;
    }
    if (!hasAppeared) {
        this->playlistNames.push_back(playlistName);
        std::cout << "Successfully created new playlist: " << playlistName << std::endl << std::endl;
        VideoPlaylist newPlaylist(playlistName);
        wholePlaylist.push_back(newPlaylist);
    }}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
    //if video or playlist does not exist, show a warning
    bool playlistHasAppeared = false, videoHasAppeared=false, videoExists=false;
    std::string playListAddedTo = "";

    if (isValidName(playlistName)) {
        std::string loweredName = transformingToLowerCase(playlistName);
        for (int i = 0; i < playlistNames.size(); ++i) {
            //checking if the playlist exists
            if (loweredName == transformingToLowerCase(playlistNames[i])) {
                playlistHasAppeared = true;
                playListAddedTo = playlistNames[i];
                break;
            }
        }
        if (playlistHasAppeared == true) {
            for (auto i : mVideoLibrary.getVideos()) {
                if (i.getVideoId() == videoId) {
                    videoExists = true;

                    for (auto i : wholePlaylist) {
                        if (i.getPlaylistName() == playListAddedTo) {
                            std::vector<std::string> videoIds = i.getVideoId();
                            for (int j = 0; j < videoIds.size(); ++j) {
                                if (videoIds[j] == videoId) {
                                    videoHasAppeared = true;
                                    break;
                                }
                            }
                            if (videoHasAppeared == true) {
                                std::cout << "Cannot add video to " << playlistName << ": Video already added" << std::endl << std::endl;
                                break;
                            }
                        }
                    }

                    if (videoHasAppeared == false) {
                        //adding video to playlist
                        std::cout << "Added video to " << playlistName << ": " << i.getTitle() << std::endl << std::endl;

                        for (auto i : wholePlaylist) {
                            if (i.getPlaylistName() == playListAddedTo) {
                                i.setVideoId(videoId);
                            }
                        }
                    }
                    break;
                }
            }
            if (videoExists == false) {
                std::cout << "Cannot add video to " << playListAddedTo << ": Video does not exist" << std::endl << std::endl;
            }
        }
        else {
            std::cout << "Cannot add video to " << playlistName << "t: Playlist does not exist" << std::endl << std::endl;
        }
    }
    else {
        std::cout << "Playlist name should not contain whitespaces";
    }
}

void VideoPlayer::showAllPlaylists() {
    if (wholePlaylist.size() == 0) {
        std::cout << "No playlists exist yet" << std::endl << std::endl;
    }
    else {
        std::cout << "Showing all playlists:" << std::endl;
        for (auto i : wholePlaylist) {
            std::cout << "  " << i.getPlaylistName() << std::endl;
        }
        std::cout << std::endl;
    }
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
    bool videosExist = false, playlistExists = false;
    for (auto k : wholePlaylist) {
        std::string loweredName = transformingToLowerCase(playlistName);
        if (transformingToLowerCase(k.getPlaylistName()) == loweredName) {
            playlistExists = true;
            std::cout << "Showing playlist :" << k.getPlaylistName() << std::endl;

            std::vector<std::string> videoIds = k.getVideoId();
            for (int l = 0; l < videoIds.size(); ++l) {
                for (auto i : mVideoLibrary.getVideos())
                {
                    if (videoIds[l] == i.getVideoId()) {
                        std::cout << "  " << i.getTitle() << " (" << i.getVideoId() << ") " << "[";
                        int iteration = 0;
                        for (auto j : i.getTags())
                        {
                            if (iteration == 0) {
                                iteration++;
                                std::cout << j;
                            }
                            else {
                                std::cout << " " << j;
                            }
                        }
                        std::cout << "]" << std::endl;
                        videosExist = true;
                    }
                }
            }
        }
    
        if (videosExist == false) {
            std::cout << "  No videos here yet" << std::endl << std::endl;
        }
    }
    if (playlistExists == false) {
        std::cout << "Cannot show playlist " << playlistName << ": Playlist does not exist";
    }
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
  std::cout << "removeFromPlaylist needs implementation" << std::endl;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {
  std::cout << "deletePlaylist needs implementation" << std::endl;
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::cout << "searchVideos needs implementation" << std::endl;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
