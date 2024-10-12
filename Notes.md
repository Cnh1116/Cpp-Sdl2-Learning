--- Class Organization / Functionality ---

The window class has a update method. Maybe ESC quits, ` opens debug menu. How to get native resolution ?
Sprite Class
Item Class
Logging Class
Player Class -> A sprite, stats, abilities
Enemy Class
Math Class
Sound Class
Ability Class -> Button to be pressed, item interactions, sprite to show, sound to make

Game Class: has a player, enemy spawner, item spawner game and debug window

Things to fix:
- Projectiles needs to have its animations code cleaned up. Maybe projectiles base class does a tick increment, or a cooldown time based frame change.
- NO VECTORS FOR ANIMATIONS, ONLY FOR DYNAMIC OBJECTS
- Vector.reserve(20) for projectiles, maybe 10 enemies. 5 items??
- Emplace back instead of push back for vectors.
- Pixel scale needs to be revisited and rethought about, making the collision rectangles weird.
- Instead of the 7 get  secondary_projectiles function calls, better to get the secondary fire object from player class then grab an attribute.
- Use const reference when passing data as merely reading values and copying them for short time
- Clean up code style, comments.

--- Goals ---

~~1. Debug Screen -> Maybe main and debug screen are apart of the game class~~
~~2. Draw a sprite~~
~~3. If SDL_Event == 'D', sprite move right~~
~~4. Change Background~~
~~5. Primary and secondary fire~~
~~6. got basic item spawn~~

--- My Game Ideas ---

1. Make the game _9_ tiles wide. ITems can spawn on the "bridge". _3_ tiles wide. Bridge shifts collumns over time. _Maybe_
2. Having a primary fire to straight forward, secondary fire to pick up items on the "bridge" ✅
3. A full body shield that breaks when hit. Has X amoount of cooldown. Make this act like a parry, very low amount of time active and then a quick cooldown to use it again. Needs to be added, maybe next?

   3.a. Shield should record how much damage attack was: normalize 1 damage to MAX_IN_GAME damage, and multiply this percentage to a max frequency sound to play when absorbing damage. higher pitch for absorbing more damage.

--- Item Ideas ---

- Ruby Radio - Fire Damage 🔥 Maybe you BECOME fire, and grabbing a diff element changes current type
- Saphire ... Ice Damage ❄️
- Emerald ... Poison / Nature ? 🌱
- Diamond ... Arcane / 🔮

- Iron - Take less damage
- Gold - Speed ⬆️
- Platinum - DPS up ?

- Glass Toucan - Damage or crit?
- Wooden Frog ⬇️ Lower "parry / shield" CDR
- Plastic
