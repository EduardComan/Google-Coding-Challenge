#pragma once
#include<iostream>
#include<vector>
/** A class used to represent a Playlist */

class VideoPlaylist {
private:
	std::string playlistName;
	std::vector<std::string> videoId;

public:
	VideoPlaylist() = default;
	VideoPlaylist(std::string name);

	std::string getPlaylistName();
	std::vector<std::string> getVideoId();
	void setPlaylistName(std::string newName);
	void setVideoId(std::string newId);
};
