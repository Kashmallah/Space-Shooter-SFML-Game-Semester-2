# Space-Shooter-SFML-Game-Semester-2
Overview

This space shooter game is the final project for the Object-Oriented Programming Course at Bahria University, created by students from BS IT 2-A. The development team includes:

Kashmallah Shah    

Introduction
Space Shooter games have been a classic genre that has captivated players for decades. The thrill of navigating through the vastness of space, dodging enemy fire, and engaging in intense battles has made them a timeless favorite. In this project, we bring you our interpretation of the space shooter genre, featuring dynamic gameplay, two-player functionality, and binary file handling for enhanced player experience.

File Structure
Bullet.h/Bullet.cpp

Contains tasks related to bullets fired by the player.
Enemy.h/Enemy.cpp

Manages movements and upgrades related to the three types of enemies in the game.  
Game.h/Game.cpp

Contains overall game functionality, including handling player input, game mechanics, and scoring.  
Player.h/Player.cpp

Loads textures for the game, initializes player movements and body updates, and manages two players with distinct controls. 

dArr.h  
Resource file for dynamic array management. This class provides functionalities for dynamic memory management, element addition, removal, and various operations on the array.  

Controls  
Player 1 (WASD + Spacebar)  
W: Move up  
A: Move left  
S: Move down  
D: Move right  
Spacebar: Shoot bullets  
1: Change body texture to left wing  
2: Change body texture to right wing  
3: Change body texture to cockpit  
4: Change body texture to auras  

Player 2 (Keypad Controls)  
8 Keypad: Move up  
4 Keypad: Move left  
5 Keypad: Move down  
6 Keypad: Move right  
0 Keypad: Shoot bullets  
1: Change body texture to left wing  
2: Change body texture to right wing  
3: Change body texture to cockpit  
4: Change body texture to auras  

Binary File Handling  
The game implements binary file handling to store the following information:  
->Score  
->Multiplier  
->Multiplier Timer  
->New Multiplier  

How to Play:  
->Clone the repository.  
->Open the project in Visual Studio Professional.  
->Link the SFML file.  
->Build and run the game.  
->Use the specified controls for each player to navigate through the game and shoot enemies.  
->Change body textures by pressing the corresponding keys.  
->Your progress and scores will be stored in binary files.  
->The score will be displayed on screen as well.  

Enjoy playing the space shooter game! If you encounter any issues or have suggestions, feel free to contact the developers.

