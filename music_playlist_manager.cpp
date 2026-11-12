#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Song {
    int id;
    string title;
    string artist;
    int duration; // duration in seconds
    Song* next;
};

class MusicPlaylist {
private:
    Song* head;
    Song* tail;
    Song* current;
    int songCount;

    Song* findById(int id) const {
        if (head == nullptr) return nullptr;
        Song* temp = head;
        do {
            if (temp->id == id) return temp;
            temp = temp->next;
        } while (temp != head);
        return nullptr;
    }

    Song* findByTitle(const string& title) const {
        if (head == nullptr) return nullptr;
        Song* temp = head;
        do {
            if (temp->title == title) return temp;
            temp = temp->next;
        } while (temp != head);
        return nullptr;
    }

    void showSong(const Song* song) const {
        if (song == nullptr) {
            cout << "No song selected.\n";
            return;
        }
        cout << "ID: " << song->id
             << " | Title: " << song->title
             << " | Artist: " << song->artist
             << " | Duration: " << song->duration / 60 << "m "
             << song->duration % 60 << "s\n";
    }

    void clearInputLine() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    MusicPlaylist() : head(nullptr), tail(nullptr), current(nullptr), songCount(0) {}

    ~MusicPlaylist() {
        clearAll();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void addSong() {
        Song* song = new Song;
        cout << "Enter song ID: ";
        if (!(cin >> song->id)) {
            cin.clear();
            clearInputLine();
            delete song;
            cout << "Invalid ID.\n";
            return;
        }

        if (findById(song->id) != nullptr) {
            delete song;
            clearInputLine();
            cout << "That song ID already exists. Use a unique ID.\n";
            return;
        }

        clearInputLine();
        cout << "Enter song title: ";
        getline(cin, song->title);
        cout << "Enter artist name: ";
        getline(cin, song->artist);
        cout << "Enter duration in seconds: ";
        if (!(cin >> song->duration) || song->duration < 0) {
            cin.clear();
            clearInputLine();
            delete song;
            cout << "Invalid duration. Song was not added.\n";
            return;
        }
        clearInputLine();

        song->next = nullptr;
        if (head == nullptr) {
            head = tail = song;
            song->next = head;
            current = song;
        } else {
            tail->next = song;
            tail = song;
            tail->next = head;
        }

        songCount++;
        cout << "Song added successfully.\n";
    }

    void displaySongs() const {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\n--- Playlist (" << songCount << " song(s)) ---\n";
        Song* temp = head;
        int position = 1;
        do {
            cout << position++ << ". ";
            showSong(temp);
            temp = temp->next;
        } while (temp != head);
    }

    void nextSong() {
        if (isEmpty()) {
            cout << "Playlist is empty. Add a song first.\n";
            return;
        }
        current = current->next;
        cout << "Current song:\n";
        showSong(current);
    }

    void previousSong() {
        if (isEmpty()) {
            cout << "Playlist is empty. Add a song first.\n";
            return;
        }
        if (current == head) {
            current = tail;
        } else {
            Song* temp = head;
            while (temp->next != current) {
                temp = temp->next;
            }
            current = temp;
        }
        cout << "Current song:\n";
        showSong(current);
    }

    void searchSong() {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "Search by 1. ID or 2. Title? ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            clearInputLine();
            cout << "Invalid choice.\n";
            return;
        }
        clearInputLine();

        Song* found = nullptr;
        if (choice == 1) {
            int id;
            cout << "Enter song ID: ";
            if (!(cin >> id)) {
                cin.clear();
                clearInputLine();
                cout << "Invalid ID.\n";
                return;
            }
            clearInputLine();
            found = findById(id);
        } else if (choice == 2) {
            string title;
            cout << "Enter exact song title: ";
            getline(cin, title);
            found = findByTitle(title);
        } else {
            cout << "Please choose 1 or 2.\n";
            return;
        }

        if (found == nullptr) {
            cout << "Song not found.\n";
        } else {
            current = found;
            cout << "Song found and selected:\n";
            showSong(current);
        }
    }

    void removeSong() {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "Remove by 1. ID or 2. Title? ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            clearInputLine();
            cout << "Invalid choice.\n";
            return;
        }
        clearInputLine();

        int id = 0;
        string title;
        if (choice == 1) {
            cout << "Enter song ID: ";
            if (!(cin >> id)) {
                cin.clear();
                clearInputLine();
                cout << "Invalid ID.\n";
                return;
            }
            clearInputLine();
        } else if (choice == 2) {
            cout << "Enter exact song title: ";
            getline(cin, title);
        } else {
            cout << "Please choose 1 or 2.\n";
            return;
        }

        Song* target = nullptr;
        if (choice == 1) target = findById(id);
        else target = findByTitle(title);

        if (target == nullptr) {
            cout << "Song not found.\n";
            return;
        }

        Song* previous = tail;
        while (previous->next != target) {
            previous = previous->next;
        }

        if (target == head && target == tail) {
            head = tail = current = nullptr;
        } else {
            previous->next = target->next;
            if (target == head) head = target->next;
            if (target == tail) tail = previous;
            tail->next = head;
            if (current == target) {
                current = target->next;
            }
        }

        delete target;
        songCount--;
        cout << "Song removed successfully.\n";
        if (current != nullptr) {
            cout << "Current song:\n";
            showSong(current);
        } else {
            cout << "Playlist is now empty.\n";
        }
    }

    void showCurrentSong() const {
        if (isEmpty()) {
            cout << "Playlist is empty. No current song.\n";
            return;
        }
        cout << "Current song:\n";
        showSong(current);
        cout << "Total songs: " << songCount << "\n";
    }

    void clearAll() {
        if (head == nullptr) return;

        // Break the circle, then delete nodes safely.
        tail->next = nullptr;
        Song* temp = head;
        while (temp != nullptr) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = current = nullptr;
        songCount = 0;
    }
};

int main() {
    MusicPlaylist playlist;
    int choice;

    do {
        cout << "\n========== MUSIC PLAYLIST MANAGER ==========\n";
        cout << "1. Add a song\n";
        cout << "2. Remove a song\n";
        cout << "3. Display all songs\n";
        cout << "4. Next song\n";
        cout << "5. Previous song\n";
        cout << "6. Search and select a song\n";
        cout << "7. Show current song and total count\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
            case 1: playlist.addSong(); break;
            case 2: playlist.removeSong(); break;
            case 3: playlist.displaySongs(); break;
            case 4: playlist.nextSong(); break;
            case 5: playlist.previousSong(); break;
            case 6: playlist.searchSong(); break;
            case 7: playlist.showCurrentSong(); break;
            case 0: cout << "Exiting Music Playlist Manager. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
