#include "videoplaylist.h"

VideoPlaylist::VideoPlaylist(std::string name){
	playlistName = name;
}

std::string VideoPlaylist::getPlaylistName(){
	return playlistName;
}

std::vector<std::string> VideoPlaylist::getVideoId(){
	return videoId;
}

void VideoPlaylist::setPlaylistName(std::string newName){
	playlistName = newName;
}

void VideoPlaylist::setVideoId(std::string newId){
	videoId.push_back(newId);
}


