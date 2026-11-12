# Music Playlist Manager (C++)

A console-based B.Tech DSA project using a **circular singly linked list**.

## Features
- Add songs with unique ID, title, artist, and duration in seconds
- Remove a song by ID or exact title
- Display all songs
- Move to next song (last -> first)
- Move to previous song (using traversal)
- Search by ID or exact title and select the song
- Display current song and total count
- Handles empty and single-song playlists
- Releases allocated nodes on deletion and program exit

## Compile and run

### macOS / Linux (g++)
Open Terminal in this folder and run:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic music_playlist_manager.cpp -o music_playlist_manager
./music_playlist_manager
```

### Windows (MinGW)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic music_playlist_manager.cpp -o music_playlist_manager.exe
music_playlist_manager.exe
```

## Notes / current limitations
- This is a console-based playlist manager; it does not play audio.
- Song data is stored in memory and is not saved after exiting.
- Title search is exact and case-sensitive.
- Previous-song navigation is O(n) because this implementation uses a singly circular linked list.
- Song IDs must be unique.

## Suggested demo
1. Add ID `101`, title `Night Drive`, artist `Artist A`, duration `225`.
2. Add ID `102`, title `Summer Days`, artist `Artist B`, duration `190`.
3. Add ID `103`, title `Midnight Rain`, artist `Artist C`, duration `240`.
4. Display all songs.
5. Move Next until ID 103 is current, then move Next again; ID 101 should be current.
6. Search for ID 102 and select it.
7. Delete ID 102 and display the playlist again.
8. Show current song and total count.
