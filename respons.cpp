#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;
const int MAX_DATA = 100;

struct Song
{
    string lyric[MAX_DATA], title;
};

Song songs[MAX_DATA];
string saveLyricToFile = "C:\\C++1\\The Real Sandbox\\Practicum9\\Lyric\\";
int totalSong = 0;

int integerDetection();
void mainMenu();
void playlistMenu();
void inputSong();
void playSong();
void deleteSong();
void listOfPlaylist();
void openPlaylist();

int main(){
    int menuSelection;
    bool change = true;
    
    while (change)
    {
        mainMenu();
        menuSelection = integerDetection();
        system("cls");

        switch (menuSelection)
        {
        case 1:
            inputSong();
            system("pause");
            system("cls");
            break;
        
        case 2:
            openPlaylist();
            system("pause");
            system("cls");
            break;
        
        case 3:
            cout << "\tThank You\n" << endl;
            change = false;
            break;
        
        default:
            cout << "Invalid Input, Please Try Again!" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    
    cin.get();
    return 0;
}

int integerDetection(){
    int input;
    while (!(cin >> input))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter an integer input: ";
    }
    return input;
}

void mainMenu(){
    cout << "Amount of song in playlist: " << totalSong << endl << endl;
    cout << "\tMenu" << endl;
    cout << "1. Input Song" << endl;
    cout << "2. Open Playlist" << endl;
    cout << "3. Exit" << endl << endl;
    cout << "Enter menu: ";
}

void playlistMenu(){
    cout << "\tMenu" << endl;
    cout << "1. Play a Song" << endl;
    cout << "2. Delete a Song" << endl << endl;
    cout << "Enter menu: ";
}

void inputSong(){
    cout << "\tInput Song" << endl << endl;
    cout << "Song Title: ";
    cin.ignore();
    getline(cin, songs[totalSong].title);

    fstream savePlaylist("Playlist.txt", ios::app);
    if (savePlaylist.is_open())
    {
        savePlaylist << songs[totalSong].title << endl;
        savePlaylist.close();
    }else
    {
        cout << "Cannot open file" << endl;
    }  

    cout << "\n\tInput Lyric" << endl;
    cout << "\tInput (---) to save" << endl << endl;

    fstream saveLyric(saveLyricToFile + songs[totalSong].title + ".txt", ios::app);

    int line = 0;

    while (true)
    {
        getline(cin >> ws, songs[totalSong].lyric[line]);

        if (songs[totalSong].lyric[line] == "---")
        {
            break;
        }        

        if (saveLyric.is_open())
        {
            saveLyric << songs[totalSong].lyric[line] << endl;
        }else
        {
            cout << "Cannot open file" << endl;
        }
        line++;
    }

    saveLyric.close();
    totalSong++;
}

void listOfPlaylist(){
    cout << "\tPlaylist" << endl;

    for (int i = 0; i < totalSong - 1; i++)
    {
        for (int j = 0; j < totalSong - i - 1; j++)
        {
            if (songs[j].title > songs[j + 1].title)
            {
                string temp = songs[j].title;
                songs[j].title = songs[j + 1].title;
                songs[j + 1].title = temp;
            }                
        }
    }

    fstream sortingPlaylistFile("Playlist.txt", ios::out);

    if (sortingPlaylistFile.is_open())
    {
        for (int i = 0; i < totalSong; i++)
        {
            sortingPlaylistFile << songs[i].title << endl;
            cout << i + 1 << ". " << songs[i].title << endl;
        }
        sortingPlaylistFile.close();
    }else
    {
        cout << "Cannot open file" << endl;
    }
}

void playSong(){
    string songLyrics;
    int choice;

    listOfPlaylist();

    cout << "\nChoose a song to play (Integer): ";
    choice = integerDetection();
    system("cls");

    if (choice < 1 || choice > totalSong)
    {
        cout << "No song found" << endl;
    }else
    {
        for (int i = 0; i < totalSong; i++)
        {
            if (choice == (i + 1))
            {
                fstream playSongFromFile(saveLyricToFile + songs[i].title + ".txt", ios::in);
                cout << "\t" << songs[i].title << endl << endl;
                cout << "Lyrics" << endl << endl;

                if (playSongFromFile.is_open())
                {
                    while (!playSongFromFile.eof())
                    {
                        getline(playSongFromFile, songLyrics);
                        cout << songLyrics << endl;
                    }
                    playSongFromFile.close();              
                }else
                {
                    cout << "Cannot open file" << endl;
                }                   
            }            
        }        
    }
}

void deleteSong(){
    string songTitleTemp;
    int choose;
    int titleInArray = 0;

    listOfPlaylist();

    cout << "\nChoose a song to delete (Integer): ";
    choose = integerDetection();
    system("pause");
    system("cls");

    if (choose < 1 || choose > totalSong)
    {
        cout << "No song found" << endl;
    }else
    {
        for (int i = 0; i < totalSong; i++)
        {
            if (choose == (i + 1))
            {
                songTitleTemp = songs[i].title;

                fstream rewriteSongTitle("Playlist.txt", ios::out);

                if (rewriteSongTitle.is_open())
                {
                    for (int j = 0; j < totalSong; j++)
                    {
                        if (songs[j].title != songTitleTemp)
                        {
                            rewriteSongTitle << songs[j].title << endl;
                        }
                    }
                    rewriteSongTitle.close();
                }else
                {
                    cout << "Cannot open file" << endl;
                }

                fstream rewriteSongTitleArray("Playlist.txt", ios::in);

                if (rewriteSongTitleArray.is_open())
                {
                    while (!rewriteSongTitleArray.eof())
                    {
                        getline(rewriteSongTitleArray, songs[titleInArray].title);
                        titleInArray++;
                    }
                    rewriteSongTitleArray.close();
                }else
                {
                    cout << "Cannot open file" << endl;
                }
                
                string lyricToDelete = saveLyricToFile + songTitleTemp + ".txt";

                if (remove(lyricToDelete.c_str()) == 0)
                {
                    cout << "Song with title: " << songTitleTemp << endl;
                    cout << "Has been deleted successfully" << endl << endl;
                }else
                {
                    cout << "Cannot delete file" << endl;
                }                
            }
        }
        totalSong--;
    }
}

void openPlaylist(){
    int playlistSelection;
    bool access = true;

    if (totalSong == 0)
    {
        cout << "Playlist is empty" << endl;
    }else
    {
        while (access)
        {
            listOfPlaylist();
            cout << endl;

            playlistMenu();
            playlistSelection = integerDetection();
            system("cls");

            switch (playlistSelection)
            {
            case 1:
                playSong();
                access = false;
                break;
            
            case 2:
                deleteSong();
                access = false;
                break;

            default:
                cout << "Invalid Input, Please Try Again!" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
    }
}