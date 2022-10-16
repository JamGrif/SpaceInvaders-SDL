![](https://github.com/JamGrif/SpaceInvaders-SDL/blob/main/res/media/banner1.png)

# SpaceInvaders-SDL  

A complete Space Invaders game made using SDL2 in C++. Small project I've been working on in my spare time for fun.

**Full game showcase video:**

# Gameplay Features  
- Player can destroy aliens in order to gain score  
- When the player destroys all aliens, they move onto the next round and gain an additional life  
- Can press the *esc* key to pause the game
- The game is virtually endless and can only end if either of the following conditions are met:  
  - If the player runs out of lives, the player gets taken to the game over screen  
  - If the aliens reach the ending line, the player gets taken to the game over screen  
- Player can hide behind the blocks which take damage and can be destroyed upon hit
- The blocks will respawn on game reset
- The game over screen displays final score and why the player was brought to the game over screen  
- Each type of alien is worth a different amount of score:    
  - Lower Alien:  10  
  - Middle Alien: 20  
  - Upper Alien:  30  
  - Boss Alien:   ???   

# Program Features  
- Uses **SDL2** and its other libraries: **SDL2_image**, **SDL2_mixer**, **SDL2_ttf**  
- The levels geometry and starting objects are created using the Tiled application  
- Levels created in Tiled are saved as a .tmx (.xml) file and read from the program  
- The level files are read, decoded and decompressed with the help of other libraries: **tinyXML**, **Base64**, **zlib**  
- The game uses a Finite State Machine to organise and swap between the states  
- Currently, there are four states which can be changed too:  
  - PlayState  
  - MainMenuState  
  - PauseState  
  - GameOverState  
- Game has audio support and has sound effects and a looping music track
- Game has TrueType font support  
  
  
![](https://github.com/JamGrif/SpaceInvaders-SDL/blob/main/res/media/banner3.png)

![](https://github.com/JamGrif/SpaceInvaders-SDL/blob/main/res/media/banner2.png)

![](https://github.com/JamGrif/SpaceInvaders-SDL/blob/main/res/media/banner4.png)

![](https://github.com/JamGrif/SpaceInvaders-SDL/blob/main/res/media/banner5.png)


