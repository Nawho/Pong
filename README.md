# Pong (In Dev)
The classic arcade game is brought to life again with **C++ and SDL2**, providing an entertaining gaming experience with both singleplayer and multiplayer modes. Prepare yourself for some intense, retro-inspired paddle action! 🏓

<details>
<summary>
   <h3> Gameplay & Controls 🕹️</h3>
</summary>
The round will be played until a player scores 11 points or the timer runs out. When the timer runs out, the player with most points will win.
You can choose singleplayer mode, to test you skills facing an AI-controlled opponent. (May include difficulty levels in the future) or multiplayer mode to play locally with your friends or familiy.

<br>
<br>

**Singleplayer controls:** move your paddle with [W] or [↑] and [S] or [↓]

**Multiplayer controls:** one player moves their paddle with [↑], [↓] and the other [W], [S]

</details>

<details>
<summary>
   <h3> Installation 📥</h3>
</summary>
  
### Simply want to play?
Perfect! Go to "Releases" and download the appropiate version for you operating system. Have fun!

<br/>

### Want to download and tweak the code?
For now, you can clone the repository, download the necessary libraries: SDL2, SDL_mixer and SDL_ttf and the configure the dependencies manually to work in VS Code (recommended) or wherever you prefer. 
In the future, I will add CMake to the project for this to be easier. For now, be patient.

</details>

<details>
<summary>
   <h3> Release History 📜 </h3>
</summary>
  

###  Latest Changes
- Version 1.0.0 (Initial Release)
    - Classic Pong gameplay in singleplayer mode with a simple yet challenging AI.

</details>


<details>
<summary>
   <h3> Collaboration & contributions 🤝🏻 </h3>
</summary>
   For now, the project is not open for contributions, but you can fork the repo and use it for you own version or project.
</details>


<details>
<summary>
  <h3> Planned features 🚀 & known bugs 🐛</h3>
</summary>
  
### Planned features
- Multiplayer mode.
- Infinite mode.
- A set of different levels with increasing difficulty for singleplayer mode.

<br>

### Known bugs
- Ball can glitch when the paddle hits it vertically because of the way the collisions are implemented.
  
</details>

<br>

## License
This project is licensed under the MIT License.
